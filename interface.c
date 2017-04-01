#include "interface.h"

struct TCD_istruct{
	long all_articles, unique_articles, all_revisions;
	hashTArt ht_art;
	hashTContrib ht_contrib;
	avlArt avlA;
	avlContrib avlC;
};

TAD_istruct init(){
	TAD_istruct qs = malloc(sizeof(struct TCD_istruct));
	qs->all_articles = qs->all_revisions = qs->unique_articles = 0;
	hashTArt_Init(qs->ht_art);
	hashTContribInit(qs->ht_contrib);

	return qs;
};

void parsePage(TAD_istruct qs, xmlNodePtr cur);

TAD_istruct load(TAD_istruct qs, int nsnaps, char * snaps_paths[]){

	xmlDocPtr doc;
	xmlNodePtr cur;
	int i;

	for(i=0; i<nsnaps; i++){

		doc = xmlReadFile(snaps_paths[i],NULL,0);

		cur = xmlDocGetRootElement (doc);

		if (cur == NULL) {
			fprintf(stderr,"empty document\n");
			xmlFreeDoc(doc);
			return 0;
		}

		if (xmlStrcmp(cur->name, (const xmlChar *) "mediawiki")) {
			fprintf(stderr,"document of the wrong type, root node != mediawiki");
			xmlFreeDoc(doc);
			return 0;
		}

		cur = cur->xmlChildrenNode;
		while(cur){
			if((!xmlStrcmp(cur->name, BAD_CAST "page")))
				parsePage(qs,cur);
			cur=cur->next;
		}

		xmlFreeDoc(doc);
	}
	return qs;
}

long all_articles(TAD_istruct qs){
	return qs->all_articles;
}

long unique_articles(TAD_istruct qs){
	return qs->unique_articles;
}

long all_revisions(TAD_istruct qs){
	return qs->all_revisions;
}

long* top_10_contributors(TAD_istruct qs){
	long* top = calloc(sizeof(long),10);
	avlContrib_TopN(qs->avlC, top, 0, 10);
	return top;
}       

char* contributor_name(long contributor_id, TAD_istruct qs){
	return NULL;
}

long* top_20_largest_articles(TAD_istruct qs){
	return NULL;
}

char* article_title(long article_id, TAD_istruct qs){
	return hashTArt_GetTitle (qs->ht_art, article_id);
}

long* top_N_articles_with_more_words(int n, TAD_istruct qs){
	return NULL;
}

char** titles_with_prefix(char* prefix, TAD_istruct qs){
	return hashTArt_Prefix(qs->ht_art, prefix);
}

char* article_timestamp(long article_id, long revision_id, TAD_istruct qs){
	return hashTArt_Timestamp (qs->ht_art, article_id, revision_id);
}

TAD_istruct clean (TAD_istruct qs){
	hashTArt_Clean(qs->ht_art);
	hashTContribClean(qs->ht_contrib);
	avl_Clean(qs->avlA);
	avl_Clean(qs->avlC);
	return qs;
}

/* Funções de parsing
 *
 * parseText -> Pega no texto dos artigos e devolve por referencia o numero de bytes e palavras do texto.
 * parseContributors -> Pega no nodo de contribuidores do xml e devolve por referencia o seu nome e id.
 * parseRevision -> Pega no nodo de revisão de um artigo e vai buscar a informação com o auxilio das duas funções anteriores.
 * parsePage -> Pega no nodo de uma página de artigo e extrai dela toda a informação para carregar na estrutura de dados.
 *
 */

void parseText(xmlNodePtr cur, int* nbytes, int* nwords){
	char* text = (char*) xmlNodeGetContent(cur);
	int i, words= 0;
	for(i=0; text[i]!='\0';i++)
		if(text[i]==' ' || text[i]=='\n' || text[i]=='\t') words++;
	*nbytes = i-1;
	*nwords = words;
	free(text);
}

int parseContributors(xmlNodePtr cur, xmlChar** cont_name, xmlChar** cont_id){

	cur = cur->xmlChildrenNode;
	int i;

	while(cur){
		if((!xmlStrcmp(cur->name, BAD_CAST "ip"))){
			i=0;
			cur=cur->next;
		}
		else{
			if((!xmlStrcmp(cur->name, BAD_CAST "username")))
				*cont_name = xmlNodeGetContent(cur);
			if((!xmlStrcmp(cur->name, BAD_CAST "id")))
				*cont_id = xmlNodeGetContent(cur);
			i=1;
		}
		cur = cur->next;
	}
	return i;
}

int parseRevision(xmlNodePtr cur, xmlChar** rv_id, xmlChar** tstamp, xmlChar** cont_name, xmlChar** cont_id, int* nbytes, int* nwords){

	int i;
	cur = cur->xmlChildrenNode;

	while(cur){
		if((!xmlStrcmp(cur->name, BAD_CAST "id")))
			*rv_id = xmlNodeGetContent(cur);
		if((!xmlStrcmp(cur->name, BAD_CAST "timestamp")))
			*tstamp = xmlNodeGetContent(cur);
		if((!xmlStrcmp(cur->name, BAD_CAST "contributor")))
			i=parseContributors(cur, cont_name, cont_id);
		if((!xmlStrcmp(cur->name, BAD_CAST "text") && cur->type == 1))
			parseText(cur, nbytes, nwords);
		cur = cur->next;
	}
	return i;
}

void parsePage(TAD_istruct qs, xmlNodePtr cur){

	xmlChar* title, *title_id, *revision_id, *timestamp, *contributor_name, *contributor_id;
	int n_bytes, n_words;
	int contrib,add_code = 0;

	cur = cur->xmlChildrenNode;
	while(cur){
		if((!xmlStrcmp(cur->name, BAD_CAST "title")))
			title = xmlNodeGetContent(cur);
		if((!xmlStrcmp(cur->name, BAD_CAST "id")))
			title_id = xmlNodeGetContent(cur);
		if((!xmlStrcmp(cur->name, BAD_CAST "revision")))
			contrib=parseRevision(cur, &revision_id, &timestamp, &contributor_name, &contributor_id, &n_bytes, &n_words);

		cur = cur->next;
	}
	add_code = hashTArt_Add (qs->ht_art, (char*)title, (long) atoi( (char*) title_id), n_bytes, n_words, (long) atoi( (char*) revision_id), (char*) timestamp, &(qs->avlA));
	qs->all_articles++;
	if (add_code) qs-> all_revisions++;
	if (add_code == 2) qs-> unique_articles++;

	xmlFree(title);
	xmlFree(title_id);
	xmlFree(revision_id);
	xmlFree(timestamp);
	if(contrib){ 
		if(add_code) 
			hashTContribAdd(qs->ht_contrib,(char*) contributor_name, (long) atoi( (char*) contributor_id), &(qs->avlC));
		xmlFree(contributor_id);
		xmlFree(contributor_name);
	}
}

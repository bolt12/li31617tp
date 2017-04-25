#include "hashTArt.h"
#include "avl.h"

typedef struct stringList{
	char * string;
	struct stringList * next;

} *StringList;

/* Funções referentes à hashTArt */

int hashCode (long title_ID){
	return (title_ID % SIZE);
} 

void hashTArt_Init (hashTArt h){
	int i;
	for(i = 0; i < SIZE; i++){
		h[i] = NULL;
	}
}

/*
   Se res == 0->Não foi adicionado nenhum artigo nem nenhuma revisão
   Se res == 1->Foi adicionada apenas uma revisão
   Se res == 2->Foi adicionada um novo artigo (consequentemente uma nova revisão)
   */
int hashTArt_Add (hashTArt h, char* title, long title_ID, int n_bytes, int n_words, long revision_id, char* timestamp, 
		avlArtBytes *avlBytes, avlArtWords *avlWords){
	int pos = hashCode (title_ID);
	artNodo ant, aux, new = NULL;
	int res = 0;
	for(aux = ant = h[pos]; aux && aux -> title_ID != title_ID; ant = aux, aux = aux-> next);
	if(!aux){
		res++;
		new = malloc (sizeof (struct hashtable));
		new-> title = strdup (title);
		new-> title_ID = title_ID;
		new-> n_bytes = n_bytes;
		new-> n_words = n_words;
		new-> revisions = NULL;
		new-> next = NULL;
		if(!h[pos]){
			h[pos] = new;
			*avlBytes = avlArtBytes_Insert(*avlBytes,new);
			*avlWords = avlArtWords_Insert(*avlWords,new);
		}
		else{
			ant->next = new;
			*avlBytes = avlArtBytes_Insert(*avlBytes,new);
			*avlWords = avlArtWords_Insert(*avlWords,new);
		}
		aux = new;
	}
	else{
		*avlBytes = avlArtBytes_Remove(*avlBytes,aux);
		*avlWords = avlArtWords_Remove(*avlWords,aux);
		free(aux->title);
		aux-> title = strdup (title);

		if (aux->n_bytes < n_bytes) aux->n_bytes = n_bytes;
		if (aux->n_words < n_words) aux->n_words = n_words;

		*avlBytes = avlArtBytes_Insert(*avlBytes, aux);
		*avlWords = avlArtWords_Insert(*avlWords,aux);
	}

	res += insertRevision(&aux->revisions, revision_id, timestamp);

	return res;
}

char *hashTArt_GetTitle (hashTArt h, long title_ID){
	int pos = hashCode (title_ID);
	artNodo aux;
	for(aux = h[pos]; aux && aux->title_ID != title_ID; aux = aux-> next);
	if(aux)
		return (aux-> title);

	return NULL;
}

int stringComparator (const void * a, const void * b ) {
    const char *pa = *(const char**)a;
    const char *pb = *(const char**)b;

    return strcmp(pa,pb);
}


char** hashTArt_Prefix (hashTArt h, char* prefix){
	int size = 30;
	char **result = calloc (size, sizeof(char*) );
	int ins_pos=0, hash_pos;
	artNodo aux;

	for (hash_pos = 0; hash_pos < SIZE; hash_pos++)
		for (aux = h[hash_pos]; aux; aux = aux->next)
			if (!strncmp(prefix, aux->title, strlen(prefix))){

					if (ins_pos > (size * 0.8)){
						size = size * 2;
						result = realloc(result, size * sizeof(char *));
					}

					result[ins_pos] =strdup (aux->title);
					ins_pos++;
			}
	qsort(result, ins_pos-1, sizeof(char*), stringComparator);
	result[ins_pos] = NULL;
	return result;
	
}
char* hashTArt_Timestamp (hashTArt h, long title_ID, long revision_id){
	int pos = hashCode (title_ID);
	artNodo aux;
	for(aux = h[pos]; aux && aux->title_ID != title_ID; aux = aux-> next);
	if(aux){
		return (retrieveTimestamp(aux->revisions, revision_id));
	}

	return NULL;
}

void hashTArt_Clean (hashTArt h){
	int i;
	artNodo aux, ant;
	for(i = 0; i < SIZE; i++){
		aux = h[i];
		while (aux){
			free (aux-> title);
			cleanList(&aux->revisions);
			ant = aux;
			aux = aux->next;
			free(ant);
		}
		h[i] = NULL;
	}
}

void hashTArt_Print (hashTArt h){
	int i;
	artNodo aux;
	for(i = 0; i < SIZE; i++){

		for(aux = h[i]; aux; aux = aux-> next){
			printf("%p \t%d->",h[i], i);
			printf("Title: %ld\t",aux->revisions->revision_id);
		}
		printf("\n");
	}
}

/* Funções referentes à avlArtBytes */

avlArtBytes avlArtBytes_Insert(avlArtBytes p, artNodo n)
{
	if ( !p )
		return new_AVL(n);

	if (((artNodo) p->artigo)->title_ID == n->title_ID)
		p->artigo = n;
	else{ 
		if(n->n_bytes == ((artNodo) p->artigo)->n_bytes){
			if(n->title_ID < ((artNodo) p->artigo)->title_ID){
				artNodo aux = p->artigo;
				p->artigo = n;
				n = aux;
			}
			p->left = avlArtBytes_Insert(p->left, n);
		}
		else if( n->n_bytes > ((artNodo) p->artigo)->n_bytes )
			p->right = avlArtBytes_Insert(p->right, n);
		else
			p->left = avlArtBytes_Insert(p->left, n);
	}
	return balance(p);
}

int avlArtBytes_TopN(avlArtBytes avl, long* top, int i, int n){

	if(!avl) return i;
	if(i<n)
		i=avlArtBytes_TopN(avl->right, top, i, n);
	if(i<n)
		top[i++]=((artNodo)avl->artigo)->title_ID;
	if(i<n)
		i=avlArtBytes_TopN(avl->left, top, i, n);
	return i;
}

avlArtBytes avlArtBytes_Remove(avlArtBytes p, artNodo n)
{
	if ( !p )
		return NULL;

	if ( n->n_bytes < ((artNodo) p->artigo)->n_bytes)
		p->left = avlArtBytes_Remove(p->left, n);
	else if ( n->n_bytes > ((artNodo) p->artigo)->n_bytes )
		p->right = avlArtBytes_Remove(p->right, n);
	else if (((artNodo) p->artigo)->title_ID == n->title_ID)
	{
		avlArtBytes l = p->left;
		avlArtBytes r = p->right;
		free(p);

		if ( r == NULL )
			return l;

		avlArtBytes m = find_min(r);
		m->right = remove_min(r);
		m->left = l;

		return balance(m);
	}

	return balance(p);
}

void avlArtBytes_Print(avlArtBytes p){
	if(p){
		avlArtBytes_Print(p->left);
		printf("Title: %s; n_bytes: %d\n", ((artNodo) p->artigo)->title, ((artNodo) p->artigo)->n_bytes);
		avlArtBytes_Print(p->right);
	}
	return;
}

/* Funções referentes à avlArtWords */

avlArtWords avlArtWords_Insert(avlArtWords p, artNodo n)
{
	if ( !p )
		return new_AVL(n);

	if (((artNodo) p->artigo)->title_ID == n->title_ID)
		p->artigo = n;
	else{ 
		if(n->n_words == ((artNodo) p->artigo)->n_words){
			if(n->title_ID < ((artNodo) p->artigo)->title_ID){
				artNodo aux = p->artigo;
				p->artigo = n;
				n = aux;
			}
			p->left = avlArtWords_Insert(p->left, n);
		}
		else if( n->n_words > ((artNodo) p->artigo)->n_words )
			p->right = avlArtWords_Insert(p->right, n);
		else
			p->left = avlArtWords_Insert(p->left, n);
	}
	return balance(p);
}

int avlArtWords_TopN(avlArtWords avl, long* top, int i, int n){

	if(!avl) return i;
	if(i<n)
		i=avlArtWords_TopN(avl->right, top, i, n);
	if(i<n)
		top[i++]=((artNodo)avl->artigo)->title_ID;
	if(i<n)
		i=avlArtWords_TopN(avl->left, top, i, n);
	return i;
}

avlArtWords avlArtWords_Remove(avlArtWords p, artNodo n)
{
	if ( !p )
		return NULL;

	if ( n->n_words < ((artNodo) p->artigo)->n_words)
		p->left = avlArtWords_Remove(p->left, n);
	else if ( n->n_words > ((artNodo) p->artigo)->n_words )
		p->right = avlArtWords_Remove(p->right, n);
	else if (((artNodo) p->artigo)->title_ID == n->title_ID)
	{
		avlArtWords l = p->left;
		avlArtWords r = p->right;
		free(p);

		if ( r == NULL )
			return l;

		avlArtWords m = find_min(r);
		m->right = remove_min(r);
		m->left = l;

		return balance(m);
	}

	return balance(p);
}

void avlArtWords_Print(avlArtWords p){
	if(p){
		avlArtWords_Print(p->left);
		printf("Title: %s; n_words: %d\n", ((artNodo) p->artigo)->title, ((artNodo) p->artigo)->n_words);
		avlArtWords_Print(p->right);
	}
	return;
}

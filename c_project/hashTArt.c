#include "hashTArt.h"
#include "avl.h"

/* Funções referentes à hashTArt */

int hashCode (long title_ID){
	return (title_ID % SIZE);
} 

void hashTArt_Init (hashTArt h){
	for(int i = 0; i < SIZE; i++){
		h[i] = NULL;
	}
}

int hashTArt_Add (hashTArt h, char* title, long title_ID, int n_bytes, int n_words, long revision_id, char* timestamp, avlArtWords *avlWords){
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
		new->revisions = NULL;
		new-> next = NULL;
		if(!h[pos])
			h[pos] = new;
		else
			ant->next = new;

		aux = new;
	}
	else {
		free(aux->title);
		aux-> title = strdup (title);

		if (aux->n_bytes < n_bytes) aux->n_bytes = n_bytes;
		if (aux->n_words < n_words) aux->n_words = n_words;
	}

	res += insertRevision(&(aux->revisions), revision_id, timestamp);

	return res;
}

char *hashTArt_GetTitle (hashTArt h, long title_ID){
	int pos = hashCode (title_ID);
	artNodo aux;
	for(aux = h[pos]; aux && aux->title_ID != title_ID; aux = aux-> next);
	if(aux)
		return (aux->title);

	return NULL;
}

int stringComparator (const void * a, const void * b ) {
	const char *pa = *(const char**)a;
	const char *pb = *(const char**)b;

	return strcmp(pa,pb);
}


char** hashTArt_Prefix (hashTArt h, char* prefix){
	int size = 30;
	char **result = malloc (size*sizeof(char*) );
	int ins_pos=0;

	int hash_pos;

	#pragma omp parallel for
	for (hash_pos = 0; hash_pos < SIZE; hash_pos++){
		artNodo aux;
		for (aux = h[hash_pos]; aux; aux = aux->next)
			if (!strncmp(prefix, aux->title, strlen(prefix))){
				if (ins_pos > (size * 0.8)){
					#pragma omp critical
					{
						size = size * 2;
						result = realloc(result, size * sizeof(char *));
					}
				}

				#pragma omp critical
				result[ins_pos++] =strdup (aux->title);
			}
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
			cleanRevisionList(aux->revisions);
			ant = aux;
			aux = aux->next;
			free(ant);
		}
		h[i] = NULL;
	}
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

avlArtWords avlArtWords_InsertALL(hashTArt ht, avlArtWords p){
	int i;
	for(i=0; i<SIZE; i++){
		artNodo aux;
		for(aux = ht[i]; aux; aux = aux->next)
			p = avlArtWords_Insert(p, aux);
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

LinkedList newNodeA (LinkedList l, artNodo a){
	LinkedList new = malloc(sizeof(struct llig));

	if(new){
		new->node = a;
		new->next = l;
	}
	return new;
}

void insertOrderedA(LinkedList* list, artNodo a){
	int i=0;
	while((*list) && i<20 &&((artNodo)(*list)->node)->n_bytes > a->n_bytes){
		list = &((*list)->next);
		i++;
	}
	if(i==20 && ((artNodo)(*list)->node)->n_bytes < a->n_bytes){
		*list = newNodeA(*list, a);
		(*list)->next = NULL;
	}
	else
		*list = newNodeA(*list, a);
}

void getTop20NodesA(hashTArt ht, LinkedList* list){
	artNodo aux;
	for(int i=0; i<SIZE; i++){
		for(aux = ht[i]; aux; aux=aux->next){
			insertOrderedA(list, aux);
		}
	}
}

long* getTop20A(LinkedList list){
	long* top20 = malloc(sizeof(long)*20);
	LinkedList aux;
	int i;
	for(aux=list, i=0; aux && i<20; aux=aux->next, i++){
		top20[i] = ((artNodo)aux->node)->title_ID;
	}
	return top20;
}

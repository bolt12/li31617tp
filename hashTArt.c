#include <string.h>
#include "hashTArt.h"
#include "avl.h"

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
int hashTArt_Add (hashTArt h, char* title, long title_ID, int n_bytes, int n_words, long revision_id, char* timestamp, avlArt *avl){
	int pos = hashCode (title_ID);
	artNodo ant, aux, new = NULL;
	int res = 0;
	for(aux = ant = h[pos]; aux && aux -> title_ID != title_ID; ant = aux, aux = aux-> next);
	if(!aux){
		res++;
		new = malloc (sizeof (struct hashtable));
		new-> title = malloc (strlen(title)+1);
		strcpy (new-> title, title);
		new-> title_ID = title_ID;
		new-> n_bytes = n_bytes;
		new-> n_words = n_words;
		new-> revisions = NULL;
		new-> next = NULL;
		if(!h[pos]){
			h[pos] = new;
			*avl = avlArt_Insert(*avl,new);
		}
		else{
			ant->next = new;
			*avl = avlArt_Insert(*avl,new);
		}
		aux = new;
	}
	else{
		*avl=avlArt_Remove(*avl,aux);
		free(aux->title);
		aux-> title = malloc (strlen(title)+1);
		strcpy (aux-> title, title);
		aux->n_bytes=n_bytes;
		aux->n_words=n_words;

		*avl=avlArt_Insert(*avl, aux);
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

char** hashTArt_Prefix (hashTArt h, char* prefix){
	int size = 20;
	char **result = calloc (size, sizeof(char*) );
	int j,i, k = 0;

	artNodo aux;
	for (i = 0; i < SIZE; i++)
		for (aux = h[i]; aux; aux = aux->next)
			if (! strncmp (prefix, aux-> title, strlen (prefix) )){
				for (j = 0; result[j] != NULL && strcmp (aux->title, result[j]); j++);
				if (result[j] == NULL){
					if (k > size * 0.7){
						size = size * 2;
						result = realloc (result, size * sizeof(char *));
						for (j=k+1; j < size; j++) *(result+j) = NULL;
					}

					*(result+k) = malloc ((strlen (aux->title)) +1);
					strcpy ( *(result+k) , aux->title);
					k++;
				}
			}
		
	return result;
}

char* hashTArt_Timestamp (hashTArt h, long title_ID, long revision_id){
	int pos = hashCode (title_ID);
	artNodo aux;
	for(aux = h[pos]; aux && aux->title_ID != title_ID; aux = aux-> next);
	if(aux)
		return (retrieveTimestamp(aux->revisions, revision_id));

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

/* Funções referentes à avlArt */

avlArt avlArt_Insert(avlArt p, artNodo n)
{
	if ( !p )
		return new_AVL(n);

	if ( n -> n_bytes < ((artNodo) p->artigo)-> n_bytes)
		p->left = avlArt_Insert(p->left, n);
	else if ( n->n_bytes > ((artNodo) p->artigo)->n_bytes )
		p->right = avlArt_Insert(p->right, n);
	else if (((artNodo) p->artigo)->title_ID == n->title_ID)
		p->artigo = n;

	return balance(p);
}

int avlArt_TopN(avlArt avl, long* top, int i, int n){
	if(!avl) return i;
	if(i<n)
		i=avlArt_TopN(avl->right, top, i, n);
	if(i<n)
		top[i++]=((artNodo)avl->artigo)->title_ID;
	if(i<n)
		i=avlArt_TopN(avl->left, top, i, n);
	return i;
}

avlArt avlArt_Remove(avlArt p, artNodo n)
{
	if ( !p )
		return NULL;

	if ( n->n_bytes < ((artNodo) p->artigo)->n_bytes)
		p->left = avlArt_Remove(p->left, n);
	else if ( n->n_bytes > ((artNodo) p->artigo)->n_bytes )
		p->right = avlArt_Remove(p->right, n);
	else if (((artNodo) p->artigo)->title_ID == n->title_ID)
	{
		avlArt l = p->left;
		avlArt r = p->right;
		free(p);

		if ( r == NULL )
			return l;

		avlArt m = find_min(r);
		m->right = remove_min(r);
		m->left = l;

		return balance(m);
	}

	return balance(p);
}

void avlArt_Print(avlArt p){
	if(p){
		avlArt_Print(p->left);
		printf("Title: %s; n_bytes: %d\n", ((artNodo) p->artigo)->title, ((artNodo) p->artigo)->n_bytes);
		avlArt_Print(p->right);
	}
	return;
}

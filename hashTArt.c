#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hashTArt.h"
#include "linkedListRevisions.h"


// ****************** ELIMINAR ***************************** //
typedef struct hashtable{
	char * title;
	long title_ID;
	int n_bytes;
	int n_words;
	int heapInd; // -1 se não estiver na heap;
	struct revisionsList * revisions;
	struct hashtable * next;	
}*hashTArt[SIZE], artNodo;
//*************************************************************



int hashCode (long title_ID){
	return (title_ID % HSIZE);
} 

void hashArtInit (hashTArt h){
	int i;
	for (i = 0; i < SIZE; i++){
		h[i] = NULL;
	}
}

/*
	Se res == 0 -> Não foi adicionado nenhum artigo nem nenhuma revisão
	Se res == 1 -> Foi adicionada apenas uma revisão
	Se res == 2 -> Foi adicionada um novo artigo (consequentemente uma nova revisão)
*/
int hashTArt_Add (hashTArt h, char* title, long title_ID, int n_bytes, int n_words, long revision_id, char* timestamp
					 char * contributor_name, long contributor_id, maxHeapArt mh){
	int pos = hashCode (title_ID);
	artNodo aux, new = NULL;
	int res = 0;

	for (aux = h[pos]; aux && aux -> title_ID != title_ID; aux = aux-> next);
	if (!aux){
		res++;
		new = malloc sizeof (struct hashtable);
		new-> title = malloc (sizeof (title));
		strcpy (new-> title, title);
		new-> title_ID = title_ID;
		new-> n_bytes = n_bytes;
		new-> n_words = n_words;
		new-> revisions = NULL;
		new-> next = aux;
		aux = new;
	}

	res += insertRevision(aux->revisions, revision_id, timestamp);
	if (res) aux-> heapInd = maxHeapArt_Insert(maxHeapArt mh, aux);

	return res;
}


char *hashTArt_GetTitle (hashTArt h, long title_ID){
	int pos = hashCode (title_ID);
	artNodo aux;
	for (aux = h[pos]; aux && aux -> title_ID != title_ID; aux = aux-> next);
	if (aux) return (aux-> title);
	return NULL;
}

char** hashTArt_Prefix (hashTArt h, char * prexix){
	return NULL;
}


char* hashTArt_Timestamp (hashTArt h, long title_ID, long revision_id){
	int pos = hashCode (title_ID);
	artNodo aux;
	for (aux = h[pos]; aux && aux -> title_ID != title_ID; aux = aux-> next);
		if (aux){
			return (retrieveTimestamp(aux->revisions, revision_id) );
		}
	return NULL;
}


void hashTArt_Clean (hashTArt h){
	int i;
	artNodo aux, ant;
	for (i = 0; i < SIZE; i++){
		aux = h[i];
		while (aux){
			free (aux-> title);
			cleanList(aux-> revisions);
			ant = aux;
			aux = aux->next
			free(ant)
		}
		h[i] = NULL;
	}
}


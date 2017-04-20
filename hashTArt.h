#ifndef __HASHTART__H__
#define __HASHTART__H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linkedListRevisions.h"
#include "avl.h"

#define SIZE 19889 // Número primo mais baixo e mais próximo de 19886, número de revisões únicas

typedef struct hashtable{
	char * title;
	long title_ID;
	int n_bytes;
	int n_words;
	int heapInd;
	Revisions revisions;
	struct hashtable * next;	
}*hashTArt[SIZE], *artNodo;

/* Funções referentes a hashTArt */

int hashCode (long title_ID);
void hashTArt_Init (hashTArt h);
int hashTArt_Add (hashTArt h, char* title, long title_ID, int n_bytes, 
		int n_words, long revision_id, char* timestamp, avlArtBytes *avlBytes, avlArtWords *avlWords);
char* hashTArt_GetTitle (hashTArt h, long article_id);
char** hashTArt_Prefix (hashTArt h, char* prefix);
char* hashTArt_Timestamp (hashTArt h, long article_id, long revision_id);
void hashTArt_Clean (hashTArt h);
void hashTArt_Print(hashTArt h);

/* Funções referentes a avlArtBytes */

avlArtBytes avlArtBytes_Insert(avlArtBytes avl, artNodo n);
avlArtBytes avlArtBytes_Remove(avlArtBytes avl, artNodo n);
int avlArtBytes_TopN(avlArtBytes avl, long* top, int i, int n);
void avlArtBytes_Print(avlArtBytes avl);

/* Funções referentes a avlArtWords */

avlArtWords avlArtWords_Insert(avlArtWords avl, artNodo n);
avlArtWords avlArtWords_Remove(avlArtWords avl, artNodo n);
int avlArtWords_TopN(avlArtWords avl, long* top, int i, int n);
void avlArtWords_Print(avlArtWords avl);

#endif

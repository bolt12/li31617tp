#ifndef __HASHTART__H__
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linkedListRevisions.h"
//#include "maxHeapArt.h"
#endif


/*	ATENCAO : NOTAS IMPORTANTES -> Alterar !!!!
	Para testar:
	---> maxHeap substituida por Int 
	---> SIZE definido como 10

*/
#define SIZE 19889 // Número primo mais baixo e mais próximo de 19886, número de revisões únicas
//#define SIZE 10 

typedef struct hashtable{
	char * title;
	long title_ID;
	int n_bytes;
	int n_words;
	int heapInd;
	Revisions revisions;
	struct hashtable * next;	
}*hashTArt[SIZE], *artNodo;

typedef struct avlart{
	artNodo artigo;
	int height;
	struct avlart *left;
	struct avlart *right;
} *avlArt;

/* Funções referentes a hashTArt */

int hashCode (long title_ID);
void hashTArt_Init (hashTArt h);
int hashTArt_Add (hashTArt h, char* title, long title_ID, int n_bytes, 
		int n_words, long revision_id, char* timestamp,
		char* contributor_name, long contributor_id, avlArt *avl);
char* hashTArt_GetTitle (hashTArt h, long article_id);
char** hashTArt_Prefix (hashTArt h, char* prefix);
char* hashTArt_Timestamp (hashTArt h, long article_id, long revision_id);
void hashTArt_Clean (hashTArt h);
void hashTArt_Print(hashTArt h);

/* Funções referentes a avlArt */

avlArt avlArt_Init(avlArt avl);
avlArt avlArt_Insert(avlArt avl, artNodo n);
avlArt avlArt_Remove(avlArt avl, artNodo n);
long* avlArt_Top10(avlArt avl);
long* avlArt_TopNW(avlArt avl);
void avlArt_Print(avlArt avl);
void avlArt_Clean(avlArt avl);

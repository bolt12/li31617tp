#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linkedListRevisions.h"

#define SIZE 19889 // Número primo mais baixo e mais próximo de 19886, número de revisões únicas

typedef struct hashtable{
	char * title;
	long title_ID;
	int n_bytes;
	int n_words;
	int heapInd; // -1 se não estiver na heap;
	struct revisionsList * revisions;
	struct hashtable * next;	
}*hashTArt[SIZE], artNodo;


int hashCode (long title_ID);
void hashTArt_Init (hashTArt h);
int hashTArt_Add (hashTArt h, char* title, long title_ID, int n_bytes, 
					int n_words, long revision_id, char* timestamp,
		 			char * contributor_name, long contributor_id, maxHeapArt mh);
char* hashTArt_GetTitle (hashTArt h, long article_id);
char** hashTArt_Prefix (hashTArt h, char * prefix);
char* hashTArt_Timestamp (hashTArt h, long article_id, long revision_id);
void hashTArt_Clean (hashTArt h);

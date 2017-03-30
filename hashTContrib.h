#ifndef __HASHTCONTRIB__H__
#define __HASHTCONTRIB__H__
#include <stdlib.h>
#include <stdio.h>

#define SIZE 19889

typedef struct hashtablecontrib{
	char* contributor_name;
	long contributor_id;
	int contributions_number;
	struct hashtablecontrib *next;
} *Contrib, *hashTContrib[SIZE] ;

typedef struct avl *avlContrib;

//int hashTContribAdd(hashTContrib ht, maxHeapContrib hpContrib, char* contributor_name, long contributor_id);
void hashTContribInit(hashTContrib ht);
int hashTContribAdd(hashTContrib ht, char* contributor_name, long contributor_id);
int hashTContribHash(long contributor_id);
char* hashTContribRetrieveName(hashTContrib ht, long contributor_id);
int hashTContribRetrieveContributions(hashTContrib ht, long contributor_id);
void hashTContribClean(hashTContrib ht);

/* Funções referentes à avlcontrib */

avlContrib avlContrib_Insert(avlContrib avl, Contrib n);
avlContrib avlContrib_Remove(avlContrib avl, Contrib n);
long* avlContrib_Top10(avlContrib avl);
long* avlContrib_TopNW(avlContrib avl);
void avlContrib_Print(avlContrib avl);
void avlContrib_Clean(avlContrib avl);

#endif

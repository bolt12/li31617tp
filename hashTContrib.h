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

void hashTContribInit(hashTContrib ht);
int hashTContribAdd(hashTContrib ht, char* contributor_name, long contributor_id);
int hashTContribHash(long contributor_id);
char* hashTContribRetrieveName(hashTContrib ht, long contributor_id);
int hashTContribRetrieveContributions(hashTContrib ht, long contributor_id);
void hashTContribClean(hashTContrib ht);

void getTop10NodesC(hashTContrib, LinkedList*);
long* getTop10C(LinkedList list);
#endif


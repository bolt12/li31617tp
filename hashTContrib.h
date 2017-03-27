#ifndef __HASHTCONTRIB__H__
#include <stdlib.h>
#include <stdio.h>
//#include "maxHeapContrib.h"
#endif

#define SIZE 19889

typedef struct hashtablecontrib
{
	char* contributor_name;
	long contributor_id;
	int contributions_number;
	int heapInd;
	struct hashtablecontrib *next;
} Contrib, *hashTContrib[SIZE] ;

//int hashTContribAdd(hashTContrib ht, maxHeapContrib hpContrib, char* contributor_name, long contributor_id);
void hashTContribInit(hashTContrib ht);
int hashTContribAdd(hashTContrib ht, char* contributor_name, long contributor_id);
int hashTContribHash(long contributor_id);
char* hashTContribRetrieveName(hashTContrib ht, long contributor_id);
int hashTContribRetrieveContributions(hashTContrib ht, long contributor_id);
void hashTContribClean(hashTContrib ht);

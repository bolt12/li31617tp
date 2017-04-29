#ifndef __LINKEDLIST__H__
#define __LINKEDLIST__H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct revision{
	long revision_id;
	char* revision_timestamp;
} *Revision;

typedef struct llig{
	void *node;
	struct llig *next;
} *LinkedList;

int insertRevision(LinkedList*, long, char*);
char* retrieveTimestamp(LinkedList, long);
long getRevisionId(Revision);
void cleanList(LinkedList);
void cleanRevisionList(LinkedList);

#endif

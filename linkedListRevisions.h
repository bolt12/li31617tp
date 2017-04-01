#ifndef __LINKEDLIST__H__
#define __LINKEDLIST__H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct revisionsList{
	long revision_id;
	char* revision_timestamp;
	struct revisionsList *next;
} *Revisions;

int insertRevision(Revisions*, long, char*);
void cleanList(Revisions*);
char* retrieveTimestamp(Revisions, long);

#endif

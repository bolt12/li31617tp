#ifndef __LINKEDLIST__H__
#define __LINKEDLIST__H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct revision *Revision;

typedef struct llig *LinkedList;

int insertRevision(LinkedList*, long, char*);
char* retrieveTimestamp(LinkedList, long);
long getRevisionId(Revision);
void cleanList(LinkedList);
void cleanRevisionList(LinkedList);

#endif

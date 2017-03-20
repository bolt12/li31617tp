#include <stdlib.h>

typedef struct revisionsList{
	long revision_id;
	char* revision_timestamp;
	struct revisionsList *next;
} *Revisions;

int insertRevision(Revisions*, long, char*);
void cleanList(Revisions*);
char* retrieveTimestamp(Revisions, long);
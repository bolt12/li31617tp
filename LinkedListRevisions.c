#include "LinkedListRevisions.h"

int insertRevision(Revisions* list, long revision_id, char* revision_timestamp){
	Revisions new;

	new = malloc(sizeof(struct revisionsList));
	new->revision_id = revision_id;
	new->revision_timestamp = revision_timestamp;
	new->next = NULL;

	if(!(*list)){
		*list = new;
	} else{
		if((*list)->revision_id == revision_id)
			return 0;
		else{
			new->next = (*list);
			*list = new;
		}
	}
	return 1;
}

void cleanList(Revisions* list){
	Revisions next;

	while(*list){
		next = (*list)->next;
		free(*list);
		*list = next;
	}
}

char* retrieveTimestamp(Revisions list, long revision_id){
	Revisions head = list;

	while(head){
		if(head->revision_id == revision_id)
			return head->revision_timestamp;
		else
			head = head->next;
	}

	return NULL;
}

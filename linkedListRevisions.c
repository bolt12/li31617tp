#include "linkedListRevisions.h"

int insertRevision(Revisions* list, long revision_id, char* revision_timestamp){
	Revisions new;

	new = malloc(sizeof(struct revisionsList));
	new->revision_id = revision_id;
	new->revision_timestamp = strdup(revision_timestamp);
	new->next = NULL;

	if(!(*list)){
		*list = new;
	} else{
		if((*list)->revision_id == revision_id){
			free(new->revision_timestamp);
			free(new);
			return 0;
		}
		else{
			new->next = (*list);
			*list = new;
		}
	}
	return 1;
}

void cleanList(Revisions* list){
	Revisions aux;

	while(*list){
		aux = *list;
		*list = (*list)->next;
		free(aux);
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

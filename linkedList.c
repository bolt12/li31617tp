#include "linkedList.h"

struct revision{
	long revision_id;
	char* revision_timestamp;
};

struct llig{
	void *node;
	struct llig *next;
};

Revision createRevision (long revision_id, char* timestamp){
	Revision new = malloc(sizeof(struct revision));
	new->revision_id = revision_id;
	new->revision_timestamp = strdup(timestamp);
	return new;

}

void freeRevision(Revision revision){
	 free(revision->revision_timestamp);
	 free(revision);
}

int insertRevision(LinkedList* list, long revision_id, char* timestamp){
	Revision newRevision = createRevision(revision_id,timestamp);
	Revision listHead;
	LinkedList newList = malloc(sizeof(struct llig));
	newList->node = newRevision;
	newList->next = NULL;

	if(!(*list)){
		*list = newList;
	} else{
		listHead = ((Revision)(*list)->node);
		if(listHead->revision_id == revision_id){

			freeRevision(newRevision);
			free(newList);
			return 0;
		}
		else{
			newList->next = (*list);
			*list = newList;
		}
	}
	return 1;
}
char* retrieveTimestamp(LinkedList list, long revision_id){
	LinkedList head = list;
	Revision revisionNode;

	while(head){
		revisionNode = (Revision) (head->node);
		if(revisionNode->revision_id == revision_id)
			return revisionNode->revision_timestamp;
		else
			head = head->next;
	}
	return NULL;
}
void cleanList(LinkedList list){
	LinkedList aux;

	while(list){
		aux = list;
		list = list->next;
		free(aux);
	}
}
void cleanRevisionList(LinkedList list){
	LinkedList aux;

	while(list){
		aux = list;
		freeRevision((Revision)(list->node));
		list = list->next;
		free(aux);
	}
}



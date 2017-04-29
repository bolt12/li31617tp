#include "string.h"
#include "linkedListRevisions.h"
#include "hashTContrib.h"
#include "avl.h"

int hashTContribHash(long contributor_id){
	return (contributor_id % SIZE);
}

void hashTContribInit(hashTContrib ht){
	int i;
	for (i = 0; i < SIZE; i++){
		ht[i] = NULL;
	}
}

int hashTContribAdd(hashTContrib h, char* contributor_name, long contributor_id){
	int pos = hashTContribHash(contributor_id);

	Contrib ant, aux, new = NULL;

	for(aux = ant = h[pos]; aux && aux -> contributor_id != contributor_id; ant = aux, aux = aux-> next);
	if(!aux){
		new = malloc (sizeof (struct hashtablecontrib));
		new->contributor_name = strdup(contributor_name);
		new->contributor_id = contributor_id;
		new->contributions_number=1;
		new->next = NULL;
		if(!h[pos]){
			h[pos] = new;
		}
		else{
			ant->next = new;
		}
		return 1;
	}
	else{
		(aux->contributions_number)+=1;
		return 1;
	}
	return 0;
}

char* hashTContribRetrieveName(hashTContrib ht, long contributor_id){
	int position = hashTContribHash(contributor_id);
	Contrib head = ht[position];
	while(head){
		if(head->contributor_id == contributor_id)
			return head->contributor_name;
		head = head->next;
	}
	return NULL;
}

int hashTContribRetrieveContributions(hashTContrib ht, long contributor_id){
	int position = hashTContribHash(contributor_id);
	Contrib head = ht[position];
	while(head){
		if(head->contributor_id == contributor_id)
			return head->contributions_number;
		head = head->next;
	}
	return -1;
}
void hashTContribClean(hashTContrib ht){
	int indice;
	Contrib ant, prox;
	for(indice = 0; indice < SIZE; indice++){
		prox = ht[indice];
		while(prox){
			ant = prox;
			free(ant->contributor_name);
			prox = prox->next;
			free(ant);
		}
		ht[indice] = NULL;
	}
}

LLig newNodeC (LLig l, Contrib c){
	LLig new = malloc(sizeof(struct llig));

	if(new){
		new->node = c;
		new->next = l;
	}
	return new;
}

void insertOrderedC(LLig* list, Contrib c){
	while((*list!=NULL) && ((Contrib)(*list)->node)->contributions_number > c->contributions_number)
		list = &((*list)->next);
	*list = newNodeC(*list, c);
}

void getTop10NodesC(hashTContrib ht, LLig* list){
	int i;
	for(i=0; i<SIZE; i++){
		Contrib aux;
		for(aux = ht[i]; aux; aux=aux->next){
			insertOrderedC(list, aux);
		}
	}
}

long* getTop10C(LLig list){
	long* top10 = calloc(sizeof(long),10);
	LLig aux;
	int i;
	for(aux=list, i=0; aux && i<10; aux=aux->next, i++){
		top10[i] = ((Contrib)aux->node)->contributor_id;
	}
	return top10;
}

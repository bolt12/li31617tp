#include "hashTContrib.h"
/*
1-Criar e implemetar hashtable de contribuidores
2-Criar e implemetar maxheap de contribuidores
3-juntar ambas as estruturas
4-criar testes
5-implementar queries relacionadas com contribuidores
*/

int hashTContribHash(long contributor_id){
	return contributor_id % SIZE;
}
int hashTContribAdd(hashTContrib ht, char* contributor_name, long contributor_id){
	int position = hashTContribHash(contributor_id);
	//Vou usar um apontador de apontador para poupar uma variável.
	Contrib **head = &ht[position];
	while(*head){
		if((*head)->contributor_id == contributor_id){ // se o contribuidor já estiver guardado
			((*head)->contributions_number)++;
			return 0;
		}
		head = &((*head)->next);
	}
	if(!(*head)){
		Contrib *new = malloc(sizeof(struct hashtablecontrib));
		new->contributor_id = contributor_id;
		new->contributor_name = contributor_name;
		new->contributions_number = 1;
		*head = new;
	}
	return 1;

}
char* hashTContribRetrieveName(hashTContrib ht, long contributor_id){
	int position = hashTContribHash(contributor_id);
	Contrib *head = ht[position];
	while(head){
		if(head->contributor_id == contributor_id)
			return head->contributor_name;
		head = head->next;
	}
	return NULL;
}
int hashTContribRetrieveContributions(hashTContrib ht, long contributor_id){
	int position = hashTContribHash(contributor_id);
	Contrib *head = ht[position];
	while(head){
		if(head->contributor_id == contributor_id)
			return head->contributions_number;
		head = head->next;
	}
	return -1;
}
void hashTContribClean(hashTContrib ht){
	int indice;
	Contrib *head, *next;
	for(indice = 0; indice < SIZE; indice++){
		next = ht[indice];
		//printf("%d\n", indice);
		while(next){
			printf("Eliminar %s\n", next->contributor_name);
			head = next;
			next = next->next;
			free(head);
		}
	}
}
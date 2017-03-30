#include "hashTContrib.h"
#include "avl.h"

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

void hashTContribInit(hashTContrib ht){
	int i;
	for (i = 0; i < SIZE; i++){
		ht[i] = NULL;
	}
}

int hashTContribAdd(hashTContrib ht, char* contributor_name, long contributor_id){
	if(contributor_name || contributor_id){
		int position = hashTContribHash(contributor_id);
		//Vou usar um apontador de apontador para poupar uma variável.
		Contrib *head = &ht[position];
		while(*head){
			if((*head)->contributor_id == contributor_id){ // se o contribuidor já estiver guardado
				((*head)->contributions_number)++;
				return 0;
			}
			head = &((*head)->next);
		}
		if(!(*head)){
			Contrib new = malloc(sizeof(struct hashtablecontrib));
			new->contributor_id = contributor_id;
			new->contributor_name = contributor_name;
			new->contributions_number = 1;
			*head = new;
		}
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
		//printf("%d\n", indice);
		while(prox){
			ant = prox;
			prox = prox->next;
			free(ant);
		}
		ht[indice] = NULL;
	}
}

/* Funções referentes à avlContrib */

avlContrib avlContrib_Insert(avlContrib p, Contrib n)
{
	if ( !p )
		return new_AVL(n);

	if ( n ->contributions_number < ((Contrib) p->artigo)->contributions_number)
		p->left = avlContrib_Insert(p->left, n);
	else if ( n->contributions_number > ((Contrib) p->artigo)->contributions_number )
		p->right = avlContrib_Insert(p->right, n);
	else if (((Contrib) p->artigo)->contributor_id == n->contributor_id)
		p->artigo = n;

	return balance(p);
}

avlContrib avlContrib_Remove(avlContrib p, Contrib n)
{
	if ( !p )
		return NULL;

	if ( n->contributions_number < ((Contrib) p->artigo)->contributions_number)
		p->left = avlContrib_Remove(p->left, n);
	else if ( n->contributions_number > ((Contrib) p->artigo)->contributions_number )
		p->right = avlContrib_Remove(p->right, n);
	else if (((Contrib) p->artigo)->contributor_id == n->contributor_id)
	{
		avlContrib l = p->left;
		avlContrib r = p->right;
		free(p);

		if ( r == NULL )
			return l;

		avlContrib m = find_min(r);
		m->right = remove_min(r);
		m->left = l;

		return balance(m);
	}

	return balance(p);
}

long* avlContrib_Top10(avlContrib avl){
	long* top = malloc(sizeof(long)*10);
	int i=9;
	while(avl && i>=0){
		top[i--] =  ((Contrib) avl->artigo)->contributor_id;
		avl=avl->right;
	}
	return top;
}

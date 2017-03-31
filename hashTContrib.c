#include "string.h"
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

int hashTContribAdd(hashTContrib h, char* contributor_name, long contributor_id, avlContrib *avl){
	int pos = hashTContribHash(contributor_id);

	Contrib ant, aux, new = NULL;

	for(aux = ant = h[pos]; aux && aux -> contributor_id != contributor_id; ant = aux, aux = aux-> next);
	if(!aux){
		new = malloc (sizeof (struct hashtablecontrib));
		new->contributor_name = malloc (strlen(contributor_name)+1);
		strcpy (new-> contributor_name, contributor_name);
		new-> contributor_id = contributor_id;
		new->contributions_number=1;
		new-> next = NULL;
		if(!h[pos]){
			h[pos] = new;
			*avl = avlContrib_Insert(*avl,new);
		}
		else{
			ant->next = new;
			*avl = avlContrib_Insert(*avl,new);
		}
		aux = new;
		return 1;
	}
	else{
		*avl=avlContrib_Remove(*avl,aux);
		(aux->contributions_number)+=1;
		*avl=avlContrib_Insert(*avl, aux);
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

	if (((Contrib) p->artigo)->contributor_id == n->contributor_id)
		p->artigo = n;
	else{
	       	if ( n->contributions_number > ((Contrib) p->artigo)->contributions_number)
			p->right = avlContrib_Insert(p->right, n);
		else 
			p->left = avlContrib_Insert(p->left, n);
	}

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

void avlContrib_TopN(avlContrib avl, long* top, int n){
	if(!avl) return;
	printf("%s, %d, %d\n", ((Contrib)avl->artigo)->contributor_name, ((Contrib)avl->artigo)->contributions_number, n);
	avlContrib_TopN(avl->right, top, --n);
	if(n<10){
		top[n] =((Contrib) avl->artigo)->contributor_id;
	}
}

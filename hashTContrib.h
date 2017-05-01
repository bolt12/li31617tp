#ifndef __HASHTCONTRIB__H__
#define __HASHTCONTRIB__H__
#include <stdlib.h>
#include <stdio.h>

#define SIZE 19889

typedef struct hashtablecontrib{
	char* contributor_name;		/**<! Nome do contribuidor */
	long contributor_id;		/**<! ID do contribuidor */
	int contributions_number;	/**<! Número de contribuições */
	struct hashtablecontrib *next;
} *Contrib, *hashTContrib[SIZE] ;

/**
*\brief Inicializa a Tabela de Hash
*@param h Tabela de hash
* 
*/
void hashTContribInit(hashTContrib ht);
/**
*\brief Insere informação de um contribuidor na tabela de Hash
		 ou atualiza número das suas contribuições caso já exista.
*@param ht Tabela de hash
*@param contributor_name Nome do contribuidor
*@param contributor_id ID do contribuidor
*/
int hashTContribAdd(hashTContrib ht, char* contributor_name, long contributor_id);
/**
*\brief Devolve o hashCode com base no ID de contribuidor
*@param contributor_id ID do contribuidor
*@return hashCode
*/
int hashTContribHash(long contributor_id);
/**
*\brief Procura o nome de um contribuidor com base no seu ID
*@param ht Tabela de Hash
*@param contributor_id ID do contribuidor
*@return String com o nome
* 
*/
char* hashTContribRetrieveName(hashTContrib ht, long contributor_id);
/**
*\brief Devolve o número de contribuições de um determinado contribuidor com base no seu ID
*@param ht Tabela de Hash
*@param contributor_id ID do contribuidor
*@return Número de contribuições
* 
*/
int hashTContribRetrieveContributions(hashTContrib ht, long contributor_id);
/**
*\brief Limpa a tabela de Hash
*@param ht Tabela de Hash
*/
void hashTContribClean(hashTContrib ht);
/**
*\brief Coloca numa lista ligada os nodos com os 10 contribuidores com mais contribuições
*@param[in] ht Tabela de Hash
*@param[out] list Lista ligada
*/
void getTop10NodesC(hashTContrib ht, LinkedList* list);
/**
*\brief Converte a lista ligada num array com o ID dos 10 contribuidores com mais contribuições
*@param list Lista ligada
*@return Array com ID dos top10 contribuidores
*/
long* getTop10C(LinkedList list);
#endif


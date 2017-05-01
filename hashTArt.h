#ifndef __HASHTART__H__
#define __HASHTART__H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linkedListRevisions.h"
#include "avl.h"

#define SIZE 19889 // Número primo mais baixo e mais próximo de 19886, número de revisões únicas

typedef struct hashtable{
	char * title; 	/*!< Titulo do artigo */ 
	long title_ID;	/*!< ID do artigo */ 
	int n_bytes;	/*!< Número de bytes de um artigo */
	int n_words;	/*!< Número de palavras de um artigo */
	LinkedList revisions;	/*!< Lista ligada de revisões de um artigo */
	struct hashtable * next;	
}*hashTArt[SIZE], *artNodo;

/* Funções referentes a hashTArt */

/**
 *
*\brief Devolve o hashCode com base no ID de um artigo
*@param title_ID ID do título
*@return hashCode  
*/
int hashCode (long title_ID);

/**
*\brief Inicializa a Tabela de Hash
*@param h Tabela de Hash
* 
*/
void hashTArt_Init (hashTArt h);

/**
*\brief Insere informação de um artigo na tabela de Hash
*@param h Tabela de Hash
*@param title Título do artigo
*@param title_ID ID do artigo
*@param n_bytes Número de bytes do artigo
*@param n_words Número de palavras 
*@param revision_id Id da revisão
*@param timestamp Data da revisão
*@param avlWords AVL ordenada pelo número de palavras
*@return Código de inserção (0 => nada de novo; 1 => Nova Revisão; 2 => Novo Artigo e Revisão)
* 
*/
int hashTArt_Add (hashTArt h, char* title, long title_ID, int n_bytes, 
		int n_words, long revision_id, char* timestamp, avlArtWords *avlWords);
/**
*\brief Procura o título correspondente a um determinado ID
*@param h Tabela de Hash
*@param article_id ID do artigo
*@return String com o título
* 
*/
char* hashTArt_GetTitle (hashTArt h, long article_id);
/**
*\brief Procura todos os títulos com um determinado prefixo
*@param h Tabela de Hash
*@param prefix Prefixo a ser procurado
*@return Lista de Strings com os títulos com o prefixo ordenados lexicograficamente
* 
*/
char** hashTArt_Prefix (hashTArt h, char* prefix);
/**
*\brief Procura a data correspondente a uma determinada revisão
*@param h Tabela de Hash
*@param article_id Id do artigo a que a revisão pertence
*@param revision_id Id da revisão
*@return String com a data ou null caso não exista a revisão
*/
char* hashTArt_Timestamp (hashTArt h, long article_id, long revision_id);
/**
*\brief Limpa a tabela de Hash
*@param h Tabela de Hash
*/
void hashTArt_Clean (hashTArt h);

/* Funções referentes a avlArtWords */

/**
 *\brief Insere um artigo na AVL segundo o número de palavras deste
 *@param avl AVL onde vai ser inserido
 *@param n Nodo correspondente ao artigo
 *@return AVL resultante
*/
avlArtWords avlArtWords_Insert(avlArtWords avl, artNodo n);

/**
 *\brief Percorre uma tabela de Hash de artigos e insere-os todos na AVL
 *@param ht Tabela de Hash de artigos a percorrer
 *@param p AVL onde vão ser inseridos os artigos
 *@return AVL resultante
 */

avlArtWords avlArtWords_InsertALL(hashTArt ht, avlArtWords p);

/**
 *\brief Devolve por referência o top N de artigos com maior número de palavras.
 *@param avl AVL de procura
 *@param top Array onde vai ser devolvido o top N
 *@param i Onde começa a inserção no array
 *@param n Número de posições do top
 *@return AVL resultante
 */

int avlArtWords_TopN(avlArtWords avl, long* top, int i, int n);

/**
 *\brief Percorre uma tabela de Hash de artigos
 *	 e devolve por referencia uma lista ligada
 *	 com o top N de artigos com maior número de palavras
 *@param ht Tabela de Hash de procura
 *@param list Lista Ligada de artigos que conterá o top N
 *
 */

void getTop20NodesA(hashTArt ht, LinkedList* list);

/**
 *\brief Devolve em forma de array o uma lista ligada de artigos.
 *@param list Lista Ligada de artigos
 *@return Array com o top N
 */

long* getTop20A(LinkedList list);

#endif

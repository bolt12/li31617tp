#ifndef __LINKEDLIST__H__
#define __LINKEDLIST__H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct revision *Revision;

typedef struct llig *LinkedList;

/**
*\brief Insere uma revisão na lista ligada.
*@param list Lista ligada de revisões.
*@param revision_id ID da revisão
*@param timestamp Timestamp da revisão
*@return 0 => Revisão na cabeça da lista e revisão a inserir coincidem, logo não é inserida nenhuma revisão; 1 => Nova Revisão inserida
*/
int insertRevision(LinkedList* list, long revision_id, char* timestamp);
/**
*\brief Procura na lista pela revisão com um certo ID e devolve timestamp respetivo.
*@param list Lista ligada de revisões.
*@param revision_id ID da revisão
*@return Timestamp relativo ao ID de revisão, caso a pesquisa seja sucedida. Caso contrário, devolve NULL.
*/
char* retrieveTimestamp(LinkedList list, long revision_id);
/**
*\brief Liberta toda a memória alocada pela lista ligada.
*@param list Lista ligada de revisões.
*/
void cleanList(LinkedList);
/**
*\brief Liberta toda a memória alocada pela lista ligada.
*@param list Lista ligada de revisões.
*/
void cleanRevisionList(LinkedList);

#endif

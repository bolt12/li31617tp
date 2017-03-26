#include "interface.h"

void testes_hastTableContribuidores(){

	hashTContrib hash_teste;
	char * nome;
	int contribuicoes;

	if(hashTContribAdd(hash_teste, "Zeca", 312312512))
		printf("Adicionado o Zeca\n");
	else{
		printf("Atualizado o Zeca\n");
	}
	if(hashTContribAdd(hash_teste, "Miguel", 65413245))
		printf("Adicionado o Miguel\n");
	else{
		printf("Atualizado o Miguel\n");
	}
	if(hashTContribAdd(hash_teste, "Armando", 865742))
		printf("Adicionado o Armando\n");
	else{
		printf("Atualizado o Armando\n");
	}
	if(hashTContribAdd(hash_teste, "Luis", 987654567))
		printf("Adicionado o Luis\n");
	else{
		printf("Atualizado o Luis\n");
	}
	if(hashTContribAdd(hash_teste, "Armando", 865742))
		printf("Adicionado o Armando\n");
	else{
		printf("Atualizado o Armando\n");
	}

	nome = hashTContribRetrieveName(hash_teste,987654567);
	if(strcmp(nome, "Luis") == 0)
		printf("1º Teste de busca de nome passou\n");
	nome = hashTContribRetrieveName(hash_teste, 865742);
	if(strcmp(nome, "Armando") == 0)
		printf("2º Teste de busca de nome passou\n");
	nome = hashTContribRetrieveName(hash_teste, 8765987);
	if(nome == NULL)
		printf("3º Teste de busca de nome passou\n");

	contribuicoes = hashTContribRetrieveContributions(hash_teste, 865742);
		printf("O armando tem %i contribuições.\n", contribuicoes);
	contribuicoes = hashTContribRetrieveContributions(hash_teste, 987654567);
		printf("O luis tem %i contribuições\n", contribuicoes);

	hashTContribClean(hash_teste);
}

void testes_lista_revisoes(){

	Revisions lista = NULL;
	char* timestamp;

	if(insertRevision(&lista, 3445, "23Dec2015"))
		printf("Inserida revisão com id 3445, data 23Dec2015\n");
	if(insertRevision(&lista, 7654, "01Jan2015"))
		printf("Inserida revisão com id 7654, data 01Jan2015\n");
	if(insertRevision(&lista, 5456, "24Feb2015"))
		printf("Inserida revisão com id 5456, data 24Feb2015\n");
	if(insertRevision(&lista, 9874, "15Mar2017"))
		printf("Inserida revisão com id 9874, data 15Mar2017\n");
	if(insertRevision(&lista, 1235, "31Feb2012"))
		printf("Inserida revisão com id 1235, data 31Feb2012\n");

	timestamp = retrieveTimestamp(lista, 3445);
	if(strcmp(timestamp, "23Dec2015") == 0)
		printf("1º Teste timestamp passou.\n");
	timestamp = retrieveTimestamp(lista, 9874);
	if(strcmp(timestamp, "15Mar2017") == 0)
		printf("2º Teste timestamp passou.\n");
	timestamp = retrieveTimestamp(lista, 4444);
	if(timestamp == NULL)
		printf("3º Teste timestamp passou.\n");

	cleanList(&lista);
	if(lista == NULL)
		printf("Passou teste de limpeza de lista.\n");

}

int main(int argc, char const* argv[])
{

	printf("Hello world! \n");
	testes_hastTableContribuidores();
	return 0;
}

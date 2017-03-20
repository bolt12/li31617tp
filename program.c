#include "interface.h"

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
	return 0;
}

#include "interface.h"

void testes_hastTableArtigos()
{

	hashTArt h;
	avlArt avl = NULL;
	//hashTArt_Print(h);
	hashTArt_Init(h);

	if(hashTArt_Add (h, "Title_A", 71, 9, 2, 502, "21 Novembro 2001",
				"Luís Gomes", 78701, &avl))
		printf("Adicionado artigo: Title_A\n");
	if(hashTArt_Add (h, "Title_C", 7, 10, 2, 500, "2 Janeiro 2001",
				"Luís Gomes", 78701, &avl))
		printf("Adicionado artigo: Title_C\n");
	if(hashTArt_Add (h, "Title_B", 17, 12, 2, 500, "1 Novembro 2009",
				"Luís Gomes", 78701, &avl))
		printf("Adicionado artigo: Title_B\n");
	//Adicionar nova revisão a artigo já existente
	if(hashTArt_Add (h, "Title_B", 17, 8, 33, 501, "2 Novembro 2010",
				"Luís Gomes", 78701, &avl))
		printf("Adicionada revisão ao artigo: Title_B\n");

	printf("\n");
	char * c1 = hashTArt_GetTitle (h, 71);
	char * c2 = hashTArt_Timestamp (h, 71, 502);

	printf("Title: %s; Timestamp: %s\n",c1, c2 );
	char * c3 = hashTArt_GetTitle (h, 17);
	char * c4 = hashTArt_Timestamp (h, 17, 501);

	printf("Title: %s; Timestamp: %s\n",c3, c4 );

	printf("\n----------- avlArt ------------\n");

	/*
	for(i=0; i<SIZE; i++){
		if(h[i]){
			avl = avlArt_Insert(avl,h[i]);
			printf("Adicionado artigo %s à AVL\n", h[i]->title);
		}
	}
	*/

	printf("\nROOT DA AVL: %s; %d\n",((artNodo) avl->artigo)->title, ((artNodo) avl->artigo)->n_bytes);

	avlArt_Print(avl);

	//avlArt_Remove(avl,h[17]);

	putchar('\n');

	avlArt_Print(avl);
	

	hashTArt_Clean(h);
	avl_Clean(avl);
	printf("Done!\n");
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
	/*
	printf("Hello world! \n");
	printf("\n----------Iniciar testes-------------\n");
	testes_hastTableContribuidores();
	printf("\n-Testes hashtable contribuidores done-\n");
	printf("\n-------------------------------------\n");
	testes_lista_revisoes();
	printf("\n-----Testes listas revisões done-----\n");
	printf("\n-------------------------------------\n");
	testes_hastTableArtigos();
	printf("\n----Testes hashtable artigos & avl artigos done----\n");
	printf("\n----------Testes finalizados---------\n");
	return 0;
	*/
	
	char ** datasets = (char**) argv+1;
	long x;
	TAD_istruct qs;
	qs = init();

	printf("%s\n","init feito" );

	load (qs,argc-1, datasets);

	x = all_articles (qs);
	printf("All_articles -> %ld\n",x );
	x = unique_articles (qs);
	printf("unique_articles -> %ld\n",x );
	x = all_revisions (qs);
	printf("all_revisions -> %ld\n",x );
	//hashTArt_Print(qs->ht_art);

}

#include "hashTArt.h"

int main(int argc, char const *argv[])
{
	
	hashTArt h;
	//hashTArt_Print(h);
	hashTArt_Init(h);
	
	hashTArt_Print(h);
	printf("\n\n\n");

	hashTArt_Add (h, "Title_A", 71, 10, 2, 502, "21 Novembro 2001",
					 "Luís Gomes", 78701, 1);

	hashTArt_Add (h, "Title_C", 7, 10, 2, 500, "2 Janeiro 2001",
					 "Luís Gomes", 78701, 1);

	
	hashTArt_Add (h, "Title_B", 17, 10, 2, 500, "1 Novembro 2009",
					 "Luís Gomes", 78701, 1 );
	hashTArt_Print(h);
	printf("\n\n\n");
	char * c1 = hashTArt_GetTitle (h, 71);
	char * c2 = hashTArt_Timestamp (h, 71, 502);

	printf("Title: %s; Timestamp: %s\n",c1, c2 );

	hashTArt_Clean(h);
	printf("\n\n\nDEPOIS DE LIMPA: \n");
	hashTArt_Print(h);
	return 0;
}
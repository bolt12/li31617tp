#include "hashTArt.h"

#define PARENT(i) (i-1)/2  // os indices do array começam em 0
#define LEFT(i) 2*i + 1
#define RIGHT(i) 2*i + 2

typedef struct maxheapart{
	int used;
	hashTArt heap;
} *maxHeapArt;

//typedef struct hashtable *artNodo;

void maxHeapArt_Init(maxHeapArt mh);
int maxHeapArt_Insert(maxHeapArt mh, artNodo* node);
long* maxHeapArt_Top20(maxHeapArt mh); // Querie 6
long* maxHeapArt_TopN(maxHeapArt mh); // Querie 8
void maxHeapArt_Clean(maxHeapArt mh);

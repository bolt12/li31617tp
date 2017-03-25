#include "maxHeapArt.h"

void swap (hashTArt h, int a, int b){
	artNodo* t = h[a];
	h[a] = h[b];
	h[b] = t;
}

void maxHeapArt_Init(maxHeapArt mh){
	mh->used = 0;
	int i;
	for(i=0; i<SIZE; i++)
		mh->heap[i] = NULL;
}

int bubbleUp (hashTArt a, int i) {

    while (i!=0 && a[i]->n_bytes < a[PARENT(i)]->n_bytes) {
        swap(a, i, PARENT(i));
        i = PARENT(i);
    }
    return i;
}

int maxHeapArt_Insert(maxHeapArt h, artNodo *x) {
	int idx = x->heapInd;
	if(idx == -1){
		h->heap[h->used] = x;
		(h->used)++;
		return bubbleUp(h->heap, h->used-1);
	}
	else
		return bubbleUp(h->heap, idx);
	return 0;
}

void bubbleDown(hashTArt a, int used) {
    int i = 0, min ;

    while (RIGHT(i) < used && a[min = a[LEFT(i)] < a[RIGHT(i)] ? LEFT(i) : RIGHT(i)] < a[i]) {
        swap(a, i, min);
        i = min;
    }
    if (LEFT(i) < used && a[LEFT(i)] < a[i])
        swap(a, i, LEFT(i));
}

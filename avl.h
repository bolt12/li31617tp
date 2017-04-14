#ifndef __AVL_H__
#define __AVL_H__

#include <stdlib.h>

typedef struct avl{
	void* artigo;
	int height;
	struct avl *left;
	struct avl *right;
} *AVL, *avlArtBytes,*avlArtWords, *avlContrib;

AVL new_AVL(void* nodo);
int max(int a, int b);
int height(AVL avl);
void recalc(AVL avl);
AVL rotate_right(AVL avl);
AVL rotate_left(AVL avl);
AVL balance(AVL avl);
AVL find_min(AVL avl);
AVL remove_min(AVL avl);
void avl_Clean(AVL avl);

#endif

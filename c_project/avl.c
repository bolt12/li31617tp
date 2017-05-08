#include "avl.h"

AVL new_AVL(void* n)
{
	AVL new = malloc(sizeof(struct avl));

	new->artigo = n;
	new->height = 1;
	new->left   = NULL;
	new->right  = NULL;

	return new;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int height(AVL avl)
{
	return avl ? avl->height : 0;
}

void recalc(AVL avl)
{
	avl->height = 1 + max(height(avl->left), height(avl->right));
}

AVL rotate_right(AVL avl)
{
	AVL q = avl->left;

	avl->left = q->right;
	q->right = avl;

	recalc(avl);
	recalc(q);

	return q;
}

AVL rotate_left(AVL avl)
{
	AVL q = avl->right;
	avl->right = q->left;
	q->left = avl;

	recalc(avl);
	recalc(q);

	return q;
}

AVL balance(AVL avl)
{
	recalc(avl);

	if ( height(avl->left) - height(avl->right) == 2 )
	{
		if ( height(avl->left->right) > height(avl->left->left) )
			avl->left = rotate_left(avl->left);
		return rotate_right(avl);
	}
	else if ( height(avl->right) - height(avl->left) == 2 )
	{
		if ( height(avl->right->left) > height(avl->right->right) )
			avl->right = rotate_right(avl->right);
		return rotate_left(avl);
	}

	return avl;
}


AVL find_min(AVL avl)
{
	if ( avl->left != NULL )
		return find_min(avl->left);
	else
		return avl;
}

AVL remove_min(AVL avl)
{
	if ( avl->left == NULL )
		return avl->right;

	avl->left = remove_min(avl->left);
	return balance(avl);
}

void avl_Clean(AVL avl)
{
	if ( !avl )
		return;

	avl_Clean(avl->left);
	avl_Clean(avl->right);
	free(avl);
}

#include<stdio.h>
#include<stdlib.h>

struct Node
{
  int key;
  struct Node *left;
  struct Node *right;
  struct Node *p;
};

struct Node *
Create (struct Node *root, int key)
{
  struct Node *tmp = (struct Node *) malloc (sizeof (struct Node));
  tmp->key = key;
  tmp->p = NULL;
  tmp->left = NULL;
  tmp->right = NULL;
  root = tmp;
  return root;
}

void
Inorder_Tree_Walk (struct Node *x)
{
  if (x != NULL)
    {
      Inorder_Tree_Walk (x->left);
      printf ("%d ", x->key);
      Inorder_Tree_Walk (x->right);
    }
}

struct Node *
Search (struct Node *root, int k)
{
  if (root == NULL || k == root->key)
    return root;
  if (k < root->key)
    return Search (root->left, k);
  return Search (root->right, k);
}

struct Node *
Min (struct Node *root)
{
  while (root->left != NULL)
    root = root->left;
  return root;
}

struct Node *
Max (struct Node *root)
{
  while (root->right != NULL)
    root = root->right;
  return root;
}

struct Node *
Successor (struct Node *x)
{
  if (x->right != NULL)
    return Min (x->right);
  struct Node *y = x->p;
  while (y != NULL && x == y->right)
    {
      x = y;
      y = y->p;
    }
  return y;
}

struct Node *
Predecessor (struct Node *x)
{
  if (x->left != NULL)
    return Max (x->left);
  struct Node *y = x->p;
  while (y != NULL && x == y->left)
    {
      x = y;
      y = y->p;
    }
  return y;
}

struct Node *
Insert (struct Node *root, int k)
{
  struct Node *z;
  z = Create (z, k);
  struct Node *y = NULL;
  struct Node *x = root;
  while (x != NULL)
    {
      y = x;
      if (z->key < x->key)
	x = x->left;
      else
	x = x->right;
    }
  z->p = y;
  if (y == NULL)
    {
      root = z;
    }
  else if (z->key < y->key)
    y->left = z;
  else
    y->right = z;
  return root;
}


struct Node *
MakeTree (int *arr, int n)
{
  if (n == 0)
    return NULL;
  struct Node *root = (struct Node *) malloc (sizeof (struct Node));
  root->key = arr[0];
 
  for (int i = 1; i < n; ++i)
    {
      root = Insert (root, arr[i]);
    }
  return root;
}

struct Node* Transplant(struct Node* root, struct Node* u, struct Node* v) {
	if (u->p == NULL) 
		root = v;
	else if (u == u->p->left)
		u->p->left = v;
	else u->p->right = v;
	if (v != NULL) 
		v->p = u->p;
	return root; 
} 

struct Node* Delete(struct Node* root, int k) {
	struct Node* z = (struct Node*)malloc(sizeof(struct Node));  
	z = Search(root, k);
	if (z == NULL) return NULL;
	if (z->left == NULL) { 
		root = Transplant(root, z, z->right);
		return root;
	}
	else if (z->right == NULL) {
		root = Transplant(root, z, z->left);
		return root; 
	} 
	else {
		struct Node* y;
		y = Create(y, 0);
		y = Min(z->right);
		if (y->p != z) {
			root = Transplant(root, y, y->right);
			y->right = z->right;
			y->right->p = y;	
		}
		root = Transplant(root, z, y);
		y->left = z->left;
		y->left->p = y; 
		return root; 
	} 
}

void Preorder_Tree_Walk(struct Node* root) {
	if (root == NULL) 
		return; 
	printf("%d ", root->key);
	Preorder_Tree_Walk(root->left);
	Preorder_Tree_Walk(root->right); 
}

void Postorder_Tree_Walk(struct Node* root) {
        if (root == NULL)
                return;
        Postorder_Tree_Walk(root->left);
        Postorder_Tree_Walk(root->right);
	if(root->key)
		printf("%d ", root->key);
}

struct Node* Delete_Tree(struct Node* root) {
	while(root != NULL) {
		//printf("%d ", root->key);
		root = Delete(root, root->key);
		//Inorder_Tree_Walk(root);
		//printf("\n");
	}
       return root;	
}


int
main ()
{
  int n;
  printf ("Input a size of array:");
  scanf ("%d", &n);
  int *arr = (int *) calloc (n, sizeof (int));

  for (int i = 0; i < n; ++i)
    {
      scanf ("%d", &arr[i]);
    }

  struct Node *x = MakeTree (arr, n);
  struct Node* y;
  y = Create(y, 0);
  printf("Enter a number: ");
  int v = 0;
  scanf("%d", &v);
  y = Search(x, v);
  if (y == NULL) 
	  printf("Can't find a number\n");
  else 
	  printf("%d\n", y->key);
  printf ("inorder ");
  Inorder_Tree_Walk (x);
  printf ("\n");
  printf ("preorder ");
  Preorder_Tree_Walk (x);
  printf ("\n");
  printf ("postorder ");
  Postorder_Tree_Walk (x);
  printf ("\n"); 

  printf ("Min %d\n", Min (x)->key); 
  printf ("Max %d\n", Max (x)->key);
  /*
  printf ("Search %d\n", Search (x, 10)->key);
  printf ("Suc x = %d: %d\n", x->key, Successor (x)->key);
  printf ("Pre x = %d: %d\n", x->key, Predecessor (x)->key);
  */
  x = Delete(x, x->key);
  printf ("inorder ");
  Inorder_Tree_Walk (x);
  printf ("\n");

  x = Delete_Tree(x);
  if(x == NULL)
	  printf("Tree was deleted\n");
  /*printf ("inorder ");
  Inorder_Tree_Walk (x);
  printf ("\n");
*/ 

  return 0;

}

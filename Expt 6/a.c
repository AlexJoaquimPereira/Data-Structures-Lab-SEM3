#include <stdio.h>
#include <stdlib.h>

struct treenode{
	struct treenode *lchild;
	int data;
	struct treenode *rchild;
};

struct node {
	int data;
	struct node * link;
};

struct treenode * create_tree(struct node *, struct node *, int);
struct node * create_list(struct node *, int);
struct node * addatbeg(struct node *);
struct node * addatend(struct node *);
int height(struct treenode *);
int depth(struct treenode *);
void level_order_traversal(struct treenode *);

struct treenode * create_tree(struct node *inorder, struct node *postorder, int n){
	int i, j;
	struct treenode *temp = (struct treenode *)malloc(sizeof(struct treenode));
	struct node *p = postorder, *q;
	if (n == 0)
		return NULL;
	for (i = 1; i < n; i++)
		p=p->next;
	temp->lchild = NULL, temp->rchild = NULL;
	temp->info = p->info;
	if(n == 1)
		return temp;
	q = inorder;
	for (i = 0; q->info != p->info; i++)
		q = q->next;
	temp->lchild = create_tree(postorder, inorder, i);
	for(j = 1; j <= i; j++)
		postptr =postptr->next;
	temp->rchild = create_tree(postorder, q->next, n-i-1);
	return temp;
}

struct node * addatend(struct node *start, int data)
{
	struct node *p, *temp;
	temp = (struct node*)malloc(sizeof(struct node));
	temp -> info = data;
	p = start;
	while (p -> link != NULL)
		p = p -> link;
	p -> link = temp;
	temp -> link = NULL;
	return start;
}

struct node * addatbeg(struct node *start, int data)
{
	struct node *temp;
	temp = (struct node *)malloc(sizeof(struct node));
	temp -> info = data;
	temp -> link = start;
	start = temp;
	return start;
}

struct node * create_list(struct node *start, int n){
	int n, data;
	printf("Enter number of nodes: ");
	scanf("%d", &n);
	start = NULL;
	if (n == 0)
		return start;
	printf("Enter element 1: ");
	scanf("%d", &data);
	start = addatbeg(start, data);
	for(int i = 2; i <= n; i++){
		printf("Enter element %d: ", i);
		scanf("%d", &data);
		start = addatend(start, data);
	}
	return start;
}

int height(struct treenode *ptr){
	if(ptr == NULL)
		return 0;
	int lheight, rheight;
	lheight = height(ptr->lchild);
	rheight = height(ptr->rchild);
	if(lheight >rheight)
		return (lheight + 1);
	else return (rheight + 1);
}

void level_order_traversal(struct treenode *root){
	int h = height(root);
	for(int level = 0; level < h; level++){
		current_level(root, level);
}

void current_level(struct treenode *ptr, int level){
	if(ptr == NULL)
		return;
	if(l == 0)
		printf(" %d ", ptr->data);
	else{
		current_level(ptr->lchild, level-1);
		current_level(ptr->rchild, level-1);
	} 
}

int level_check(struct treenode *ptr, int level, int info){
	if(level == 0){
		if(ptr->data == info)
			return 1;
	}
	else{
		current_level(ptr->lchild, level-1, info);
		current_level(ptr->rchild, level-1, info);
	}
	return 0; 
}

int depth(struct treenode *root, int info){
	struct treenode *ptr = root;
	if(ptr == NULL)
		return 0;
	int h = height(tree);
	for(int i = 1; i <= h; i++){
	/*
	ALGORITHM:
	1: Check level i -> send call to level_check
	1.1: if i has the node
			return 1
		else return 0
	2: if found:
			return i
	*/
		if(level_check(ptr, i, info))
			return i;
	}
}

int main(){
	int n;
	struct treenode *root = NULL;
	struct node *postorder = NULL, *inorder = NULL;
	printf("Enter the number of nodes in the tree: ");
	scanf("%d", &n);
	printf("Enter the postorder traversal:\n");
	postorder = create_list(postorder, n);
	printf("Enter the inorder traversal:\n");
	inorder = create_list(inorder, n);
	printf("Creating the binary tree...\n");
	root = create_tree(postorder, inorder, n);
	printf("Created the binary tree\n");
	printf("Height of the tree: %d\n", height(root));
}

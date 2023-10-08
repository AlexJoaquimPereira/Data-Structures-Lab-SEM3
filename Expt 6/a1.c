#include <stdio.h>
#include <stdlib.h>

struct treenode {
    struct treenode* lchild;
    int info;
    struct treenode* rchild;
};

struct node {
    int info;
    struct node* link;
};

struct treenode* create_tree(struct node*, struct node*, int);
struct node* create_list(struct node*, int);
struct node* addatbeg(struct node*, int);
struct node* addatend(struct node*, int);
int height(struct treenode*);
int depth(struct treenode*, int, int);
void level_order_traversal(struct treenode*);
void current_level(struct treenode*, int);

struct treenode* create_tree(struct node* inorder, struct node* postorder, int n) {
    int i, j;
    struct treenode* temp = NULL;
    struct node* p = postorder, * q;

    if (n == 0)
        return NULL;

    // Find the root node in the postorder traversal
    for (i = 1; i < n; i++)
        p = p->link;

    // Create a treenode for the root
    temp = (struct treenode*)malloc(sizeof(struct treenode));
    temp->lchild = NULL;
    temp->rchild = NULL;
    temp->info = p->info;

    if (n == 1)
        return temp;

    // Find the root node in the inorder traversal
    q = inorder;
    for (i = 0; q->info != p->info; i++)
        q = q->link;

    // Recursively build the left and right subtrees
    temp->lchild = create_tree(inorder, postorder, i);
    for (j = 1; j <= i; j++)
        postorder = postorder->link;
    temp->rchild = create_tree(q->link, postorder, n - i - 1);

    return temp;
}

struct node* addatend(struct node* start, int data) {
    struct node* p, * temp;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->info = data;
    temp->link = NULL;
    p = start;
    if (start == NULL) {
        start = temp;
        return start;
    }
    while (p->link != NULL)
        p = p->link;
    p->link = temp;
    return start;
}

struct node* addatbeg(struct node* start, int data) {
    struct node* temp;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->info = data;
    temp->link = start;
    start = temp;
    return start;
}

struct node* create_list(struct node* start, int n) {
    int info;
    if (n == 0)
        return start;
    printf("Enter the elements: ");
    scanf("%d", &info);
    start = addatbeg(start, info);
    for (int i = 2; i <= n; i++) {
        scanf("%d", &info);
        start = addatend(start, info);
    }
    return start;
}

int height(struct treenode* ptr) {
    if (ptr == NULL)
        return 0;
    int lheight, rheight;
    lheight = height(ptr->lchild);
    rheight = height(ptr->rchild);
    if (lheight > rheight)
        return (lheight + 1);
    else
        return (rheight + 1);
}

void level_order_traversal(struct treenode* root) {
    int h = height(root);
    for (int level = 0; level < h; level++) {
        current_level(root, level);
        printf("\n");
    }
}

void current_level(struct treenode* ptr, int level) {
    if (ptr == NULL)
        return;
    if (level == 0)
        printf(" %d ", ptr->info);
    else {
        current_level(ptr->lchild, level - 1);
        current_level(ptr->rchild, level - 1);
    }
}

int depth(struct treenode* root, int info, int currentDepth) {
    if (root == NULL)
        return 0;
    if (root->info == info)
        return currentDepth;
    int ldepth = depth(root->lchild, info, currentDepth + 1);
    if (ldepth != 0)
        return ldepth;
    int rdepth = depth(root->rchild, info, currentDepth + 1);
    return rdepth;
}

int main() {
    int n, s, info;
    struct treenode* root = NULL;
    struct node* postorder = NULL, * inorder = NULL;
    printf("Enter the number of nodes in the tree: ");
    scanf("%d", &n);
    printf("Enter the postorder traversal:\n");
    postorder = create_list(postorder, n);
    printf("Enter the inorder traversal:\n");
    inorder = create_list(inorder, n);
    printf("Creating the binary tree...\n");
    root = create_tree(inorder, postorder, n);
    printf("Created the binary tree\n");
    do {
        printf("1. Display the height of the tree\n");
        printf("2. Return the depth of a given node in the tree\n");
        printf("3. Perform Level order traversal\n");
        printf("4. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &s);
        switch (s) {
        case 1:
            printf("Height of the tree: %d\n", height(root));
            break;
        case 2:
            printf("Enter the node data to find its depth: ");
            scanf("%d", &info);
            int nodeDepth = depth(root, info, 0);
            if (nodeDepth != 0)
                printf("Depth of node %d: %d\n", info, nodeDepth);
            else
                printf("Node not found in the tree\n");
            break;
        case 3:
            printf("Level order traversal:\n");
            level_order_traversal(root);
            break;
        case 4:
            break;
        default:
            printf("Invalid input\n");
        }
    } while (s != 4);
    return 0;
}

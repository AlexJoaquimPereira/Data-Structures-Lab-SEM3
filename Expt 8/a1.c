#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    struct node* lchild;
    bool lthread;
    int info;
    struct node* rchild;
    bool rthread;
};

struct node* insert(struct node*, int);
struct node* delete(struct node*, int);
struct node* in_succ(struct node*);
struct node* in_pred(struct node*);
void inorder(struct node*);
void preorder(struct node*);
void postorder(struct node*);
void search(struct node*, int);

struct node* insert(struct node* root, int ikey) {
    struct node* temp, *par = NULL, *ptr = root;
    int found = 0;
    while (ptr != NULL) {
        if (ikey == ptr->info) {
            printf("Duplicate\n");
            found = 1;
            break;
        }
        par = ptr;
        if (ikey < ptr->info) {
            if (ptr->lthread == false)
                ptr = ptr->lchild;
            else
                break;
        } else {
            if (ptr->rthread == false)
                ptr = ptr->rchild;
            else
                break;
        }
    }
    if (!found) {
        temp = (struct node*)malloc(sizeof(struct node));
        temp->info = ikey;
        temp->lthread = true;
        temp->rthread = true;
        if (par == NULL) {
            root = temp;
            temp->lchild = NULL;
            temp->rchild = NULL;
        } else if (ikey > par->info) {
            temp->rchild = par->rchild;
            temp->lchild = par;
            par->rchild = temp;
            par->rthread = false;
        } else {
            temp->lchild = par->lchild;
            temp->rchild = par;
            par->lchild = temp;
            par->lthread = false;
        }
    }
    return root;
}

struct node* delete(struct node* root, int dkey) {
    // Implement deletion similar to your previous Binary Search Tree code
    // ...
}

struct node* in_succ(struct node* ptr) {
    if (ptr->rthread == true)
        return ptr->rchild;
    else {
        ptr = ptr->rchild;
        while (ptr->lthread == false)
            ptr = ptr->lchild;
    }
    return ptr;
}

struct node* in_pred(struct node* ptr) {
    if (ptr->lthread == true)
        return ptr->lchild;
    else {
        ptr = ptr->lchild;
        while (ptr->rthread == false)
            ptr = ptr->rchild;
    }
    return ptr;
}

void inorder(struct node* root) {
    struct node* ptr = root;
    if (ptr == NULL) {
        printf("Empty\n");
        return;
    }
    while (ptr->lthread == false)
        ptr = ptr->lchild;
    while (ptr != NULL) {
        printf(" %d", ptr->info);
        ptr = in_succ(ptr);
    }
}

void preorder(struct node* root) {
    // Implement preorder traversal
    // ...
}

void postorder(struct node* root) {
    // Implement postorder traversal
    // ...
}

void search(struct node* ptr, int skey) {
    while (ptr->lthread == false || ptr->rthread == false) {
        if (ptr->info == skey) {
            printf("Element found\n");
            return;
        } else if (skey < ptr->info)
            ptr = ptr->lchild;
        else
            ptr = ptr->rchild;
    }
    printf("Element not found\n");
}

int main() {
    struct node* root = NULL;
    int s, key;
    char c;
    printf("Do you want to insert many elements? y/n: ");
    scanf(" %c", &c);
    if (c == 'y') {
        int n;
        printf("Enter the number of elements to insert: ");
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            printf("Insert: ");
            scanf("%d", &key);
            root = insert(root, key);
        }
    }
    do {
        printf("\n1. Insertion of a new element\n"
               "2. Deletion of an existing element\n"
               "3. Searching for a given element\n"
               "4. Perform inorder, preorder, and postorder traversals\n"
               "5. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &s);
        switch (s) {
            case 1:
                printf("Insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Delete: ");
                scanf("%d", &key);
                root = delete(root, key);
                break;
            case 3:
                printf("Enter the element: ");
                scanf("%d", &key);
                search(root, key);
                break;
            case 4:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                printf("Postorder: ");
                postorder(root);
                break;
            case 5:
                break;
            default:
                printf("Invalid input\n");
        }
    } while (s != 5);
}

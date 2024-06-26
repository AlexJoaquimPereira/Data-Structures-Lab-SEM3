#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    struct node *lchild;
    bool lthread;
    int info;
    struct node *rchild;
    bool rthread;
};

struct node *insert(struct node *, int);
struct node *del(struct node *, int);
struct node *case_a(struct node *, struct node *, struct node *);
struct node *case_b(struct node *, struct node *, struct node *);
struct node *case_c(struct node *, struct node *, struct node *);
struct node *in_succ(struct node *);
struct node *in_pred(struct node *);
void inorder(struct node *);
void preorder(struct node *);

struct node *insert(struct node *root, int ikey) {
    struct node *temp, *par = NULL, *ptr = root;
    int found = 0;

    while (ptr != NULL) {
        if (ikey == ptr->info) {
            printf("Duplicate\n");
            found = 1;
            break;
        }
        par = ptr;
        if (ikey < ptr->info) {
            if (ptr->lthread == false) {
                ptr = ptr->lchild;
            } else {
                break;
            }
        } else {
            if (ptr->rthread == false) {
                ptr = ptr->rchild;
            } else {
                break;
            }
        }
    }

    if (!found) {
        temp = (struct node *)malloc(sizeof(struct node));
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

struct node *del(struct node *root, int dkey) {
    struct node *par = NULL, *ptr = root;
    int found = 0;

    while (ptr != NULL) {
        if (dkey == ptr->info) {
            found = 1;
            break;
        }
        par = ptr;
        if (dkey < ptr->info) {
            if (ptr->lthread == false) {
                ptr = ptr->lchild;
            } else {
                break;
            }
        } else {
            if (ptr->rthread == false) {
                ptr = ptr->rchild;
            } else {
                break;
            }
        }
    }

    if (!found) {
        printf("Element not found\n");
    } else if (ptr->lthread == false && ptr->rthread == false) {
        root = case_c(root, par, ptr);
    } else if (ptr->lthread == false || ptr->rthread == false) {
        root = case_b(root, par, ptr);
    } else {
        root = case_a(root, par, ptr);
    }

    return root;
}

struct node *case_a(struct node *root, struct node *par, struct node *ptr) {
    if (par == NULL) {
        root = NULL;
    } else if (ptr == par->lchild) {
        par->lthread = true;
        par->lchild = ptr->lchild;
    } else {
        par->rthread = true;
        par->rchild = ptr->rchild;
    }
    free(ptr);
    return root;
}

struct node *case_b(struct node *root, struct node *par, struct node *ptr) {
    struct node *child, *s, *p;
    if (ptr->lthread == false) {
        child = ptr->lchild;
    } else {
        child = ptr->rchild;
    }

    if (par == NULL) {
        root = child;
    } else if (ptr == par->lchild) {
        par->lchild = child;
    } else {
        par->rchild = child;
    }

    s = in_succ(ptr);
    p = in_pred(ptr);

    if (ptr->lthread == false) {
        p->rchild = s;
    } else {
        if (ptr->rthread == false) {
            s->lchild = p;
        }
    }

    free(ptr);
    return root;
}

struct node *case_c(struct node *root, struct node *par, struct node *ptr) {
    struct node *succ = ptr->rchild, *parsucc = ptr;
    while (succ->lchild != NULL) {
        parsucc = succ;
        succ = succ->lchild;
    }
    ptr->info = succ->info;

        if (succ->lthread == true && succ->rthread == true) {
        root = case_a(root, parsucc, succ);
    } else {
        root = case_b(root, parsucc, succ);
    }
    return root;
}

struct node *in_succ(struct node *ptr) {
    if (ptr->rthread == true) {
        return ptr->rchild;
    } else {
        ptr = ptr->rchild;
        while (ptr->lthread == false) {
            ptr = ptr->lchild;
        }
    }
    return ptr;
}

struct node *in_pred(struct node *ptr) {
    if (ptr->lthread == true) {
        return ptr->lchild;
    } else {
        ptr = ptr->lchild;
        while (ptr->rthread == false) {
            ptr = ptr->rchild;
        }
    }
    return ptr;
}

void inorder(struct node *root) {
    struct node *ptr = root;
    if (ptr == NULL) {
        printf("Empty\n");
        return;
    }
    while (ptr->lthread == false) {
        ptr = ptr->lchild;
    }
    while (ptr != NULL) {
        printf(" %d", ptr->info);
        ptr = in_succ(ptr);
    }
}

void preorder(struct node *root) {
    struct node *ptr = root;
    if (ptr == NULL) {
        printf("Empty\n");
        return;
    }
    while (ptr != NULL) {
        printf(" %d", ptr->info);
        if (ptr->lthread == false) {
            ptr = ptr->lchild;
        } else if (ptr->rthread == false) {
            ptr = ptr->rchild;
        } else {
            while (ptr != NULL && ptr->rthread == true) {
                ptr = ptr->rchild;
            }
            if (ptr != NULL) {
                ptr = ptr->rchild;
            }
        }
    }
}

struct node *search(struct node *ptr, int skey) {
    while (ptr != NULL) {
        if (skey == ptr->info) {
            return ptr;
        } else if (skey > ptr->info && ptr->rthread == false) {
            ptr = ptr->rchild;
        } else if (skey < ptr->info && ptr->lthread == false) {
            ptr = ptr->lchild;
        } else {
            printf("Element not found\n");
            return NULL;
        }
    }
    printf("Element not found\n");
    return NULL;
}

int main() {
    struct node *root = NULL;
    int s, k;
    char c;
    struct node *seek;

    do {
        printf("\n1. Insertion of a new element\n"
               "2. Deletion of an existing element\n"
               "3. Searching for a given element\n"
               "4. Perform inorder and preorder traversals\n"
               "5. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &s);

        switch (s) {
            case 1:
                printf("Insert: ");
                scanf("%d", &k);
                root = insert(root, k);
                break;
            case 2:
                printf("Delete: ");
                scanf("%d", &k);
                root = del(root, k);
                break;
            case 3:
                printf("Enter the element: ");
                scanf("%d", &k);
                seek = search(root, k);
                if (seek == NULL) {
                    printf("Element not found\n");
                } else {
                    printf("Element found\n");
                }
                break;
            case 4:
                printf("Inorder: ");
                inorder(root);
                printf("\nPreorder: ");
                preorder(root);
                break;
            case 5:
                printf("Exiting\n");
                break;
            default:
                printf("Invalid input\n");
        }
    } while (s != 5);

    return 0;
}
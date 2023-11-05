#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

struct node{
    struct node *lchild;
    int info;
    struct node *rchild;
    int balance;
};

struct node *RightRotation(struct node *pptr){
    struct node *aptr;
    aptr = pptr->lchild;
    pptr->lchild = aptr->rchild;
    aptr->rchild = pptr;
    return aptr;
}

struct node *LeftRotation(struct node *pptr){
    struct node *aptr;
    aptr = pptr->rchild;
    pptr->rchild = aptr->lchild;
    aptr->lchild = pptr;
    return aptr;
}

struct node *insert_rightbalance(struct node *pptr){
    struct node *aptr, *bptr;
    aptr = pptr->lchild;
    if (aptr->balance == -1){
        pptr->balance = 0;
        aptr->balance = 0;
        pptr = RightRotation(pptr);
    }
    else{
        bptr = aptr->rchild;
        switch (bptr->balance){
            case -1:
                pptr->balance = 1;
                aptr->balance = 0;
                break;
            case 1:
                pptr->balance = 0;
                aptr->balance = -1;
                break;
            case 0:
                pptr->balance = 0;
                aptr->balance = 0;
        }
        bptr->balance = 0;
        pptr->lchild = RightRotation(aptr);
        pptr = LeftRotation(pptr);
    }
    return pptr;
}

struct node *insert_leftbalance(struct node *pptr){
    struct node *aptr, *bptr;
    aptr = pptr->lchild;
    if (aptr->balance == 1){
        pptr->balance = 0;
        aptr->balance = 0;
        pptr = RightRotation(pptr);
    }
    else{
        bptr = aptr->rchild;
        switch (bptr->balance){
            case -1:
                pptr->balance = 0;
                aptr->balance = 1;
                break;
            case 1:
                pptr->balance = -1;
                aptr->balance = 0;
                break;
            case 0:
                pptr->balance = 0;
                aptr->balance = 0;
        }
        bptr->balance = 0;
        pptr->lchild = LeftRotation(aptr);
        pptr = RightRotation(pptr);
    }
    return pptr;
}

struct node *insert_left_check(struct node *pptr, int *ptaller){
    switch (pptr->balance){
        case 0:
            pptr->balance = 1;
            break;
        case 1:
            pptr->balance = 0;
            *ptaller = FALSE;
            break;
        case -1:
            pptr = insert_leftbalance(pptr);
            *ptaller = FALSE;
    }
    return pptr;
}

struct node *insert_right_check(struct node *pptr, int *ptaller){
    switch (pptr->balance){
        case 0:
            pptr->balance = -1;
            break;
        case 1:
            pptr->balance = 0;
            *ptaller = FALSE;
            break;
        case -1:
            pptr = insert_rightbalance(pptr);
            *ptaller = FALSE;
    }
    return pptr;
}

struct node *insert(struct node *pptr, int ikey){
    static int taller;
    if (pptr == NULL){
        pptr = (struct node *)malloc(sizeof(struct node));
        pptr->info = ikey;
        pptr->lchild = NULL;
        pptr->rchild = NULL;
        pptr->balance = 0;
        taller = TRUE;
    }
    else if (ikey < pptr->info){
        pptr->lchild = insert(pptr->lchild, ikey);
        if (taller == TRUE)
            pptr = insert_left_check(pptr, &taller);
    }
    else if (ikey > pptr->info){
        pptr->rchild = insert(pptr->rchild, ikey);
        if (taller == TRUE)
            pptr = insert_right_check(pptr, &taller);
    }
    else{
        printf("Duplicate key\n");
        taller = FALSE;
    }
    return pptr;
}

struct node*del_rightbalance(struct node *pptr,int *pshorter){
    struct node *bptr,*aptr;
    aptr=pptr->rchild;
    if(aptr->balance==0){
        pptr->balance=-1;
        aptr->balance=1;
        *pshorter=FALSE;
        pptr=LeftRotation(pptr);
    }
    else if(aptr->balance==-1){
        pptr->balance=0;
        aptr->balance=0;
        pptr=LeftRotation(pptr);
    }
    else{
        bptr=aptr->lchild;
        switch(bptr->balance){
            case 0:
                pptr->balance=0;
                aptr->balance=0;
                break;
            case 1:
                pptr->balance=0;
                aptr->balance=-1;
                break;
            case -1:
                pptr->balance=1;
                aptr->balance=0;
                break;
        }
        bptr->balance=0;
        pptr->lchild=RightRotation(aptr);
        pptr=LeftRotation(pptr);
    }
    return pptr;
}

struct node *del_left_check(struct node *pptr,int *pshorter){
    switch(pptr->balance){
        case 0:
            pptr->balance=-1;
            *pshorter=FALSE;
            break;
        case 1:
            pptr->balance=0;
            break;
        case -1:
            pptr=del_rightbalance(pptr,pshorter);
            break;
    }
    return pptr;
}

struct node* del_leftbalance(struct node *pptr, int *pshorter){
    struct node *bptr, *aptr;
    aptr = pptr->rchild;
    if (aptr->balance == 0) {
        pptr->balance = 1;
        aptr->balance = -1;
        *pshorter = FALSE;
        pptr = LeftRotation(pptr);
    } 
    else if (aptr->balance == -1){
        pptr->balance = 0;
        aptr->balance = 0;
        pptr = LeftRotation(pptr);
    } 
    else {
        bptr = aptr->lchild;
        switch (bptr->balance){
            case 0:
                pptr->balance = 0;
                aptr->balance = 0;
                break;
            case 1:
                pptr->balance = -1;
                aptr->balance = 0;
                break;
            case -1:
                pptr->balance = 0;
                aptr->balance = 1;
                break;
        }
        bptr->balance = 0;
        pptr->lchild = LeftRotation(aptr);
        pptr = RightRotation(pptr);
    }
    return pptr;
}

struct node *del_right_check(struct node *pptr, int *pshorter){
    switch (pptr->balance){
        case 0:
            pptr->balance = 1;
            *pshorter = FALSE;
            break;
        case -1:
            pptr->balance = 0;
            break;
        case 1:
            pptr = del_leftbalance(pptr, pshorter);
            break;
    }
    return pptr;
}

struct node *delete(struct node * pptr,int dkey){
    struct node * tmp, * succ;
    static int shorter;
    if(pptr==NULL){
        printf("Key not present\n");
        shorter=FALSE;
        return pptr;
    }
    if(dkey<pptr->info){
        pptr->lchild=del(pptr->lchild,dkey);
        if(shorter==TRUE){
            pptr=del_left_check(pptr,&shorter);
        }
    }
    else if(dkey>pptr->info){
        pptr->rchild=del(pptr->rchild,dkey);
        if(shorter==TRUE){
            pptr=del_right_check(pptr,&shorter);
        }
    }
    else{
        if(pptr->lchild!=NULL && pptr->lchild!=NULL){
            succ=pptr->lchild;
            while(succ->lchild)
                succ=succ->lchild;
            pptr->info=succ->info;
            pptr->rchild=del(pptr->rchild,succ->info);
            if(shorter==TRUE)
                pptr=del_right_check(pptr,&shorter);
        }
        else{
            tmp = pptr;
            if(pptr->lchild!=NULL)
                pptr=pptr->lchild;
            else if(pptr->rchild!=NULL)
                pptr=pptr->rchild;
            else
                pptr=NULL;
            free(tmp);
            shorter=TRUE;
        }
    }
    return pptr;
}

void search(struct node *ptr, int skey){
    static int found=0;
    if(ptr == NULL){
        printf("Element not found\n");
        return;
    }
    else if(skey<ptr->info)
        search(ptr->lchild,skey);
    else if(skey>ptr->info)
        search(ptr->rchild,skey);
    else found=1;   
    if(found == 0)
        printf("Element not found\n");
    else printf("Element found\n");
}

void minimum(struct node *ptr){
    if(ptr!=NULL)
        while(ptr->lchild!=NULL)
            ptr=ptr->lchild;
    printf("Minimum element is : %d",ptr->info);
}

void maximum(struct node *ptr){
    if(ptr!=NULL)
        while(ptr->rchild!=NULL)
            ptr=ptr->rchild;
    printf("Maximum element is : %d",ptr->info);
}

int main(){
    struct node *root = NULL;
    int s, key;
    do{
        printf("\n1. Insertion of a new element\n"
				"2. Deletion of an existing element\n"
				"3. Searching for a given element\n"
				"4. Find minimum and maximum element\n"
				"5. Exit\n");
		printf("Enter your option: ");
        scanf("%d", &s);
        switch(s){
            case 1: printf("Insert: ");
                    scanf("%d", &key);
                    root = insert(root, key);
                    break;
            case 2: printf("Delete: ");
                    scanf("%d", &key);
                    root = delete(root, key);
                    break;
            case 3: printf("Enter the element: ");
                    scanf("%d", &key);
                    search(root, key);
                    break;
            case 4: minimum(key);
                    maximum(key);
                    break;
            case 6: break;
            default: printf("Invalid input\n");
        }
    }while(s != 6);
    return 0;
}
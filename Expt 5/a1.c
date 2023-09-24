#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node* prev;
    int info;
    struct node* next;
};

struct node* addtoempty(struct node*, int);
struct node* addatbeg(struct node*, int);
struct node* addatend(struct node*, int);
struct node* create(struct node*);
struct node* addbefore(struct node*, int, int);
struct node* addafter(struct node*, int, int);
struct node* deleteNode(struct node*, int);
struct node* reverse(struct node*);
void display(struct node*);
void freeList(struct node*);

struct node* addtoempty(struct node* start, int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->info = data;
    temp->next = NULL;
    temp->prev = NULL;
    start = temp;
    return start;
}

struct node* addatbeg(struct node* start, int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->info = data;
    temp->next = start;
    temp->prev = NULL;
    start->prev = temp; // Update the previous of the old start
    start = temp;
    return start;
}

struct node* addatend(struct node* start, int data) {
    struct node* p = start, * temp;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->info = data;
    temp->next = NULL;
    while (p->next != NULL)
        p = p->next;
    temp->prev = p;
    p->next = temp;
    return start;
}

struct node* create(struct node* start) {
    int n, data;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    if (n == 0)
        return start;
    printf("Enter data: ");
    scanf("%d", &data);
    start = addtoempty(start, data);
    for (int i = 1; i < n; i++) {
        printf("Enter data: ");
        scanf("%d", &data);
        start = addatend(start, data);
    }
    return start;
}

struct node* addbefore(struct node* start, int data, int item) {
    struct node* p = start->next, * temp;
    if (start->info == item) {
        start = addatbeg(start, data); // Handle adding before the head node
        return start;
    }
    while (p != NULL) {
        if (p->info == item) {
            temp = (struct node*)malloc(sizeof(struct node));
            temp->info = data;
            temp->prev = p->prev;
            temp->next = p;
            p->prev->next = temp;
            p->prev = temp;
            return start;
        }
        p = p->next;
    }
    printf("Item not found\n");
    return start;
}

struct node* addafter(struct node* start, int data, int item) {
    struct node* p = start, * temp;
    while (p != NULL) {
        if (p->info == item) {
            temp = (struct node*)malloc(sizeof(struct node));
            temp->info = data;
            temp->prev = p;
            temp->next = p->next;
            if (p->next != NULL)
                p->next->prev = temp;
            p->next = temp;
            return start;
        }
        p = p->next;
    }
    printf("Item not found\n");
    return start;
}

struct node* deleteNode(struct node* start, int item) {
    struct node* temp;
    struct node* p = start;

    // Handle deleting the head node
    if (p != NULL && p->info == item) {
        if (p->next != NULL)
            p->next->prev = NULL;
        start = p->next;
        free(p);
        return start;
    }

    while (p != NULL && p->info != item) {
        temp = p;
        p = p->next;
    }

    if (p == NULL) {
        printf("Item not found\n");
        return start;
    }

    temp->next = p->next;

    if (p->next != NULL) {
        p->next->prev = temp;
    }

    free(p);
    return start;
}

struct node* reverse(struct node* start) {
    struct node* p = start, * temp = NULL;
    while (p != NULL) {
        temp = p->prev;
        p->prev = p->next;
        p->next = temp;
        p = p->prev;
    }
    if (temp != NULL) {
        start = temp->prev;
    }
    return start;
}

void display(struct node* start) {
    struct node* p = start;
    if (start == NULL) {
        printf("Empty list\n");
        return;
    }
    printf("List contents\n");
    while (p != NULL) {
        printf(" %d", p->info);
        p = p->next;
    }
    printf("\n");
}

void freeList(struct node* start) {
    struct node* p = start;
    while (p != NULL) {
        struct node* temp = p;
        p = p->next;
        free(temp);
    }
}

int main() {
    struct node* start = NULL;
    int s, data, item;
    do {
        printf("\n1. Creating a list");
        printf("\n2. Add at beginning");
        printf("\n3. Add at end");
        printf("\n4. Add before a node");
        printf("\n5. Add after a node");
        printf("\n6. Delete a node");
        printf("\n7. Reverse the list");
        printf("\n8. Display the list");
        printf("\n9. Exit");
        printf("\nEnter your option: ");
        scanf("%d", &s);
        switch (s) {
            case 1:
                start = create(start);
                display(start);
                break;
            case 2:
                printf("Enter the data: ");
                scanf("%d", &data);
                start = addatbeg(start, data);
                display(start);
                break;
            case 3:
                printf("Enter the data: ");
                scanf("%d", &data);
                start = addatend(start, data);
                display(start);
                break;
            case 4:
                printf("Enter the data and item: ");
                scanf("%d %d", &data, &item);
                start = addbefore(start, data, item);
                display(start);
                break;
            case 5:
                printf("Enter the data and item: ");
                scanf("%d %d", &data, &item);
                start = addafter(start, data, item);
                display(start);
                break;
            case 6:
                printf("Enter the item: ");
                scanf("%d", &item);
                start = deleteNode(start, item);
                display(start);
                break;
            case 7:
                start = reverse(start);
                printf("The list is reversed\n");
                display(start);
                break;
            case 8:
                display(start);
                break;
            case 9:
                freeList(start); // Free memory before exiting
                break;
            default:
                printf("Invalid input\n");
        }
    } while (s != 9);
    return 0;
}

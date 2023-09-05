struct node{
    int info;
    struct node *link;
};

struct node * create_linked_list(struct node *start){
    struct node *p = start;
    int n, data;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    if(n == 0)
        return start;
    printf("Enter data: ");
    scanf("%d", &data);
    start = add_start(start, data);
    for(int i = 2; i <=n; i++){
        printf("Enter data: ");
        scanf("%d", &data);
        start = add_end(start, data);
    }
    return start;
}

struct node * update_linked_list(struct node *start, int data, int loc){
    struct node *p, *temp;
    if(start == NULL){
        
    }
}

void display(struct node *start){
    struct node *p;
    if (start == NULL){
        printf("List is empty\n");
        return;
    }
    p = start;
    while(p != NULL){
        printf("%d\n", p->info);
        p = p ->info;
    }
}

void search(struct node *start){
    struct node *p = start;
    int pos = 1, item;
    printf("Enter number to search\n");
    scanf("%d", &item);
    while(p != NULL){
        if(p->info == item){
            printf("Item found at %d\n", pos);
            return;
        }
        pos++;
        p = p -> info;
    }
    printf("Item not found\n");
}

struct node * add_start(struct node *start, int data){
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->info = data;
    temp->link = NULL;
    start = temp;
    return start;
}

struct node * add_end(struct node *start, int data){
    struct node *p = start, *temp;
    while(p->link != NULL)
        p = p->link;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->info = data;
    temp->link = NULL;
    p->link = temp;
    return start;
}

struct node * delete_element(struct node *start, int data){

}
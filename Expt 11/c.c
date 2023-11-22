#include <stdio.h>
#include <stdlib.h>
#define MAX 10
struct employee{
    int empid;
    char name[20];
    int age;
};
struct Record{
    struct employee info;
    struct Record *link;
}*table[MAX];

int hash(int key){
    return (key % MAX);
}

int search(int key){
    int h;
    struct Record *ptr;
    h = hash(key);
    ptr = table[h];
    while (ptr != NULL){
        if (ptr->info.empid == key)
            return h;
        ptr = ptr->link;
    }
    return -1;
}

void insert(struct employee emprec){
    int h, key;
    struct Record *tmp;
    key = emprec.empid;
    if (search(key) != -1){
        printf("Duplicate key\n");
        return;
    }
    h = hash(key);
    tmp = (struct Record *)malloc(sizeof(struct Record));
    tmp->info = emprec;
    tmp->link = table[h];
    table[h] = tmp;
}

void delete(int key){
    int h;
    struct Record *tmp,*ptr;
    h = hash(key);
    if (table[h] == NULL){
        printf("Key %d not found\n", key);
        return;
    }
    if (table[h]->info.empid == key){
        tmp = table[h];
        table[h] = table[h]->link;
        free(tmp);
        return;
    }
    ptr = table[h];
    while (ptr->link != NULL){
        if (ptr->link->info.empid == key){
            tmp = ptr->link;
            ptr->link = tmp->link;
            free(tmp);
            return;
        }
        ptr = ptr->link;
    }
    printf("Key %d not found\n", key);
}

void display(struct Record *table[]){
    int i;
    struct Record *ptr;
    for (i = 0; i < MAX; i++){
        printf("\n[%d] ", i);
        if (table[i] != NULL){
            ptr = table[i];
            while (ptr != NULL){
                printf("%d %s %d\t", ptr->info.empid, ptr->info.name, ptr->info.age);
                if (ptr->link != NULL)
                    printf("->\t");
                ptr = ptr->link;
            }
        }
    }
    printf("\n");
}

int main(){
    struct employee emp, emprec;
    int i, key, choice, n;
    for (i = 0; i <= MAX-1; i++)
        table[i] = NULL;
    printf("Enter number of employees: ");
    scanf("%d", &n);
    printf("Enter the employee details:\n");
	for(int i = 0; i < n; i++){
		printf("Employee %d:\n", i+1);
		printf("ID: ");
		scanf("%d", &emp.empid);
		printf("Name: ");
		scanf("%s", emp.name);
		printf("Age: ");
		scanf("%d", &emp.age);
		insert(emp);
		printf("-----------------------\n");
	}
    do{
        printf("1.Insert a record\n");
        printf("2.Search a record\n");
        printf("3.Delete a record\n");
        printf("4.Display table\n");
        printf("5.Exit\n");
        printf("Enter your choice\n");
        scanf("%d", &choice);
        switch (choice){
        case 1:
            printf("Enter the record\n");
            printf("Enter empid, name, age : ");
            scanf("%d%s%d", &emprec.empid, emprec.name, &emprec.age);
            insert(emprec);
            break;
        case 2:
            printf("Enter a key to be searched : ");
            scanf("%d", &key);
            i = search(key);
            if (i == -1)
                printf("Key not found\n");
            else
                printf("Key found in chain %d\n", i);
            break;
        case 3:
            printf("Enter a key to be deleted\n");
            scanf("%d", &key);
            delete(key);
            break;
        case 4:
            display(table);
            break;
        case 5: break;
        }
    } while(choice != 5);
}
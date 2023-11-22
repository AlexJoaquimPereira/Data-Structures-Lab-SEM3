#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10
enum type_of_record {EMPTY, DELETED, OCCUPIED};
int probing_method;

struct employee{
	int empid;
	char empname[20];
	char empaddr[50];
};

struct Record{
	struct employee info;
	enum type_of_record status;
}table[MAX];

int hash(int key){
	return key % MAX;
}

int double_hash(int key){
 	return (5 + (key % (MAX - 1)));
}

int collision_resolution(int h, int i, int key){
	switch(probing_method){
		case 1: return ((h + i) % MAX);//linear probing
		case 2: return ((h + i*i) % MAX);//quadratic probing
		case 3: return ((h + i*double_hash(key)) % MAX);//double hashing
	}
}

int search(int key){
	int i, h, location;
	h = hash(key);
	location = h;
	for(i = 1; i < MAX; i++){
		if(table[location].status == EMPTY)
			return -1;
		if(table[location].info.empid == key)
			return location;
		location = collision_resolution(h, i, key);
	}
	return -1;
}

void insert(struct employee emprec){
	int i, h, location;
	h = hash(emprec.empid);
	location = h;
	for (i = 1; i < MAX; i++){
		if(table[location].status == EMPTY || table[location].status == DELETED){
			table[location].info = emprec;
			table[location].status = OCCUPIED;
			return;
		}
		location = collision_resolution(h, i, emprec.empid);
	}
	printf("Table overflow\n");
}

void delete(int key){
	int location = search(key);
	if(location == -1)
		printf("Not found\n");
	else{
		table[location].status = DELETED;
		printf("Deleted\n");
	}
}

struct employee get_details(int i){
	struct employee temp;
	printf("Employee %d\n:", i+1);
	printf("ID: ");
	scanf("%d", &temp.empid);
	printf("Name: ");
	scanf("%s", temp.empname);
	printf("Address: ");
	scanf("%s", temp.empaddr);
	return temp;
}

void display(){
    int i;
    for (i = 0; i < MAX; i++){
        printf("[%d] : ", i);
        if (table[i].status == OCCUPIED){
            printf("Occupied : %d %s", table[i].info.empid, table[i].info.empname);
            printf(" %s\n", table[i].info.empaddr);
        }
        else if (table[i].status == DELETED)
            printf("Deleted\n");
        else
            printf("Empty\n");
    }
}

int main(){
	struct employee emp;
	int n, s, item;
	printf("1.Linear 2.Quadratic 3.Double hash\n");
	printf("Enter collision resolution technique: ");
	scanf("%d", &probing_method);
	printf("Enter number of employees: ");
	scanf("%d", &n);
	printf("Enter the employee details:\n");
	for(int i = 0; i < n; i++){
		printf("Employee %d:\n", i+1);
		printf("ID: ");
		scanf("%d", &emp.empid);
		printf("Name: ");
		scanf("%s", emp.empname);
		printf("Address: ");
		scanf("%s", emp.empaddr);
		insert(emp);
		printf("-----------------------\n");
	}
	do{
		printf("1. Insert a record\n");
 		printf("2. Search a record\n");
 		printf("3. Delete a record\n");
		printf("4. Display table\n");
 		printf("5. Exit\n");
 		printf("Enter your option:");
		scanf("%d", &s);
		switch(s){
			case 1: insert(get_details(n++));
					break;
			case 2: printf("Enter ID: ");
					scanf("%d", &item);
					item = search(item);
					if(item == -1)
						printf("Item not found\n");
					else printf("Item found at %dth location\n", item);
					break;
			case 3: printf("Enter ID: ");
					scanf("%d", &item);
					delete(item);
					break;
			case 4: display();
					break;
			case 5: break;
			default: printf("Invalid input\n");
		}
	}while(s != 5);
}

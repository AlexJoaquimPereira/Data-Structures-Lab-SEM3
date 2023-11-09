#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100
enum type_of_record {EMPTY, DELETED, OCCUPIED};
int ctech;

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

int collision_resolution(int h){
	//Enter switch for diff collision tech and return location;
	
}

int search(int key){
	int i, h, location;
	h = hask(key);
	location = h;
	for(i = 1; i < MAX; i++){
		if(table[location].status == EMPTY)
			return -1;
		if(table[location].info.empid == key)
			return location;
		location = collision_resolution(h);
	}
	return -1;
}

void insert(struct employee emprec){
	int i, h, location;
	h = hash(emprec.empid);
	location = h;
	for (i = 1; i < MAX; i++){
		if (table[location].status == EMPTY || table[location].status = DELETED){
			table[location].info = emprec;
			table[location].status = OCCUPIED;
			return;
		}
		location = collision_resolution(h);
	}
	printf("Table overflow\n");
}

void delete(int key){
	int location = search(key);
	if(location == -1)
		printf("Not found\n");
	else table[location].status = DELETED;
}

int main(){
	struct employee *arr;
	int n, s, item;
	printf("Enter number of employees: ");
	scanf("%d", &n);
	arr = (struct employee *)malloc(n * sizeof(struct employee));
	printf("Enter the employee details:\n");
	for(int i = 0; i < n; i++){
		printf("Employee %d\n:", i+1);
		printf("ID: ");
		scanf("%d", &arr[i].empid);
		printf("Name: ");
		scanf("%s", arr[i].empname);
		printf("Address: ");
		scanf("%s", arr[i].empaddr);
		printf("-----------------------\n");
	}
	do{
		printf("\n");
		printf("\n");
		printf("3. Exit\n");
		printf("Enter your option: ");
		scanf("%d", &s);
		switch(s){
			case 1: 
					break;
			case 2: 
					break;
			case 3: break;
			case 4: printf("Invalid input\n");
		}
	}while(s != 4);
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100
enum type_of_record {EMPTY, DELETED, OCCUPIED};
struct employee{
	int empid;
	char empname[20];
	char empaddr[50];
};

struct Record{
	struct employee info;
	enum type_of_record status;
};

int main(){
	struct employee *arr;
	int n, s, item;
	printf("Enter number of employees: ");
	scanf("%d", &n);
	arr = (struct employee *)malloc(n * sizeof(struct employee));
	printf("Enter the employee details:\n");
	for(int i = 0; i < n; i++){
		printf("Employee %d\n:", i+1);
		printf("ID: "):
		scanf("%d", &arr[i].empid);
		printf("Name: ");
		scanf("%s", arr[i].empname);
		printf("Address: ");
		scanf("%s", arr[i].empaddr);
		printf("-----------------------\n");
	}
	do{
		printf("1. Insert a record\n");
		printf("2. Binary search\n");
		printf("3. Exit\n");
		printf("Enter your option: ");
		scanf("%d", &s);
		switch(s){
			case 1: printf("Enter the ID: ");
					scanf("%d", &item);
					item = linear_search(arr, n, item);
					if(item == -1)
						printf("Item not found\n");
					else printf("Item found at %dth location", item);
					break;
			case 2: printf("Enter the ID: ");
					scanf("%d", &item);
					item = binary_search(arr, n, item);
					if(item == -1)
						printf("Item not found\n");
					else printf("Item found at %dth location", item);
					break;
			case 3: break;
			case 4: printf("Invalid input\n");
		}
	}while(s != 4);
}

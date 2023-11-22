#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

struct employee{
	int empid;
	char empname[20];
	char empaddr[50];
};

int linear_search(struct employee arr[], int n, int item){
	int i = 0;
	while(i < n && item != arr[i].empid)
		i++;
	if (i < n)
		return i;
	else return -1;
}

int binary_search(struct employee arr[], int n, int item){
	int low = 0, high = n - 1, mid;
	while(low <= high){
		mid = (low + high) / 2;
		if(arr[mid].empid == item)
			return mid;
		else if(arr[mid].empid > item)
			low = mid + 1;
		else high = mid - 1;
	}
	return -1;
}

int main(){
	struct employee arr[MAX];
	int n, s, item;
	printf("Enter number of employees: ");
	scanf("%d", &n);
	printf("Enter the employee details:\n");
	for(int i = 0; i < n; i++){
		printf("Employee %d:\n", i+1);
		printf("ID: ");
		scanf("%d", &arr[i].empid);
		printf("Name: ");
		scanf("%s", arr[i].empname);
		printf("Address: ");
		scanf("%s", arr[i].empaddr);
		printf("-----------------------\n");
	}
	do{
		printf("1. Linear search\n");
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
					else printf("Item found at %dth location\n", item);
					break;
			case 2: printf("Enter the ID: ");
					scanf("%d", &item);
					item = binary_search(arr, n, item);
					if(item == -1)
						printf("Item not found\n");
					else printf("Item found at %dth location\n", item);
					break;
			case 3: break;
			case 4: printf("Invalid input\n");
		}
	}while(s != 3);
}

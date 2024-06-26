# Data Structures Lab (Semester 3)
My programs for my Data Structures Laboratory course in Semester 3

## Experiment 1: Singly linked list
	1. Develop a C program to implement the following:
        a. Accept two polynomials from the user 
        b. Add the two polynomials
        c. Multiply the two polynomials
        d. Modify a given polynomial:
      	    i. Insert term
            ii. Delete term
        e. Accept the polynomials from a file
	2. Develop a C program to perform the following set operations using singly linked list.
      a. Set Union
      b. Set Intersection
      c. Set Difference

## Experiment 2: Stack data structure
	1. Develop a C program to implement the following
	- Convert infix to postfix
	- Convert infix to prefix
	- Evaluate a postfix expression
	- Evaluate a prefix expression

## Experiment 3:  Queue data structure
	1. Develop a C program to implement Efficient Circular Queue. Include the following functions:
	- Insert
	- Delete
	- Peek
	- Display
 	2. Create a Structure TASK with the following data fields:
	- TaskId(int)
 	- TaskTitle(char [])
	- TaskDuration (int) to be interpreted in seconds
 	- Status: Idle/ Queued/Completed
	
 	Create an array of TASK comprising of 10 tasks. (Preferably take input from file or initialise at compile time).
	
	Implement a Queue data structure to schedule task from the above array. Max size of Queue is 5. Your options should include the following:
	1. Enter the task id of the tasks to be scheduled (insert these in a queue). If the status is queued or completed ten do no allow scheduling. If the queue is full, ask the user to wait for a certain amount of time (Print the minimum time of waiting and the max waiting time to the user)
	2. Run the Tasks: delete the task at start of the queue and run it for the given taskDuration. (Use delay() function to suspend the running of the program for the indicated time). Once the task is completed prompt the user the menu and continue based on his choice.
	3. Display the details of tasks that are queued up.

## Experiment 4: LINKED LIST IMPLEMENTATION OF STACK AND QUEUE
	1. Develop a C program to implement Queues using Linked List
	2. Develop a C program to implement Stacks using Linked List and use the same to convert a postfix expression to its equivalent infix expression.

## Experiment 5: DOUBLY LINKED LIST AND CIRCULAR SINGLY LINKED LIST
	Develop a C program to implement the following
	1. Implement a doubly linked list(add, delete, reverse)
	2. Swap the adjacent elements of doubly linked list by rearranging the links.
	3. Create a doubly linked list in which the info part of each node contains a digit of a given number. The digits should be stored in reverse order. i.e., the least significant digit should be stored in the first node and the most significant digit should be stored in the last node.Example: If number entered in 5679 the list should be 9 -&gt; 7 -&gt;6 -&gt; 5. Write a function to add two numbers using the above linked list representation.
	4. Delete alternate nodes from a circular singly linked list

## Experiment 6: BINARY TREES
	Develop a C program to create a binary tree given its Inorder and Postorder traversal.
	Provide options to the user to perform the following operations on the binary tree:
	1. Display the height of the tree
	2. Return the depth of a given node in a tree
	3. Perform Level order traversal

## Experiment 7: BINARY SEARCH TREES
	Develop a C program to create a binary search tree and perform the following operations 
	1. Insertion of a new element
	2. Deletion of an existing element
	3. Searching for a given element
	4. Perform in order, pre order and post order traversals
	5. Find the maximum and minimum value

## Experiment 8: THREADED BINARY SEARCH TREES
	Develop a C program to create a Threaded Binary Search tree.
	Provide options to the user to perform the following operations on the binary tree:
	1. Insertion of a new element
	2. Deletion of an existing element
	3. Searching for a given element
	4. Performing inorder and preorder traversal on the tree.

## Experiment 9: AVL (Adelson-Velsky and Landis) TREE
	Develop a C program to create an AVL tree and perform the following operations 
	1. Insertion of a new element
	2. Deletion of an existing element
	3. Searching for a given element
	4. Find the maximum and minimum value

## Experiment 10: GRAPHS
	Develop a C program to implement a directed graph G = (V, E) having |V|=8 and |E|=12.
	Perform the following operations on the graph using an adjacency matrix:
	1. Display Breadth First Traversal
	2. Display Depth First Traversal
	Perform the following operations on the graph using an adjacency list:
	1. Add a new vertex
	2. Delete a vertex
	3. Add a new edge
	4. Delete an edge

## Experiment 11: Hashing and Searching 
	1. Implement linear search and binary search using an employee structure (structure should have id, name and address).
	2. Implement hashing using following collision resolution techniques
		• Linear Probing
		• Quadratic probing
		• Double hashing
	3. Implement hashing using separate chaining

## Experiment 12: SORTING
	Develop a C program to implement the following sorting algorithms:
	1. Insertion Sort using a character array
	2. Merge Sort using a linked list
	3. Quick Sort
	4. Heap Sort

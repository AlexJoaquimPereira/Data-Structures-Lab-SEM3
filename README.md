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

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
};

// Function to create a new node
struct node* createNode(int value) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new element into the BST
struct node* insert(struct node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

// Function to find the minimum value in the BST
struct node* findMin(struct node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to delete an element from the BST
struct node* deleteNode(struct node* root, int value) {
    if (root == NULL) {
        return root;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

// Function to search for an element in the BST
struct node* search(struct node* root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }

    if (value < root->data) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

// Function for in-order traversal
void inOrder(struct node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

// Function for pre-order traversal
void preOrder(struct node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Function for post-order traversal
void postOrder(struct node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

// Function to find the maximum value in the BST
struct node* findMax(struct node* root) {
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

int main() {
    struct node* root = NULL;
    int choice, value;

    do {
        printf("\nBinary Search Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. In-order Traversal\n");
        printf("5. Pre-order Traversal\n");
        printf("6. Post-order Traversal\n");
        printf("7. Find Maximum\n");
        printf("8. Find Minimum\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (search(root, value) != NULL) {
                    printf("%d found in the tree.\n", value);
                } else {
                    printf("%d not found in the tree.\n", value);
                }
                break;
            case 4:
                printf("In-order Traversal: ");
                inOrder(root);
                printf("\n");
                break;
            case 5:
                printf("Pre-order Traversal: ");
                preOrder(root);
                printf("\n");
                break;
            case 6:
                printf("Post-order Traversal: ");
                postOrder(root);
                printf("\n");
                break;
            case 7:
                if (root == NULL) {
                    printf("Tree is empty.\n");
                } else {
                    struct node* maxNode = findMax(root);
                    printf("Maximum value: %d\n", maxNode->data);
                }
                break;
            case 8:
                if (root == NULL) {
                    printf("Tree is empty.\n");
                } else {
                    struct node* minNode = findMin(root);
                    printf("Minimum value: %d\n", minNode->data);
                }
                break;
            case 9:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);

    return 0;
}

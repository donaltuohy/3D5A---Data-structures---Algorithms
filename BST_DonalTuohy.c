//3D5A - Assignment 3
//Name:				Donal Tuohy
//Student Number:	14313774
//Date:				18/11/16


#include <stdio.h>
#include <stdlib.h>

typedef struct BST_Node BST_Node;
struct BST_Node {
	BST_Node *left, *right;
	char data;
};

//To change the amount of chars to sort all you have to do is change this
#define SIZE_OF_ARRAY 26
char List_of_char[SIZE_OF_ARRAY];

//Swap the values at two indices of the global array
void swap(int a, int b) {
	char c = List_of_char[a];
	List_of_char[a] = List_of_char[b];
	List_of_char[b] = c;
}

//Returns the index where the divide is 
int partition(int first, int last) {				//Take in a section of the array from first to last
	int pivot_value = List_of_char[last];			//Set the pivot value to the last number in the section
	int prev_index = first - 1;						//Set the divide before the first number
	for (int current_index = first; current_index < last; current_index++) {  //Run for the length of the section
		if (List_of_char[current_index] < pivot_value) {		//if the current value is les than the pivot value
			prev_index++;									//Move the divide forward 1
			swap(prev_index, current_index);				//Swap the current value with the one behind the divide -- so now anything less than the pivot will be left of the divide
		}
	}
	swap(last, prev_index + 1);								//End of for loop so place the pivot in betwwen all the values lower and higher than it. This is now it's final position
	return prev_index + 1;									//Return the index of the divide so quicksort can use it to sort either side recursively
}

//Sorts the rhs and left hand side of the divide recursively.
void quicksort(int first, int last);
void quicksort(int first, int last) {
	int divide_index = 0;
	if (first < last) {								//If there is still a section to be sorted
		divide_index = partition(first, last);		//This is the index of the partition of the section
		quicksort(first, divide_index - 1);			//Recursively sort the left hand side of the partition
		quicksort(divide_index + 1, last);			//Recursively sort the right hand side of the partition
	}
}

//This is a recursive function that inserts a node into 
//a binary search tree.
void insert_tree_node(BST_Node* root, char data);
void insert_tree_node(BST_Node* root, char data) {
	if (!root)
		return;
	if (data < root->data) {										//If data is less than root 
		if (root->left != NULL) {									//If left child is not NULL 
			insert_tree_node(root->left, data);						//Recurse on the left subtree
		}
		else {														//If left child is NULL
			root->left = (BST_Node*)malloc(sizeof(BST_Node));		//Create memory the size of a node and set it to the left child of the parent
			root->left->data = data;								//Fill it with the data entered in the original parameter
			root->left->left = root->left->right = NULL;			//Set the children of the new node equal to NULL
			printf("%c added left of %c\n", data, root->data);
		}
	}
	else {															//Otherwise the data is greater than the root
		if (root->right != NULL) {									//If right child is not NULL 
			insert_tree_node(root->right, data);					//Recurse on the right subtree	
		}
		else {														//If right child is NULL
			root->right = (BST_Node*)malloc(sizeof(BST_Node));		//Create memory the size of a node and set it to the right child of the parent
			root->right->data = data;								//Fill it with the data entered in the original parameter
			root->right->left = root->right->right = NULL;			//Set the children of the new node equal to NULL
			printf("%c added right of %c\n", data, root->data);
		}
	}
}

//Goes through the tree recursively,
//printing out each node.
void tree_print_sorted(BST_Node* root);
void tree_print_sorted(BST_Node* root) {

		if (!root) {										//Checking if the top node equals NULL
			printf("\nThe Binary Search Tree is empty\n");
			return;											//If so, exit function.
		}
		if (root->left == NULL) {				//If you're at the the end of the left branch.
			printf("%c, ", root->data);			//Print the value as it will be the lowest.
		}
		else {									//If there is another node to the left.
			tree_print_sorted(root->left);		//Recurse this function again until you reach the end.
			printf("%c, ", root->data);			//When the levels below have finished recursing, print the value at the top of the current tree.
		}

		if (root->right == NULL) {				//If you're at the end of the right branch.
			return;								//You're done.
		}
		else {									//If there is more on the right.
			tree_print_sorted(root->right);		//Recurse through each tree on the right.
		}
		
	}

//Traverses throught the tree left then 
//right deleteing the tree as it moves inwards.
void tree_delete(BST_Node* root);
void tree_delete(BST_Node* root){
	if (!root)														//Check if the tree is there.
		return;														//Exit if not.
	if (root->left != NULL)											//If there is a child to the left.
		tree_delete(root->left);									//Recurse with the left child as the root.
	 if(root->right != NULL)										//If there is a child on the right.
		tree_delete(root->right);									//Recurse with the right child as the root.

	printf("The node with %c is deleted. \n", root->data);
	free(root);														//Delete the memory of a node when its children are NULL.
}

// Returns a pointer to the node where the value is contained. 
// If not in the binary search tree it, returns NULL.
BST_Node* tree_search(BST_Node* root, char data) {
	BST_Node* temp = root;				//Create a temporary node pointer to tranverse through the tree.

	while (temp) {						//Keep checking nodes until you reach the end.
		if (data == temp->data) {		// If you find the data in a node, return a pointer to that node.
			return temp;
		}
		if (data < temp->data) {		//If the data is less then the value in the current node.
			temp = temp->left;			//Set the current to the left child of that node.
		}
		if (data > temp->data) {		//If the data is greater then the value in the current node.
			temp = temp->right;			//Set the current to the right child of that node.
		}	
	}
	return NULL;						//If the data could not be found, return NULL.
}

//Uses a algorithm similiar to quicksort. 
//Divides array, then sets the middle as the parent.
//It then recursively divides the left and right,
//setting the middle either side as the child of
//the middle from the last recursion. Continues this 
//until the binary tree is balanced.
void balance_tree(BST_Node* root, int first, int last, int length);
void balance_tree(BST_Node* root, int first, int last, int length) {
	
	if (root == NULL) {													//If the root = null
		printf("No tree to balance. \n");								//Error message
		return;															//Finish function
	}
	if (length < 1) {													//If the length of the section is less than 1, so it cannot go negative or 0;
		return;
	}
	if (length <= 2) {													//If the length of the section is 1 or 2
		insert_tree_node(root, List_of_char[first]);					//insert the first part of the section 
		if (length == 2) {												//if the length = 2, it means you need to insert the second part of the section
			insert_tree_node(root, List_of_char[last]);					//insert the the second part of the section
		}																//This recursion is now done as it has been reduced down to one or two values which have been inserted
	}
	else {																//This else runs if the length is greater than two
		int middle =first + length / 2;									//Set the middle point index
		if (length != SIZE_OF_ARRAY) {									//The root has been set in main, this if means if it is the first recursion it will not set the root twice
			insert_tree_node(root, List_of_char[middle]);				//Insert the current middle into the tree
		}
		balance_tree(root, first, middle - 1, middle - first);			//Recurse the function for the left hand side
		balance_tree(root, middle + 1, last, last - (middle ));			//Recurse the function for the right hand side
	}
}

int main() {

	BST_Node* root = (BST_Node*)malloc(sizeof(BST_Node));						//Allocating memory for the root.

	if (!root) 
		fprintf(stderr, "ERROR: out of memory %s:%i\n", __FILE__, __LINE__);	//If the malloc didn't work, show the line where the error is.

	for (int i = 0; i < SIZE_OF_ARRAY ; i++) {
		List_of_char[i] = 'A' + i;												//Fill the array with values from A up to the size of the array.
	}
	
	quicksort(0, SIZE_OF_ARRAY-1);												//Use the quicksort function to sort the array from smallest to largest.

	int middle = SIZE_OF_ARRAY / 2;												//Find the middle of the array.
	root->data = List_of_char[middle];											//Put that char into the root.
	root->left = root->right = NULL;											//Set root's children to NULL.
											
	balance_tree(root ,0, SIZE_OF_ARRAY-1, SIZE_OF_ARRAY);						//A function which splits up the array and balances the by inserting data in a certain order.

	tree_print_sorted(root);													//Print the tree when it is all inserted, should print the sorted array.
	printf("\n");
	tree_delete(root);															//Use the delete function to delete every node in the tree.
	printf("All Nodes deleted.\n\n");
	
	


}
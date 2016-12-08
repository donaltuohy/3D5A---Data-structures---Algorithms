//Donal Tuohy


#include <stdio.h>
#include <string.h>
#include <time.h>


#define SIZE_OF_ARRAY 10				//To change the amount of numbers to sort all you have to do is change this

int List_of_num[SIZE_OF_ARRAY];			//Array for quicksort
int List_of_num2[SIZE_OF_ARRAY];		//Array for selection sort
int quick_sort_probes = 0;			//Count for quicksort
int selection_sort_probes = 0;			//Count for selection sort

//Fills the array with random numbers
void fill_array(){
	srand(time(NULL));									//Set the seed for the random numbers
	for (int i = 0; i < SIZE_OF_ARRAY; i++) {			
		List_of_num[i] = rand()%(SIZE_OF_ARRAY*10);		//Set each value to a random number modded by the size*10 so that they are not too big
		List_of_num2[i] = List_of_num[i];				//Just copying the array so that the different functions sort the same array
	}
}

//Prints out the array used for quicksort in one line
void print_list_quicksort() { 
	for (int i = 0; i < SIZE_OF_ARRAY; i++) {
		printf("%i, ", List_of_num[i]);
	}
	printf("\n");
}

//Prints out the array used for selection sort in one line
void print_list_selection_sort() {
	for (int i = 0; i < SIZE_OF_ARRAY; i++) {
		printf("%i, ", List_of_num2[i]);
	}
	printf("\n");
}

//Takes 2 indices and swap the values in the array
void swap(int a, int b) {
	int c = List_of_num[a];
	List_of_num[a] = List_of_num[b];
	List_of_num[b] = c;
}

void swap_selection_sort(int a, int b) {
	int c = List_of_num2[a];
	List_of_num2[a] = List_of_num2[b];
	List_of_num2[b] = c;
}

//Returns the index where the divide is 
int partition(int first, int last) {				//Take in a section of the array from first to last
	int pivot_value = List_of_num[last];			//Set the pivot value to the last number in the section
	int prev_index = first - 1;						//Set the divide before the first number
	for (int current_index = first; current_index < last; current_index++) {  //Run for the length of the section
		if (List_of_num[current_index] < pivot_value) {		//if the current value is les than the pivot value
			prev_index++;									//Move the divide forward 1
			swap(prev_index, current_index);				//Swap the current value with the one behind the divide -- so now anything less than the pivot will be left of the divide
		}
		quick_sort_probes++;								//Add one to the global count of probes
	}
	swap(last, prev_index + 1);								//End of for loop so place the pivot in betwwen all the values lower and higher than it. This is now it's final position
	return prev_index + 1;									//Return the index of the divide so quicksort can use it to sort either side recursively
}

//Uses partition function and recursion to sort the array
void quicksort(int first, int last) {
	int divide_index = 0;
	if (first < last) {								//If there is still a section to be sorted
		divide_index = partition(first, last);		//This is the index of the partition of the section
		quicksort(first, divide_index - 1);			//Recursively sort the left hand side of the partition
		quicksort(divide_index + 1, last);			//Recursively sort the right hand side of the partition
	}

}

//Sorts the array using selection sort
void selection_sort() {
	int current = 0;

	for (int i = 0; i < SIZE_OF_ARRAY; i++) {		//first for loop 
		current = List_of_num2[i];					//The number to start coparing at
		for (int j = i; j < SIZE_OF_ARRAY; j++){	//Start at i every time as we want sorted values to stay in their place
			selection_sort_probes++;				//Add 1 to the probe count
			if (current > List_of_num2[j]) {		//If the current is greater than the number we're comparing 
				swap_selection_sort(i, j);			//Swap the values at the current and the original value
				current = List_of_num2[i];			//Set the current equal to the new lower value
			}
		}
	}
}


int main()
{
	//Quicksort Part
	{
		fill_array();
		printf("Original List\n-----------------\n");
		print_list_quicksort();
		int last = SIZE_OF_ARRAY - 1;
		quicksort(0, last);
		printf("\nQuicksorted List - Probes: %i\n-----------------\n", quick_sort_probes);
		print_list_quicksort();
	}

	//Selection Sort Part
	{
		printf("\n\nOriginal List\n-----------------\n");
		print_list_selection_sort();
		selection_sort();
		printf("\nSelection Sorted List - Probes: %i\n-----------------\n", selection_sort_probes);
		print_list_selection_sort();
	}


	return 0;
}


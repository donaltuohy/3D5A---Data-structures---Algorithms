//Donal Tuohy
//Student Number: 14313774
//Dijkstra Assignment - Module 3D5A

#include <stdio.h>
#include <string.h>

#define MAX_NODES 12

//This struct is for each edge
typedef struct Edge Edge;
struct Edge {
	char Linked_char;
	int Weight;
	Edge* next_edge;
	int visited;
};

//This struct is for each Node and contains the pointer to the first edge on the linked list
typedef struct Node Node;
struct Node {
	char letter;
	char parent;
	int number_of_edges;
	int shortest_path_cost;
	Edge* first_edge;
	int visited;
	int permanent;
	int paths_checked;
};

Node Nodes[MAX_NODES];			//This is the global array which stores the nodes of the program
int Visited_Nodes[MAX_NODES];	//Parralel array which tells us which nodes were visited

//This function is just a simple way of getting the index of a node by entering the character
int index_of_char(char i) {
	int result = i - 'A';
	return result;
}

//This function takes in the index of a node, the char of the node it's been linked to, and the weight of the edge
void new_edge(int index, char letter, int weight) {	
	Edge* new_edge = (Edge*)malloc(sizeof(Edge));			//Allocate memory for the new edge
	new_edge->Linked_char = letter;					//Fill the new node with the inputs into the function
	new_edge->Weight = weight;
	new_edge->next_edge = NULL;

	Edge* current = Nodes[index].first_edge;		//Create a temporary edge pointer that points to the first edge for that node
	
	if (current == NULL) {							//If there is no edges for that node
		Nodes[index].first_edge = new_edge;			//Make the first edge of the node equal to the new edge 
		Nodes[index].number_of_edges = 1;			//Adjust the number of nodes
		//printf("%c added as an edge to %c \n", Nodes[index].first_edge->Linked_char, 'A' + index);
	}
	else {											//If there is already an edge attached to the node
		while (current->next_edge != NULL) {		//Tranverse to the last edge
			current = current->next_edge;			
		}
		current->next_edge = new_edge;				//Set the last edges's next edge equal to the new edge
		//printf("%c added as an edge to %c\n", current->next_edge->Linked_char, 'A' + index);
		Nodes[index].number_of_edges++;				//Increment the count of edges for this node
	}
	return;
}

//This function just is hard code to build the graph using the new edge function
void add_edges() {
	//Start with node A and add B
	{
		new_edge(0,'B', 1);
	}
	//B has three edges to A, C, B
	{
		new_edge(1, 'A', 1);
		new_edge(1, 'C', 2);
		new_edge(1, 'D', 2);
		
	}
	//C has three edges to B, E, F
	{
		new_edge(2, 'B', 2);
		new_edge(2, 'E', 3);
		new_edge(2, 'F', 2);
		
	}
	//D has two edges to B, G
	{
		new_edge(3, 'B', 2);
		new_edge(3, 'G', 2);
		
	}
	//E has one edge to C
	{
		new_edge(4, 'C', 3);
		
	}
	//F has four edges to C, H, I, J
	{
		new_edge(5, 'C', 2);
		new_edge(5, 'H', 1);
		new_edge(5, 'I', 2);
		new_edge(5, 'J', 4);

	}
	//G has four edges to D, J, K, L
	{
		new_edge(6, 'D', 2);
		new_edge(6, 'J', 1);
		new_edge(6, 'K', 2);
		new_edge(6, 'L', 3);

	}
	//H has one edge to F
	{
		new_edge(7, 'F', 2);
		
	}
	//I has two edges to F, K
	{
		new_edge(8, 'F', 2);
		new_edge(8, 'K', 11);
	
	}
	//J has three edges to F, G, L
	{
		new_edge(9, 'F', 2);
		new_edge(9, 'G', 1);
		new_edge(9, 'L', 2);

	}
	//K has two edges to G, I
	{
		new_edge(10, 'G', 2);
		new_edge(10, 'I', 11);
		
	}
	//L has two edges to G, J
	{
		new_edge(11, 'G', 3);
		new_edge(11, 'J', 5);

	}
}

//Prints each vertex and it's linked list of vertices it's connected to
void print_graph() {

	for (int i = 0; i < MAX_NODES; i++) {				//For loop that iterates through the global array of each vertice
		printf("%c:  ", Nodes[i].letter);				//Print the Letter of the current node
		Edge* current = Nodes[i].first_edge;			//Create a new edge poiner to iterate through the linked list of edges for each vertice
		while (current != NULL) {							//Tranverse through the linked list of edges and print each one till you get to the end 
			printf("%c, ", current->Linked_char);
			current = current->next_edge;
		}
		printf("\n");
	}
}

//Depth first search through graph
int DFS(char start_at, char find_value);
int DFS(char start_at, char find_value) {

	Node* vertex = &(Nodes[index_of_char(start_at)]);			//Create a vertex pointer and set it to the address of the vertex which contains the start at char

	if (vertex->visited == 1)									//If the vertex has been visited, return 0
		return 0;
	else {														//If not print the letter
		printf("%c, ", vertex->letter);
	}

	int recursive_call = 0;

	

	Edge* current = vertex->first_edge;			//Create a current edge pointer to tranverse through the edges
	vertex->visited = 1;						//Set the current vertex to visited 

	while (current != NULL && current->Linked_char != find_value) {			//Stop when you reach the end of the linked list or if you find the target
		Node* node_index = &(Nodes[index_of_char(current->Linked_char)]);	//Create a vertex pointer to the address of the current edge linked letter

		recursive_call = DFS(node_index->letter, find_value);				//Recurseively call the function and pass the return into the variable
		if (recursive_call == 0) {											//If the function returns 0
			current = current->next_edge;									//Check the next edge
		}
		else if (recursive_call == 1) {										//If it reurns 1, the value has been found at a lower level, so get out of there
			break;
		}
	}


	if (current == NULL) {			//If the while loop quit because it was Null, return 0.
		return 0;
	}
	
	else if (current->Linked_char == find_value) {			// If the while loop quit becasue it found the target vertex, print the letter and return 0.
		printf("%c, ", current->Linked_char);
		return 1; // Path found
	}
	else if(recursive_call == 1)							//If in a low down recursion level and the target was found, keep passing 1 back up the levels.
	{
		return 1;
	}
	else {													//Nothing was found, return 0.
		return 0;
	}


	
}


//Prints the DFS details in a nice layout
void DFS_print(char a, char b) {
	printf("DFS from %c to search for %c: ", a, b);	
	int answer = DFS(a, b);								//Call the DFS function, returns 1 if found, 0 if not 

	if (answer == 1) {
		printf("\nTarget Found - HALT\n\n");
	}
	else {
		printf("\nTarget Not Found\n\n");
	}

	for (int i = 0; i < MAX_NODES; i++)			//Resetting the visited boolean once it is finished
		Nodes[i].visited = 0;

}

int Dijkstra(char start_at, char find_value, int total_weight);
int Dijkstra(char start_at, char find_value, int total_weight) {

	Node* current_vertex = &(Nodes[index_of_char(start_at)]);					//Create a ointer to the current vertex
	Edge* current_edge = current_vertex->first_edge;							//Create a pointer to the first edge of this vertex
	current_vertex->shortest_path_cost = total_weight;							//Set the current vertex's cost to the weight passed throught the recursion
	current_vertex->permanent = 1;												//Set the vertex as permanent

	for (int i = 0; i < current_vertex->number_of_edges; i++)					//Have a for loop run for the amount of edges on this vertex
	{
		if (current_edge != NULL){												//Just a safety hazard, won't get a segmantation fault, just lets the for loop run out
			int current_edge_index = index_of_char(current_edge->Linked_char);	//Just creating some variables so that the index of char function doesn't have to be called loads
			char current_edge_char = current_edge->Linked_char;

		if (Nodes[current_edge_index].permanent == 1 && Nodes[current_edge_index].number_of_edges != 1) {													//If the node has been visited and the node isn't just out on it's own like E or H
			if (Nodes[current_edge_index].shortest_path_cost > current_edge->Weight + total_weight || Nodes[current_edge_index].shortest_path_cost == 0) {	//If the current path to the node is more expensive than the one you have, or if there is no current cost in the node
				Nodes[current_edge_index].shortest_path_cost = current_edge->Weight + total_weight;															//Set the current path to the cheaper path
				Nodes[current_edge_index].parent = start_at;																								//Set the parent of the node so that it is on this path
				int Dijk_branch = Dijkstra(current_edge_char, find_value, Nodes[current_edge_index].shortest_path_cost);									//Look at all of this nodes edges with the new cost
				current_edge = current_edge->next_edge;																										//Once out of that recursion, go to the next edge of this level

			}
			else {											//If the path already at the node was cheaper, move on
				current_edge = current_edge->next_edge;
			}
		}
		else if ( Nodes[current_edge_index].permanent == 1 && Nodes[current_edge_index].number_of_edges == 1) { //this will happen if the node is out on it's own. It'll just move on, once it has been visited once
			current_edge = current_edge->next_edge;
		}
		else                    //This will happen if the node hasn't been visited already
		{
			if (Nodes[current_edge_index].shortest_path_cost > current_edge->Weight + total_weight || Nodes[current_edge_index].shortest_path_cost == 0) {
				Nodes[current_edge_index].shortest_path_cost = current_edge->Weight + total_weight;
				Nodes[current_edge_index].parent = start_at;
				int Dijk_branch = Dijkstra(current_edge_char, find_value, Nodes[current_edge_index].shortest_path_cost);
				current_edge = current_edge->next_edge;

			}
			else {
				current_edge = current_edge->next_edge;
			}

		}
	}
	
	}

	
}


void Dijkstra_print(char a, char b) {
	printf("Dijkstra path from '%c' to '%c': \n", a, b);
	int answer = Dijkstra(a, b, 0);				//Call the function

	for (int i = 0; i < MAX_NODES; i++)			//Iterate through the nodes to print every node out with it's corresponding length and parent
	{
		if (Nodes[i].shortest_path_cost != 0)
			printf("%c length %d, parent %c\n", Nodes[i].letter, Nodes[i].shortest_path_cost, Nodes[i].parent);
		Nodes[i].parent = 0;				//Reset the parent and length so function can be used again
		Nodes[i].shortest_path_cost = 0;
	}

	if (index_of_char(b) > MAX_NODES) {
		printf("Target does not exsist!\n");
	}
	else {
		printf("Target found - HALT\n");
	}

	printf("\n\n");
}

int main() {
	
	for (int i = 0; i < 12; i++) {			//Use a for loop to fill the array
		Nodes[i].letter = 'A' + i;			//Give each index it's char
		Nodes[i].visited = 0;				//Set them all to unvisited
	}


	add_edges();
	//print_graph();

	DFS_print('A', 'X');
	DFS_print('K', 'B');

	Dijkstra_print('A', 'X');
	Dijkstra_print('A', 'J');
}
/*
*   Name:           Donal Robert Tuohy
*   Student No:     14313774
*`  Module:         3D5A - Data Structures & Algorithms
*   Assignment:     Hash Tables Assignment - Week 5
*   Date:           26/10/16
*/
#include <stdio.h>
#include <string.h>

//
// i #define array lengths so i only have to change them in one place
#define NUM_TEST_KEYS 13
#define MAX_KEY_LENGTH 16
#define HASH_TABLE_SIZE_M 17


// -- the hash table itself --
char hash_table[HASH_TABLE_SIZE_M][MAX_KEY_LENGTH];
char hash_table2[HASH_TABLE_SIZE_M][MAX_KEY_LENGTH];

// -- the double hash function --
// This function returns a value for which the double hash table use. It will be the value that will be stepped by a
int double_hash_function( const char *key, int table_size ) {
	int index = 0;
	int sum = 0;
	int ascii_val = 0;


	for(int i = 0; i < MAX_KEY_LENGTH; i++){

        ascii_val = (int)key[i];    //Find the ASCII value for each character of the word
        sum = sum + ascii_val;      //Sum all the values

        }

     ascii_val = (int)key[0];       // take the first letter ASCII value away from the index
     sum = sum - ascii_val;

    index = sum % (HASH_TABLE_SIZE_M/2) + 1;    //This value is the double hash index

    return index;
}


// --Linear Probing Function--
int hash_function( const char *key, int table_size ) {
	int index = 0;
	int sum = 0;
	int ascii_val = 0;

	//
	// write your hash function here
	//
	for(int i = 0; i < MAX_KEY_LENGTH; i++){

        ascii_val = (int)key[i];    //Find the ASCII value for each character of the word
        sum = sum + ascii_val;      //Sum all the values
        }

     ascii_val = (int)key[0]; // Add the first letter value to the index
     sum = sum + ascii_val;

    index = sum % HASH_TABLE_SIZE_M + 1;    //This is the value for index when doing linear probing


    while(0 != hash_table[index][0] ){

        index++;
        if (index > HASH_TABLE_SIZE_M){
            index = 1;
            }
    }



    strcpy(hash_table[index], key); //Put the string into the hash table at its index

	return index;
}

// --Double Hashing Function--
int hash_function_part_2( const char *key, int table_size ) {
	int index = 0;
	int sum = 0;
	int ascii_val = 0;


	for(int i = 0; i < MAX_KEY_LENGTH; i++){

        ascii_val = (int)key[i];        //Find the ASCII value for each character of the word
        sum = sum + ascii_val;          //Sum all the values

        }

     ascii_val = (int)key[0];       // Add the first letter value to the index
     sum = sum + ascii_val;

    index = sum % HASH_TABLE_SIZE_M + 1;    //This gives us the first index
    int index2 = 0;

     while(0 != hash_table2[index][0] ){


        index2 = double_hash_function(key, HASH_TABLE_SIZE_M);  //This returns the value of the second index if the first is the same
        index = index + index2;     //This is where the double hashing differs from the linear probing
                                    //Instead of going to the next one down, it steps the value of index 2.
        if (index > HASH_TABLE_SIZE_M){
            index = index % HASH_TABLE_SIZE_M; //This makes the indexing loop around
            }
    }


    strcpy(hash_table2[index], key);

	//
	// consider counting the number of probes it takes to store
	// your key and printing that out

	return index;
}


int main() {
    //Quick check so that there isn't more values than the size of the hash map
    if(NUM_TEST_KEYS > HASH_TABLE_SIZE_M){
        printf("There is too many names, increase the hash table size.\n");
        return 0;
    }
	//
	// example: array of test strings to use as keys
	char test_strings[NUM_TEST_KEYS][MAX_KEY_LENGTH] = {
		"Prince Adam", "Orko", "Cringer", "Teela", "Aleet", "Princess Adora", "Orko", "Anna", "Anna", "Eoin", "Jim", "Donal", "Gerry"
	};

	//
	// example: store each key in the table and print the index for each test key
	printf(
		"              key|   table index|  double index|\n---------------------------------------------------------\n" );
	for ( int i = 0; i < NUM_TEST_KEYS; i++ ) {
		int index = hash_function( test_strings[i], HASH_TABLE_SIZE_M );
		int index2 = hash_function_part_2(test_strings[i], HASH_TABLE_SIZE_M );


		// the %16s means print a string (%s) but pad it to 16 spaces

		printf( "%16s | %12i | %12i |\n", test_strings[i], index, index2 );

	}

	printf("---------------------------------------------------------\n\n");

    //Printing out the first hash map in order of index, just to visualise the table
	for ( int i = 1; i <= HASH_TABLE_SIZE_M; i++ )
        {
            printf("%i. ", i);
	    if( 0 ==  hash_table2[i][0]){
            printf("---//--- \n");
	    }else{
            printf("%s \n", hash_table2[i]);
            }
	}
	//
	// calculate table load here
	//

	return 0;
}

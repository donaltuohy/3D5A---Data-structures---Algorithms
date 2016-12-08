//Donal Tuohy
//

#include <stdio.h> // printf() etc.
#include <string.h> // strcpy(), strlen() etc.

//
// i #define array lengths so i only have to change them in one place
#define NUM_TEST_KEYS 9
#define MAX_KEY_LENGTH 16
#define HASH_TABLE_SIZE_M 17

//
// -- the hash table itself --
char hash_table[HASH_TABLE_SIZE_M][MAX_KEY_LENGTH];


//
// -- example hash function skeleton --
// if it finds the key in the table it should return that index
// otherwise return the appropriate empty index or -1 if table is full
int hash_function( const char *key, int table_size ) {
	int index = 0;
	int sum = 0;
	int ascii_val = 0;

	//
	// write your hash function here
	//
	for(int i = 0; i < MAX_KEY_LENGTH; i++){

        ascii_val = (int)key[i];
        sum = sum + ascii_val;

        }

     ascii_val = (int)key[0]; // Add the first letter value to the index
     sum = sum + ascii_val;

    index = sum % HASH_TABLE_SIZE_M + 1;

    int count = 0;

    while(0 != hash_table[index][0] && (count < HASH_TABLE_SIZE_M)){

        index++;
        count++;
        if (index > HASH_TABLE_SIZE_M){
            index = 1;
            }
    }

    strcpy(hash_table[index], key);

	//
	// consider counting the number of probes it takes to store
	// your key and printing that out

	return index;
}

int main() {

	//
	// example: array of test strings to use as keys
	char test_strings[NUM_TEST_KEYS][MAX_KEY_LENGTH] = {
		"prince adam", "orko", "cringer", "teela", "aleet", "princess adora", "orko", "anna", "anna"
	};

	//
	// example: store each key in the table and print the index for each test key
	printf(
		"             key      table index\n-----------------------------------\n" );
	for ( int i = 0; i < NUM_TEST_KEYS; i++ ) {
		int index = hash_function( test_strings[i], HASH_TABLE_SIZE_M );


        //hash_table[index] = test_strings[i];
		//
		// i would check for errors and store the keys in the table here
		//

		// the %16s means print a string (%s) but pad it to 16 spaces

		printf( "%16s %6i\n", test_strings[i], index );

	}

	//
	// calculate table load here
	//

	return 0;
}

/**
 * @file virus_scan.c
 * @brief In-Memory Pattern Matching (Virus Detection Algorithm)
 * 
 * This program simulates a security scan by searching for a specific 
 * malicious pattern (virus signature) within a simulated memory dump.
 * It utilizes a sliding window approach and pointer arithmetic to 
 * detect matches and count occurrences.
 */

#include <stdio.h>
#include <string.h>

// Function prototype for pattern matching
int detectVirus (char *memoryDump , char *virusSignature , int *ptr);

int main(void)
{
	char memory[100];
	char Vsignature[50];
	int m;
	int v;
	int status;
	int *ptr;
	int count;
	
	ptr = &count;
	
	// Step 1: Receive the simulated memory dump from the user
	printf("Enter the memory dump: ");
	fgets(memory , sizeof(memory) , stdin);
	
	// Step 2: Receive the targeted virus signature to scan for
	printf("\nEnter the virus signature: ");
	fgets(Vsignature , sizeof(Vsignature) , stdin);
	
	m = strlen(memory);
	v = strlen(Vsignature);
	
	// Null-terminate the strings safely (Note: fgets includes the newline character)
	memory[m] = '\0';
	Vsignature[v] = '\0';
	
	// Step 3: Execute the detection algorithm
	status = detectVirus(memory , Vsignature , &count);
	
	// Step 4: Evaluate and display the security scan results
	if(status == 0) {
		printf("\n\nThe memory is safe.\n");
	}
	else {
		printf("\n\nVirus signature matched!\n");
		printf("The number of the signs: %d\n" , count);
	}
	
	return 0;
}

/**
 * @brief Scans the memory dump for the virus signature using a sliding window.
 * 
 * @param memoryDump Pointer to the main memory array (string)
 * @param virusSignature Pointer to the pattern being searched (string)
 * @param ptr Pointer to an integer tracking the number of matched characters/signs
 * @return int Status code (1 for match found, 0 for safe/no match)
 */
int detectVirus (char *memoryDump , char *virusSignature , int *ptr)
{
	int lenD;
	int lenS;
	int status;
	
	*ptr = 0; // Initialize the match counter
	
	lenD = strlen(memoryDump);
	lenS = strlen(virusSignature);
	
	// Sliding window loop: Slide the signature across the memory dump
	for (int i=0; i < lenD - lenS + 1; ++i) {
		
		// If the first character matches, start deep inspection
		if(*(memoryDump + i) == *virusSignature) {
			
			// Inner loop: Check the remaining characters of the signature
			for(int j=0; j < lenS; ++j) {
				if (*(memoryDump + i + j) == *(virusSignature + j)) {
					status = 0; // Partial/Full character match flag update
				}
			    ++(*ptr); // Increment the total matched character occurrences	
			}
		}
		else {
			status = 1; // No match at this window position
		}
	}
	
	return status;
}
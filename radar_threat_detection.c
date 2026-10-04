/**
 * @file radar_threat_detection.c
 * @brief Radar Stream Pattern Matching and Threat Detection
 * 
 * This program simulates a radar defense system that scans an incoming 
 * continuous data stream for specific hostile signatures. It utilizes a 
 * sliding window algorithm with standard string manipulation functions 
 * (strncpy, strcmp) to identify and locate threats.
 */

#include <stdio.h>
#include <string.h>

int main(void)
{
	char radarStream[100];
	char threatSignature[20];
	char window[20]; // Buffer for the sliding window
	int r_len;
	int t_len;
	int threat_number = 0;
	int check;
	
	// Step 1: Receive the radar data stream and the threat signature
	printf("Enter the radar stream: ");
	fgets(radarStream , sizeof(radarStream) , stdin);
	
	printf("\nEnter the threat signature: ");
	fgets(threatSignature , sizeof(threatSignature) , stdin);
	
	r_len = strlen(radarStream);
	t_len = strlen(threatSignature);
	
	// Step 2: Data Sanitization
	// Remove the trailing newline character '\n' captured by fgets
	radarStream[r_len - 1] = '\0';
	threatSignature[t_len - 1] = '\0';
	
	// Update lengths after removing the newline character
	r_len = r_len - 1;
	t_len = t_len - 1;
	
	// Step 3: Sliding Window Algorithm for Pattern Matching
	// Iterate through the radar stream until the remaining characters are fewer than the signature
	for(int i = 0; i <= r_len - t_len; ++i) {
		
		// Copy a chunk of the radar stream into the sliding window
		strncpy(window , radarStream + i , t_len);
		window[t_len] = '\0'; // Null-terminate the window buffer
		
		// Compare the current window with the target threat signature
		check = strcmp(window , threatSignature);
		
		// Step 4: Threat Logging and Alert System
		if(check == 0) {
			printf("\n\nWARNING! Threat has been detected.\n");
			// Print the exact index range where the threat was found
			printf("The location of the threat: index %d-%d" , i , (i + t_len - 1));
			++threat_number;
		}
	}
	
	// Step 5: Mission Debriefing
	printf("\n\nThe number of total threats: %d\n" , threat_number);
	
	return 0;
}
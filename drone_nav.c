/**
 * @file drone_nav.c
 * @brief UAV Navigation and Telemetry Simulation
 * 
 * This program simulates a basic Unmanned Aerial Vehicle (UAV) flight controller.
 * It features manual command-based navigation in an X-Y coordinate system, 
 * tracks real-time battery consumption, and executes an axis-by-axis 
 * Return-to-Home (RTH) protocol using Euclidean distance calculations.
 */

#include <stdio.h>
#include <math.h>

// Function prototypes
void move_drone(double *x_ptr , double *y_ptr , int *battery_ptr);
void return_to_home (double *x_ptr , double *y_ptr);
void total_distance(double *x_ptr , double *y_ptr);

int main(void)
{
	double x = 0.0;
	double y = 0.0;
	int battery = 100;
	
	// Pointers for memory-efficient state management (Pass-by-reference)
	double *x_ptr;
	double *y_ptr;
	int *battery_ptr;
	
	x_ptr = &x;
	y_ptr = &y;
	battery_ptr = &battery;

    // Phase 1: Manual flight mode via user commands
	move_drone(&x , &y , &battery);
	
	// Phase 2: Autonomous Return-to-Home (RTH) sequence
	return_to_home(&x , &y);
	
	// Phase 3: Display total mission distance
	total_distance(&x , &y);
	
	return 0;
}

/**
 * @brief Handles manual flight control and real-time battery telemetry.
 * 
 * Prompts the user for directional commands (W, A, S, D). Updates the drone's 
 * coordinates via pointers and decreases the battery level for each movement.
 * Prevents further movement if the battery is depleted.
 * 
 * @param x_ptr Pointer to the drone's X coordinate
 * @param y_ptr Pointer to the drone's Y coordinate
 * @param battery_ptr Pointer to the drone's battery level
 */
void move_drone(double *x_ptr , double *y_ptr , int *battery_ptr)
{
	char command;
	
	printf("'To increase x by 1: Press D.'\n'To decrease x by 1: Press A.'\n'To increase y by 1: Press W.'\n'To decrease y by 1: Press S.'\n'To close the program press 'Q'.\n\n");
	scanf(" %c" , &command);
	
	// Command loop: Continues until user quits or battery dies
	while (command != 'Q' && command != 'q') {
		
		if (command == 'D' || command == 'd') {
			printf("x will be increased by 1.\n\n");
			if (*battery_ptr == 0)
				printf("Mission failed: Out of battery!\n\n");
			else {
				*x_ptr = *x_ptr + 1;
				--*battery_ptr; 
			}
			scanf(" %c" , &command); 	
		}
		 
		else if (command == 'A' || command == 'a') {
			printf("x will be decreased by 1.\n\n");
			if (*battery_ptr == 0)
				printf("Mission failed: Out of battery!\n\n");
			else {
				*x_ptr = *x_ptr - 1;
				--*battery_ptr; 
			}
			scanf(" %c" , &command);	
		}
		
		else if (command == 'W' || command == 'w') {
			printf("y will be increased by 1.\n\n");
			if (*battery_ptr == 0)
				printf("Mission failed: Out of battery!\n\n");
			else {
				*y_ptr = *y_ptr + 1;
				--*battery_ptr; 
			}
			scanf(" %c" , &command);
		}
		
		else {
			printf("y will be decreased by 1.\n\n");
			if (*battery_ptr == 0)
				printf("Mission failed: Out of battery!\n\n");
			else {
				*y_ptr = *y_ptr - 1;
				--*battery_ptr; 
			}
			scanf(" %c" , &command);
		}
	}
}

/**
 * @brief Executes the Return-to-Home (RTH) protocol.
 * 
 * Autonomously navigates the drone back to the origin point (0,0).
 * It uses an axis-by-axis approach (X-axis first, then Y-axis).
 * Calculates and prints the remaining Euclidean distance after each step.
 * 
 * @param x_ptr Pointer to the drone's X coordinate
 * @param y_ptr Pointer to the drone's Y coordinate
 */
void return_to_home (double *x_ptr , double *y_ptr)
{
	int current_location_x;
	int current_location_y;
	double distance;
	
	// Sync local tracking variables with current drone state
	current_location_x = *x_ptr;
	current_location_y = *y_ptr;
	
	// RTH Navigation Loop: Continues if either axis is not at 0
	while (current_location_x != 0 || current_location_y != 0) {
	    
		// 1. Move towards 0 from a positive X position
		for (current_location_x = *x_ptr; current_location_x >= 0; --current_location_x) {
			*x_ptr = current_location_x;
			printf("\nCurrent location: (%d , %d)\n\n" , current_location_x , current_location_y);
			distance = sqrt(((*x_ptr)*(*x_ptr)) + ((*y_ptr)*(*y_ptr)));
			printf("The remain total distance is %.2f units.\n\n" , distance); 
		}
	    
		// 2. Move towards 0 from a negative X position
		for (current_location_x = *x_ptr; current_location_x <= 0 ; ++current_location_x) {
			*x_ptr = current_location_x;
			printf("Current location: (%d , %d)\n\n" , current_location_x , current_location_y);
			distance = sqrt(((*x_ptr)*(*x_ptr)) + ((*y_ptr)*(*y_ptr)));
			printf("The remain total distance is %.2f units.\n\n" , distance); 
		}
	    
		// 3. Move towards 0 from a positive Y position
		for (current_location_y = *y_ptr; current_location_y >= 0; --current_location_y) {
			*y_ptr = current_location_y;
			printf("\nCurrent location: (%d , %d)\n\n" , current_location_x , current_location_y);
			distance = sqrt(((*x_ptr)*(*x_ptr)) + ((*y_ptr)*(*y_ptr)));
			printf("The remain total distance is %.2f units.\n\n" , distance); 
		}
	    
		// 4. Move towards 0 from a negative Y position
		for (current_location_y = *y_ptr; current_location_y <= 0; ++current_location_y) {
			*y_ptr = current_location_y;
			printf("\nCurrent location: (%d , %d)\n\n" , current_location_x , current_location_y);
			distance = sqrt(((*x_ptr)*(*x_ptr)) + ((*y_ptr)*(*y_ptr)));
			printf("The remain total distance is %.2f units.\n\n" , distance); 
		}
		
		break;      
	}
	printf("The drone came back to its initial point.\n\n");
}

/**
 * @brief Calculates the total Euclidean distance required for the round trip.
 * 
 * Computes the direct linear distance from origin to the final point, 
 * and multiplies by 2 to represent a straight-line round trip.
 * 
 * @param x_ptr Pointer to the drone's final X coordinate
 * @param y_ptr Pointer to the drone's final Y coordinate
 */
void total_distance(double *x_ptr , double *y_ptr)
{
	double distance;
	
	distance = sqrt(((*x_ptr)*(*x_ptr)) + ((*y_ptr)*(*y_ptr)));
	distance = distance * 2;
	printf("The total distance is %.2f units.\n\n" , distance);
}
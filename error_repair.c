/**
 * @file error_repair.c
 * @brief Sensor Data Error Correction and Statistical Analysis
 * 
 * This program simulates a robot's sensor log system. It generates an array 
 * of sensor readings, injects simulated hardware faults (represented by -99), 
 * and then applies a data recovery algorithm to repair the corrupted logs.
 * Finally, it performs statistical analysis on the repaired data.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 90 // Constant for the log system, length of the array.

// Function prototypes:
void create_log(int log[] , int size);
int count_faults(const int log[] , int size);
void print_fault_indices(const int log[] , int size);
void repair_log(int log[] , int size);
float calculate_average(const int log[] , int size);
int count_large_changes(const int log[] , int size);

int main(void)
{
    int robot_log[SIZE];
    int faults_number;
    float the_average;
    int counts;
    
    // Initializes random seed based on current time
    srand(time(NULL));
    
    // 1. Generate the initial corrupted log
    create_log(robot_log , SIZE); 
    
    printf("Original log: ");
    for(int i = 0; i < SIZE; i++){
        printf("%d " , robot_log[i]); 
    }
        
    // 2. Analyze the log for faults before repair
    faults_number = count_faults(robot_log , SIZE);
    printf("\n\nNumber of Faults: %d" , faults_number);
    
    print_fault_indices(robot_log , SIZE);
    
    // 3. Repair the corrupted log
    repair_log(robot_log , SIZE); 
    
    printf("\n\nRepaired log: ");
    for(int j = 0; j < SIZE; j++) {
        printf("%d " , robot_log[j]);
    }
    
    // 4. Statistical data of repaired log
    the_average = calculate_average(robot_log , SIZE);
    printf("\n\nAverage: %.2lf" , the_average);
    
    counts = count_large_changes(robot_log , SIZE);
    printf("\nLarge changes: %d\n" , counts);
    
    return 0;
}

/**
 * @brief Fills the array with valid random readings and injects hardware faults.
 * @param log The sensor log array to be populated
 * @param size The size of the array
 */
void create_log(int log[] , int size)
{
    int position;
    
    // Fills entire array with valid random readings (20-200)
    for(int i = 0; i < size; ++i) { 
        log[i] = (rand() % 181) + 20;       
    }
    
    // Changes the values of exactly nine random elements to -99 (Error code)
    for(int j = 0; j < 9; j++) {
        position = rand() % size;
        log[position] = (-99);
    }
}

/**
 * @brief Scans the log to count the total number of sensor faults.
 * @param log The corrupted sensor log array (read-only)
 * @param size The size of the array
 * @return Total number of detected faults
 */
int count_faults(const int log[] , int size)
{
    int faults = 0;
    
    for (int i = 0; i < size; i++){
        if (log[i] == (-99)) {
            ++faults;
        }
    }
    return faults;
} 

/**
 * @brief Finds the elements that have a value of -99 and prints their indices.
 * @param log The corrupted sensor log array (read-only)
 * @param size The size of the array
 */
void print_fault_indices(const int log[] , int size)
{
    printf("\nFault indices: ");
    
    for (int i = 0; i < size; ++i) {
        if(log[i] == (-99)) {
            printf("%d " , i);
        }
    }
}

/**
 * @brief Repairs corrupted readings using adjacent valid data (Data Recovery).
 * @param log The sensor log array to be repaired
 * @param size The size of the array
 */
void repair_log(int log[] , int size)
{
    int j = 1;
    for(int i = 0; i < size; ++i) {  
        if(log[i] == (-99)) {
            // Edge case: If the first reading is faulty, find the next valid one (Forward propagation)
            if(i == 0) {
                while (j < size && log[j] == (-99)) {
                    ++j; 
                }
                log[i] = log[j];    
            }
            // Standard case: Replace with the previous valid reading (Backward propagation)
            else {
                log[i] = log[i-1];
            }
        }
    }
}

/**
 * @brief Calculates the floating-point average of the repaired log.
 * @param log The repaired sensor log array (read-only)
 * @param size The size of the array
 * @return The calculated average
 */
float calculate_average(const int log[] , int size)
{
    int sum = 0;
    float average;
    
    for (int i = 0; i < size; i++) {
        sum = sum + log[i];
    }
    
    // Use floating-point division with float casting to protect precision
    average = (float)sum / size;
    
    return average;
}

/**
 * @brief Counts occurrences of sudden spikes/drops between consecutive readings.
 * @param log The repaired sensor log array (read-only)
 * @param size The size of the array
 * @return Number of large changes (difference > 35)
 */
int count_large_changes(const int log[] , int size)
{
    int count = 0;
    
    // Iterates until size-1 to avoid out-of-bounds for log[i+1]
    for (int i = 0; i < size - 1; i++) {
        if (abs(log[i] - log[i+1]) > 35) {
            ++count; 
        }
    }
    return count;
}
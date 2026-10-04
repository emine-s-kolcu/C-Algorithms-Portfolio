/**
 * @file filter_peak.c
 * @brief Sensor Data Filtering and Anomaly (Peak) Detection Simulation
 * 
 * This program simulates a radar/sensor data stream, injects random anomalies,
 * applies a weighted moving average filter to smooth the data, and finally 
 * detects local maxima (peaks) that represent potential threats.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 50

// Structure to store the timestamp and severity of detected threats
struct Threat {
	int time_index;
	float intensity;
};

// Function prototypes
void createArray (float *ptr);
void theFilter (float *ptr);
int thePeak (float *ptr , struct Threat *t , int limit);

int main(void)
{
	float datas[SIZE];
	int threshold = 50; // Critical limit for threat detection
	int threat_num;
	
	struct Threat threat[10]; // Array to hold up to 10 detected threats
	
	srand(time(NULL));
	
	// Step 1: Generate simulated sensor data with random anomalies
	createArray(datas);
	
	// Step 2: Apply moving average filter to smooth the noise
	theFilter(datas);
	
	// Step 3: Detect local maxima (peaks) exceeding the threshold
	threat_num = thePeak(datas , threat , threshold);
	
	// Step 4: Display the results
	printf("Time indices of threats: ");
	for (int i=0; i<threat_num; ++i) {
		printf("%d " , threat[i].time_index);
	}
	
	printf("\n\n");
	
	printf("Intensities of threats: ");
	for(int i=0; i<threat_num; ++i) {
		printf("%.2f " , threat[i].intensity);
	}
	
	return 0;
}

/**
 * @brief Fills the array with baseline noise and injects random high values
 * @param ptr Pointer to the sensor data array
 */
void createArray (float *ptr) {
	int index;
	
	// Create baseline environmental noise (Values between 10 and 39)
	for (int i=0; i<SIZE; i++) {
		*(ptr+i) = (rand() % 30) + 10;
	}
	
	// Inject 10 random high-intensity anomalies (Values between 70 and 79)
	for(int j=0; j<10; j++) {
		index = rand() % SIZE;
		
		if (*(ptr + index) < 50) {
		    *(ptr + index) = (rand() % 10) + 70;
		}
	}
}

/**
 * @brief Applies a selective weighted moving average filter
 * @param ptr Pointer to the sensor data array
 * 
 * Smooths out spikes by averaging the current value with its neighbors.
 * Gives 50% weight to the current value, and 25% to adjacent values.
 */
void theFilter (float *ptr) {
	for (int i=0; i<SIZE; i++) {
		
		// Apply filter only to values exceeding the normal noise limit (50)
		if (*(ptr + i) > 50 && i != 0 && i != 49) {
			*(ptr + i) = (*(ptr + i - 1) + *(ptr + i)*2 + *(ptr + i + 1)) / 4;
		}
		// Edge case: First element
		else if (*(ptr + i) > 50 && i == 0) {
			*(ptr + i) = (*(ptr + i)*2 + *(ptr + i + 1)) / 3;
		}
		// Edge case: Last element
		else if (*(ptr + i) > 50 && i == 49) {
			*(ptr + i) = (*(ptr + i - 1) + *(ptr + i)*2) / 3;
		}
	}
}

/**
 * @brief Detects local maxima that exceed the defined threshold
 * @param ptr Pointer to the filtered data array
 * @param t Array of Threat structures to store detected peaks
 * @param limit The minimum intensity required to be classified as a threat
 * @return Total number of detected threats
 */
int thePeak (float *ptr , struct Threat *t , int limit) {
	int j = 0;
	
	for (int i=0; i<SIZE; i++) {
	    // Standard case: Current value is > limit AND > both neighbors
		if (*(ptr + i) > limit && i != 0 && i != SIZE - 1 && *(ptr + i - 1) < *(ptr + i) && *(ptr + i + 1) < *(ptr + i)) {
			(t + j)->time_index = i;
			(t + j)->intensity = *(ptr + i);
			++j;
		}
		// Edge case: Last element
		else if (i == SIZE - 1 && *(ptr + i) > limit && *(ptr + i - 1) < *(ptr + i)) {
			(t + j)->time_index = i;
			(t + j)->intensity = *(ptr + i);
			++j;
		}
		// Edge case: First element
		else if (i == 0 && *(ptr + i) > limit && *(ptr + i + 1) < *(ptr + i)) {
			(t + j)->time_index = i;
			(t + j)->intensity = *(ptr + i);
			++j;
		}
	}
	
	return j;
}
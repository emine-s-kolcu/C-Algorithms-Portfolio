###### \#C-Algorithms-Portfolio



###### \*A collection of C programs simulating defense and engineering algorithms.\*

###### 

###### 

###### These are terminal-based simulations focused on array manipulation, pointers (pass-by-reference), and basic algorithm design for data filtering and pattern matching. All core algorithms were originally implemented during my freshman year.

###### 

###### \## Projects Included

###### 

###### \### 1. UAV Navigation Simulation (`drone\_nav.c`)

###### A basic drone movement simulator on an X-Y grid. It tracks coordinates and battery life entirely via pointers, and includes a simple Return-to-Home (RTH) loop that calculates Euclidean distance back to the origin.

###### 

###### \### 2. Radar Threat Detection (`radar\_threat\_detection.c`)

###### A sliding window algorithm implementation. It scans a simulated radar data stream to find specific target signatures using standard C string functions (`strncpy`, `strcmp`).

###### 

###### \### 3. Sensor Data Error Repair (`error\_repair.c`)

###### Simulates a sensor log that occasionally receives faulty hardware data (represented by -99). The code finds these errors and repairs them by replacing them with the nearest valid data point, followed by basic statistical analysis.

###### 

###### \### 4. Memory Virus Scanner (`virus\_scan.c`)

###### A pattern-matching script. It slides a target signature across a simulated memory dump string to detect matches and count how many times the specific pattern appears.

###### 

###### \### 5. Sensor Peak Detection (`filter\_peak.c`)

###### Generates an array of sensor noise, applies a basic moving average filter to smooth the data, and then iterates through the array to detect local maxima (peaks) representing anomalies.

###### 

###### \---

###### \*Developed by an Electrical and Electronics Engineering student at Hacettepe University.\*


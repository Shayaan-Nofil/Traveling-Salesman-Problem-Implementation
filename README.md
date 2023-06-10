# Traveling-Salesman-Problem-Implementation
The problem statement:

Suppose you are designing a delivery robot that must visit a number of locations in a warehouse. The robot
starts at a designated "home" location and must visit every other location exactly once before returning to the
home location. Additionally, the robot has a limited battery life and must return home before its battery runs
out.
More formally, you are given an undirected graph G = (V, E) representing the warehouse layout, where each
vertex v ∈ V represents a location and each edge (u, v) ∈ E represents a direct path between locations u and v
that the robot can traverse. The home location is a designated vertex h ∈ V, and each vertex v ∈ V (other than
h) has a delivery time t(v) representing the amount of time it takes the robot to deliver a package at location v.
Your goal is to find a Hamiltonian circuit in G that starts and ends at h and visits every other vertex exactly
once, subject to the constraint that the total time taken by the robot (including delivery times and travel times)
does not exceed a given time limit T.
Design an algorithm to solve this problem. If a feasible Hamiltonian circuit exists, your algorithm should output
the sequence of vertices visited in the circuit. If no feasible circuit exists, your algorithm should output "NO
FEASIBLE CIRCUIT".
You may assume that the input graph is connected, and that the battery life of the robot is sufficient to travel
between any two locations in the warehouse.
 Write the program in C++ and name the source code file as hcp.cpp.

 In your project report, write your algorithm (in pseudocode form) and perform the asymptotic time-
complexity analysis. Your solution should list all steps in the form of primitive operations, i.e., without the

use of any built-in function call.
Note: You have been given several text files, each containing different test cases. Your task is to develop a code
that can process the test cases in each file. Here is a possible approach you can take:
1. Define a function that can handle a single test case. This function may need to read data from the text
file, perform calculations or operations, and generate an output, depending on the specific task.
2. Write a loop that can iterate over each text file in the directory. For each file, use the open() function to
read its contents and separate the test cases based on a delimiter, such as a blank line.
3. For each test case in the file, call the processing function you defined in step 1 to generate an output.
4. You may choose to display the output on the screen or write it to a file.
----------------------------------------------------------------------------------------------------------------------

The solution makes use of the brute force algorithm for solving TSP. Included with the .cpp files are 4 test cases which can
be run to check the output of the program. The solution is developed in a windows enviroment, using visual studio 2022.

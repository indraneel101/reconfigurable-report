Simulated Annealing Algorithm Implementation  

In this project, I have implemented the Simulated Annealing Algorithm in C++ and MATLAB. The practical implementation in the algorithm is based on VLSI Design Automation to have an efficient way of placing the cells in the correct manner rather than prefering random placement.

The algorithm is developed in C++. We use a linked list data structure to store the data nd than output of the algorithm in C++ is a text file. The text file is fed to MATLAB, thorugh which we get graphical details and analysis.

The algorithm goes like this: 

Assumptions:
Maintain aspect ratio (Height/Width)=1
Placement is a NP complete problem.

Steps of the algorithm:

1) Read. Net file input from the user.
2) Create Linkekd List data structure of Netlist and Cell list.
3) Calculate no. of rows and cells required per row such that the aspect ratio is close to 1.
4) Find the initial wirelength.
5) Calculate the initial tempreature
6) Check the equilibrium condition   (Check the no. of swaps to the iteration count)
7) If this count is less, swap the location of two random variables.
8) If the count is high, stay with the initial placement.
9) Get the output as a text file
10) Feed the text file to MATLAB.
11) Get the graphical analysis.

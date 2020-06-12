Problem

This program  is capable of solving static puzzles representing rectangular maps in which the only permissible movements are horizontal and vertical displacements. 
Each cell in these maps has an indicator of its value when entering that cell. Possible values ​​are negative, null or positive.


Restrictions

In addition to the map there is an agent placed in one of the cells of the map and that agent has a given initial energy value. 
It is intended that the agent walks along the map with the aim of increasing his energy, if possible. 
Different restrictions may be allowed for the paths taken by the agent:

1. The path produced has exactly k steps, neither less nor more
2. The agent cannot go on if his energy ever stops being positive
3. The path traveled cannot use any cell more than once, including the starting cell. 


Objectives

In addition to the above restrictions, the agent may have one of two objectives to be achieved at the end of the path: 
1) to reach or exceed a specific energy value
2) achieve the greatest possible energy for the map on which it is placed


Input format

The .maps extension file can contain one or more maps to be resolved. 
Each map is defined as follows: 
- the first line contains 
-- information about the dimensions of the map (rows and columns)
-- what is the objective (a positive integer for the minimum energy to reach - objective 1 -, or -2 for the maximum possible energy - objective 2)
-- the coordinates of the agent's starting position; the number of steps, k, of the route; and what is the agent initial energy 

- in the following lines, the composition of the map is identified, in which each line of the ﬁ le represents, through whole numbers, the costs or rewards in each cell of that line.


Output format

The result of executing the aMazeMe program is to present the steps that constitute the path produced or the indication that the problem does not admit a solution.
For any problem, the first line of the solution should always repeat the first line of the problem, as shown in the input file, to which an integer is added. 
This eighth integer must indicate the final energy, for problems that have a solution, or -1, indicating that the problem has no solution. 
If the eighth integer is positive, the following lines must contain the solution to the problem. In other words, there must be k lines of three integers each: coordinates of the position to be advanced and the value of that position. 
For example, if the initial coordinates are l = 3 and c = 7, the first line indicating the first step of the path may be one of the following possibilities: 3 8 k_1; 36 k_2; 27 k_3; or 17 k_4. The k_i values ​​will identify the penalty or premium received at the indicated position. If the eighth integer is -1, only that first line is the appropriate answer to the problem in question.
The complete solution for a given map could be, for example:

10 8 -2 1 1 5 100 128 
1 2 -1 
1 3 -1 
1 4 27 
1 5 -1 
1 6 4

If the .maps extension file has more than one problem, the output file will contain a solution for each of the indicated problems and in the same order as they appear in the input file.


How to execute the program

The aMazeMe program should be invoked on the command line as follows: ./amazeme <name>.maps
where <name> is a variable identifying the file containing the map(s) to be solved. They can be found in the maps folder.

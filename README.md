Ruchit Patel

---------------------
DESCRIPTION

- In this lab, three sorting algorithms are implemented: Bubble sort, Shell sort, and Quick sort.
- Bubble sort and Shell sort directly work on an array. 
- Quick sort is implemented using two abstract data types: a stack and a queue.
- Arguments:    -a (run all three sorting algorithms),
                -b (run bubble sort), 
		-s (run shell sort), 
		-q (run quick sort using a stack), 
		-Q (run quick sort using a queue), 
		-r (sets the random seed), 
		-n (sets the array size), 
		-p (prints out n elements of an array).

---------------------
FILES

1. bubble.h
- This is a header file that declares the bubble sort method.

2. bubble.c 
- This source file implements the bubble sort method.

3. gaps.h
- This header file defines the gap array to be used by the shell sort method.

4. shell.h 
- This is a header file that declares the shell sort method.

5. shell.c
- This source file implements the shell sort method.

6. quick.h 
- This is a header file that declares the quick sort method.

7. quick.c 
-This source file implements the quick sort method (both with stack and queue).

8. stack.h 
- This header file declares the queue abstract data structure and the methods to manipulate it.

9. stack.c
-  This source file implements the methods declared in stack.h to work with a stack (used by quick sort).

10. queue.h 
- This header file declares the queue abstract data structure and the methods associated with it.

11. quick.c 
- This source file implements the methods declared in queue.h to work with a queue(used by quick sort).

12. sorting.c 
- This source file contains the main method and calls the other sorting method implemented in the source files mentioned above. 

13. sorting.h
- This file contains extern variables and function to keep track of compares and moves throughout different algrorithms.

14. set.c
- This file contains implementation of set ADT which is used as a bitmask for arguments.

15. set.h
- This header file is an interface for the set ADT as described above.

16. DESIGN.pdf 

- This PDF explains the design for this lab. It includes a brief description of the lab and pseudocode alongwith implementation description. It also contains the answers to pre-lab questions.

17. WRITEUP.pdf

- This file contains the analysis of the sorting algorithms and examines time complexities output vs input graphs, sizes of stacks and queues, etc.

18. Makefile

- This is a Makefile that can be used with the make utility to build the executable.


---------------------
INSTRUCTIONS

Manually:
1. Keep all the source and header files in the same directory and compile the source files using clang compiler in Ubuntu 20.04.

2. The documented compilation command is as follows: clang -Wall -Wextra -Wpedantic -Wshadow -o sorting *.c 

3. Finally, execute ./sorting -[arguments] in a terminal. 

4. The program would run as described in the description based on the arguments. 


With make:
1. Keep the Makefile in the same directory as all other files mentioned above.

2. Execute “make” or “make all” in terminal in order to produce the sorting executable. 

3. Finally, execute ./sorting -[arguments] in a terminal. 

4. The program would run as described in the description based on the arguments. 

5. In order to scan-build the source file, run “make scan-build” in the terminal.

6. In order to clean up (remove object and executable files), run “make clean” in the terminal.

This is a part of a lab designed by Prof. Darrell Long

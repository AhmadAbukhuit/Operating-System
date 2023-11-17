# Multi-Threads

I implemented a multi-threaded program (using C++) on Linux that will perform several arithmetic operations in parallel. 

The program will have 4 different types of worker threads: multipliers, dividers, adders, and subtractors. Each of the worker threads perform the arithmetic operation indicated by its name. The program will receive an initial value (initVal) through command line. Then, the input file will list the number of workers of each type, and the amount they will do in their operation.

Multiplier and Divider threads can start in parallel, but they must finish before allowing any Adder or Subtractor thread to start. After all Multipliers and Dividing threads are done, the Adders and Subtractors threads can start working in parallel. The main thread waits until all threads are done.

My program will also receive another value through command line, which is a threshold, I will use in the threads’ execution. The program have three global shared variables to report the statistics:
  1. aboveThreshold: Number of times a thread caused the accumulated value to be above threshold
  2. equalThreshold: Number of times a thread caused the accumulated value to be equals threshold
  3. belowThreshold: Number of times a thread caused the accumulated value to be below threshold

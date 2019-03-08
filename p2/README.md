# CSC262 memfit

Memory Allocation Assignment (Due Friday, 8 March 2019)

## Build and run
Download file, cd to memfit/, run main.c in CLION.

## Give me an input file that you have used.
```
pool random 1000
alloc A 200
alloc B 300
alloc C 100
free B
alloc D 150
alloc E 100
alloc F 200
free D
alloc G 100
alloc H 100
free C
```
We tested it line by line, you can do the same thing to verify these algorithms:)

## Other

The input file contains a sequence of lines with one of three commands on them:

-	``pool ALGORITHM SIZE``
-	``alloc NAME SIZE``
-	``free NAME``

``ALGORITHM`` is one of "first", "best", "worst", "next" or "random".

-----------------------------------------------------------------------------------

## Rubric

### README (20 points):

-	Tell me how to build and run your program.
-	Give me an input file that you have used.

### Functionality (80 points):

-	(10) Program can read from an arbitrary file and run commands in order.
    -	You may choose to start with hard-coding these method calls.
-	(20) Program supports first, best, and worst fits.
    - Start with first-fit.
    - Sorting may be hard to get going, depending on your experience with it.
- (10) Program supports “free” by name. Compact free space!
    -	Can do nothing at first.
    - Has nice error if you free a silly name?
-	(10) Program supports random fits.
    - Not much different than first-fit if you know how to shuffle.
- (10) Program supports next fits.
    - How do you keep track of the last block handed out?
-	(10) Program outputs a list of used and free sections in offset order.
-	(5) Program outputs the percentage of used, free memory after executing a file.
-	(5) Program outputs the number of failed allocations after executing a file.

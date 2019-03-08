# CSC262 memfit

Memory Allocation Assignment (Due Friday, 8 March 2019)

## Build and run
1. Change commands in input.txt
2. Choose one of these algorithms (Case sensitive):
    - random
    - best
    - worst
    - first
    - next
3. Run main.c
### Program structure
1. All algorithms are written in fits.c
2. Algorithm selections are stored and parsed in simulation_start() and simlation_alloc() in simulation.c.
3. To free a block: everytime we free a block, the program will merge it with its adjacent blocks (written in simulation.c, at the bottom).
4. Free_list is always sorted by offset using list_sort_by_offset() written in block.c.
5. Memory report is written in main.c, the section after parsing the input file.
6. Failed_allocation_number is stored in sim and is updated everytime an algorithm fails to allocate a block with required size.


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
We tested it line by line, you can do the same thing to verify our algorithms:)

## Other

The input file contains a sequence of lines with one of three commands on them:

-	``pool ALGORITHM SIZE``
-	``alloc NAME SIZE``
-	``free NAME``

``ALGORITHM`` is one of "first", "best", "worst", "next" or "random".

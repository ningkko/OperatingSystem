Feb26 - OS Note


### Space & Memory - arbitrary size
1. Segmentation
- Process level
- ~= block allocation
 * Offset
 * Size
- The more flexible the structure, the more cost to organize

2. Paging - Fixed size
- OS level
- page id + fixed size


### Time & Scheduling

1. Oracle scheduling
- imagining that we know how long a process is going to take
- Algos
 * Short job first
 * First come first served
 * Longest job first 
- Time slice
 * fixed size
- Algos
 * simple- Round Robin
 * fair and less latency
 * multilayer -  MLFQ
 * Probability - Lottery


#### Thread.sleep(100)
- The name is really just more a suggestion because time slices are fix-sized. 
- For people really care about timing, use while loop instead.


### Data Structure
1. Stack - LIFO
	- Just a pointer in C, pointing to the first cell. 
	- In Java, have to define something that comes after the first cell.
2. Queue - FIFO
 	- Scheduling, concurrency
3. Pool
 	- Alloc & free
	- OS has fixed size resources
4. Tree
	- Binary Trees
		* Not useful due to large depth
	- Recursive structure are usually called trees ignoring the balancing and node thing…



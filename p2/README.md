# CSC262 memfit

Memory Allocation Assignment (Due Friday, 8 March 2019)

## Example Input File:

```
pool first 1000
alloc A 200
alloc B 300
alloc C 100
free B
```

The input file contains a sequence of lines with one of three commands on them:

-	``pool ALGORITHM SIZE``
-	``alloc NAME SIZE``
-	``free NAME``

``ALGORITHM`` is one of "first", "best", "worst", "next" or "random".

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

### Extra Credit Opportunities:

- Do (some of) it again, but in plain C.
- Unit tests for tricky algorithms, like compactFreeSpace.
- Try outputting HTML tables or SVG for automatically generating snazzy diagrams.
- Generate input files automatically.
- Figure out how to make Best or Worst fit use a heap.
- Figure out how to measure fragmentation. Is there a single number you could use to represent how fragmented your simulator is?

## Architecture Hints (Java)

```java
// I’d want a simulation class to do most of the work.
class Simulation {
  String algorithm;
  List<Block> free_list;
  List<Block> used_list;
   
  // Strongly recommend you start with printing out the pieces.
  void print();
  Block alloc(String name, int size) { /* #4,#5,#6 on worksheet */ }
  private Block alloc_first(String name, int size);
  …
  void free(String name);
  private void splitBlock(Block b, String newName, int size) { /* #1 on worksheet */ }
  private void compactFreeList() { /* #3 on worksheet */ }
  public static void main(String[] args) { /* #9 on worksheet (modified) */ }
}

// I’d want a block class with at least these fields and methods.
class Block {
  String name;
  int offset;
  int size;
  public String toString(); // highly recommended
  public boolean is_adjacent(Block other) { /* #2 on worksheet*/  }
}

// Sort-by in Java: (needs a class)
class ByOffset implements Comparator<Block> {
  @Override int compare(Block lhs, Block rhs) {
    return Integer.compare(lhs.offset, rhs.offset);
  }
}

static void exampleSort(List<Block> blocks) {
    Collections.sort(blocks, new ByOffset());
}

```

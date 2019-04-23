## SO far...
1. Scheduling -> Processes
2. Threading -> Within process scheduling
3. Memory -> malloc/new
	- Have fixed size pool
		1. First Fit
		2. Worst Fit
		3. Best Fit
4. FileSystems -> open/read/write
	- Difference with a system?
		- Disk
		- more permanent 
		- open("file.txt", "w") Don't know how big the file is going to be until finish reading it

## What/Why Bitmap, inode, data
- bitmap
	1. An idea way of page structure
		- PageAllocationIdea{
			- boolean used[1024];
			- byte pages [4096][1024]; 
		- }
	2. Another way
		- Class Page{
			- boolean used;
			- bytes[] data;
		- } 
	- 1 Keeps the memory of the boolean elsewhere, so things are at wheretehy are expected to be in the page table
	- 1 Should be faster when looking for missing pages
	- Useful for keeping track of resources
	- Keep different data seperately
- inode
	tells what's ina file
	- Inode{
		- file.size
		- owner permission
		- times(modify, create, access)
		- link-count
		- blocks(#)
		- disk_blocks[16] // Optimized for small files
		- indirect_block
	}

## Defragmentation
- the process of locating the noncontiguous fragments of data into which a computer file may be divided as it is stored on a hard disk, and rearranging the fragments and restoring them into fewer fragments or into the whole file.
- Potentially makes Windows even slower

## FAT: [file-allocation-table](https://www.techopedia.com/definition/1369/file-allocation-table-fat)
- Linked list
- for hard drives that originally used 12 or 16 bits for each cluster entry into the file allocation table

## Superblock: Read more about [blocks](https://www.slashroot.in/understanding-file-system-superblock-linux)
- a unique data structure in a filesystem (though multiple copies exist to guard against corruption). 
- holds metadata about the filesystem, like which inode is the top-level directory and the type of filesystem used.


## FFS: Fast File System
- The Unix file system (UFS; also called the Berkeley Fast File System, the BSD Fast File System or FFS) is a file system supported by many Unix and Unix-like operating systems.

## sectors (512)
- The minimum storage unit of a hard drive.
- A subdivision of a track on a magnetic disk or optical disc. 
- Each sector stores a fixed amount of user-accessible data, traditionally 512 bytes for hard disk drives (HDDs) and 2048 bytes for CD-ROMs and DVD-ROMs.
- The smallest smount of memory that can be read from a RAM -> a word

## [Ext2](https://en.wikipedia.org/wiki/Ext2)
- Nowadays Ext4
- was the default filesystem in several Linux distributions, including Debian and Red Hat Linux, until supplanted more recently by ext3, which is almost completely compatible with ext2 and is a journaling file system.
- File allocation‎: ‎bitmap (free space), table ...
- Directory contents‎: ‎Table ...

## B-tree
- Nowadays most filesystems are written in Btree
- [Why Btree for filesystems?](https://stackoverflow.com/questions/32512700/why-b-tree-for-file-systems)
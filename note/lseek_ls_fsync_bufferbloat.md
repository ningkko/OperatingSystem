## strace
- System call
- strace cat foo.txt
- Coverity "static analysis tool" uses strace to find all relebant source files

## lseek
- Commands:
	1. Current place in the file: p = lseek(file, 0, SEEK_CUR)
	2. Go to the beginning of the file: lseek(file, 0, SEEK_SET)
	3. Skip 1000 bytes: lseek(file, 1000, SEEK_CUR)
	4. Go to the end of the file: lseek(file, 0, SEEK_END)
- To find out how big the file is: 4, 1, 2

## ls
- stat() 
	- Function: Display file (default) or filesystem status
    - Syntax: stat [-FLnq] [-f format|-l|-r|-s|-x] [-t timefmt] [file ...]
	- Example: stat -F /tmp/foo
- There should not be more than 4000 files in the directory
- Noatime 
	- Noatime will tell the filesystem not to record the last accessed date of the file.
	- Command
		- mount -o remount /
		- #check
		- cat /proc/mounts | grep noatime

## fork/dup - ref.count
- Open file table
	0. stdin
	1. stdout
	2. stderr
	3. Your file (hello.java)
- If we want to print the error to output.txt:
	- java Hello.java 2>&1 > output.txt
	- 2>&1: stderr & stdout. Without this only actual result will be written to output.txt
- When fork(), the table got duplicated.
- Whenever fork() makes a new child, the file descriptors are not retained at all - they are changed. Although the file will be a duplicate, it will have a different file descriptor.
- [file descriptor](https://pubweb.eng.utah.edu/~cs4400/file-descriptor.pdf)

## BufferedReader
- .read(1024) // a buffer
- while (true) 
	- { int n = getc(); // getc() -> system call
	- if (n == EOF) {break;}
	- do ((char) n)
- }

## Struct of a file
- struct FILE {
	- int fd;
	- int position;
	- Queue buffer;
- }

## fsync() sync() and fflush()
- fsync()
	- synchronize changes to a file
	- int fsync(int fd); // synchronize a file's in-core state with storage device
	- requests that all data for the open file descriptor named by fildes is to be transferred to the storage device associated with the file described by fildes. T
	- does not return until the system has completed that action or until an error is detected.
	- fail if:
		- [EBADF] The fildes argument is not a valid descriptor.
		- [EINTR] The fsync() function was interrupted by a signal.
		- [EINVAL] The fildes argument does not refer to a file on which this operation is possible.
		- [EIO] An I/O error occurred while reading from or writing to the file system.

- sync() 
    - sync() will commit all modified files to disk.
    - Old gameboys or nitendo machines uses DRAM and have to sync() to prevent data missing


- fflush()
	- int fflush(FILE *stream); // flush a stream, FILE* type
	- fflush() works on FILE*, it just flushes the internal buffers in the FILE* of your application out to the OS.
	- fsync works on a lower level, it tells the OS to flush its buffers to the physical media.
	- OSs heavily cache data you write to a file. If the OS enforced every write to hit the drive, things would be very slow. fsync (among other things) allows you to control when the data should hit the drive.
	- Furthermore, fsync/commit works on a file descriptor. It has no knowledge of a FILE* and can't flush its buffers. FILE* lives in your application, file descriptors live in the OS kernel, typically.


## bufferbloat
- the undesirable latency comes from a router or other network equipment buffering too much data.
- a huge drag on Internet performance created

## inode
- describes a file-system object such as a file or a directory.
- stores the attributes and disk block location(s) of the object's data

## ln-s
- "symbolic"
	- link latest java to old jdks
- "soft"

## ACLs
- Access Control Lists
- structure:
	 - usr(owner)
	 - group(owner and the group)
	 - other

## mkfs
- In unix, every file system is a file.

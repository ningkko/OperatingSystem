## Processes and UNIX

### Abstraction ::= Hiding details

### Process 
an abstraction because it hides things from the OS

Process is like a box inside which there are threads. Some programs like Python has secret threads that the OS does not know about.
Usually a program uses only one process unless (in Java) Runtime.exec("ls -l") which makes a bash call. Or in Python, System(" ").

### How exec() works?
The program fork() the code,data,stack,...heap first and overwrite it and the call exec().\
Note: fork() is an abstraction becauase it hides a lot of work which tells addresses of things etc. This is also why it's quicker to copy and overwrite than to just create a new one).

### Time Slice
- before iOS4, only 1 app can be open at one time.

### Alternative model: Cooperative Multitasking
- Run process in a for loop
- Only in trusted system which all codes can be trusted because it never stops until someone calls sleep()

Modern OS systems:
- Unix Style: Vending machines, ATMs, TV, iOS...
- Realtime OS: Respond as fast as possible. E.g. car brains,robots, spaceship, personal medical care device...

### Latency
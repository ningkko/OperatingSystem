Ch. 7: Ideal Scheduling
Ideal = You know how long jobs will take.
- FIFO/FCFS – First in First Out / First Come First Serve 
- SJF – Shortest Job First 
- STCF/PSJF – Shortest Time to Completion First / Pre-emtive SJF 
- RR – Round Robin

Ch. 8: Real-World Scheduling 
MLFQ: Multi-Level Feedback Queue 
- Is the MLFQ Online Machine Learning? 
- What data structure might it be made of? 
- Why only finite priorities?


To handle **interruptions**, usually write inside assembly
-> _**Interrupt Register**_ \
E.g. When divided by 0, computer overheats\
Only one interrupt register , if while ealing with one error, another one comes -> crash\
So usually an interrupt register will disable interrupt while dealing with some error\
&nbsp;&nbsp;  Every delta t Timer interrupt:\
&nbsp;&nbsp;&nbsp;&nbsp;  disable interrupt()\
&nbsp;&nbsp;&nbsp;&nbsp;  kernel thinks about scheduling\
&nbsp;&nbsp;&nbsp;&nbsp;  enableInterrupt()

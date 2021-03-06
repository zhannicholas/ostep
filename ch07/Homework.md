# Scheduling: Introduction

## Homework (Simulation) 
This program, scheduler.py, allows you to see how different schedulers perform under scheduling metrics such as response time, 
turnaround time, and total wait time. See the README for details. 

## Questions 
1. Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers.
   
   |      | response time | turnaround time |
   |------|---------------|-----------------|
   | SJF  | 0, 200, 400   | 200, 400, 600   | 
   | FIFO | 0, 200, 400   | 200, 400, 600   |
   
2. Now do the same but with jobs of different lengths: 100, 200, and 300.
   
   |      | response time | turnaround time |
   |------|---------------|-----------------|
   | SJF  | 0, 100, 300   | 100, 300, 600   |
   | FIFO | 0, 100, 300   | 100, 300, 600   |
   
3. Now do the same, but also with the RR scheduler and a time-slice of 1.
   
   lengths: 100, 200, 300
   
   |      | response time | turnaround time |
   |------|---------------|-----------------|
   |  RR  |     0, 1, 2   |  298, 499, 600  |
   
4. For what types of workloads does SJF deliver the same turnaround times as FIFO? 

   任务的执行时长非递减有序。
   
5. For what types of workloads and quantum lengths does SJF deliver the same response times as RR? 
   
   每个任务的时长相同，并且时间片的长度恰好是任务的时长。
   
6. What happens to response time with SJF as job lengths increase? Can you use the simulator to demonstrate the trend? 
   
   响应时间会变长。
   
7. What happens to response time with RR as quantum lengths increase? Can you write an equation that gives the worst-case response time, given N jobs?

   响应时间会变长。
   response_time_of_nth_job = (n - 1) * quantum

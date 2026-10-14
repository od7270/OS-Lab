/*
 * Ex. No. 9 – SCHEDULING ALGORITHMS: FCFS, SJF
 * Q1. Write a program to implement the FCFS scheduling algorithm
 *
 * ---- Background from the manual ----
 *
 * ## 1. FCFS scheduling algorithm
 *
 * Given n processes with their burst times, find the average waiting time and average
 * turnaround time using FCFS scheduling. First in, first out (FIFO), also called first
 * come, first served (FCFS), is the simplest scheduling algorithm. It queues processes in
 * the order they arrive in the ready queue. The process that arrives first runs first, and
 * the next process starts only after the previous one has finished. Assume the arrival
 * time of every process is 0.
 *
 * - Turnaround time = Completion time − Arrival time
 * - Waiting time (W.T.) = Turnaround time − Burst time
 *
 * Algorithm:
 *
 * 1. Input the processes along with their burst times (bt).
 * 2. Find the waiting time (wt) for all processes.
 * 3. The first process does not wait, so wt[0] = 0.
 * 4. For every other process i: wt[i] = bt[i-1] + wt[i-1].
 * 5. Turnaround time = waiting_time + burst_time for every process.
 * 6. Average waiting time = total_waiting_time / no_of_processes.
 * 7. Average turnaround time = total_turn_around_time / no_of_processes.
 *
 * Input: process numbers and their burst times
 * Output: burst time, waiting time and turnaround time for each process, plus the average
 * waiting time and average turnaround time
 *
 * Source: OS_Lab_Manual.md, line 751
 */

#include <stdio.h>

int main()
{
    int n,i,bt[20],wt[20],tat[20];
    float total_wt=0,total_tat=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);
    printf("Enter burst time of each process:\n");
    for(i=0;i<n;i++)
    {
        printf("P%d: ",i+1);
        scanf("%d",&bt[i]);
    }

    wt[0]=0;                        /* first process does not wait */
    for(i=1;i<n;i++)
        wt[i]=bt[i-1]+wt[i-1];
    for(i=0;i<n;i++)
    {
        tat[i]=wt[i]+bt[i];
        total_wt+=wt[i];
        total_tat+=tat[i];
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i=0;i<n;i++)
        printf("P%d\t%d\t\t%d\t\t%d\n",i+1,bt[i],wt[i],tat[i]);
    printf("\nAverage waiting time = %.2f\n",total_wt/n);
    printf("Average turnaround time = %.2f\n",total_tat/n);
    return 0;
}

/*
 * Output:
 * Enter number of processes: 3
 * Enter burst time of each process:
 * P1: 24
 * P2: 3
 * P3: 3
 *
 * Process Burst Time      Waiting Time    Turnaround Time
 * P1      24              0               24
 * P2      3               24              27
 * P3      3               27              30
 *
 * Average waiting time = 17.00
 * Average turnaround time = 27.00
 */

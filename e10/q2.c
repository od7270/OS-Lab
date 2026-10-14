/*
 * Ex. No. 10 – SCHEDULING ALGORITHMS: Priority and Round Robin
 * Q2. Write a program to implement the Round Robin scheduling algorithm
 *
 * ---- Background from the manual ----
 *
 * ## 2. Round Robin
 *
 * Aim: To simulate the round-robin CPU scheduling algorithm.
 *
 * Description: The aim is to calculate the average waiting time. There is a time slice,
 * and each process runs for at most one time slice at a time. If it doesn't finish, it
 * goes back to waiting. First check whether the remaining burst time is less than the time
 * slice. If it is, the process finishes and its waiting time is set from the total time
 * elapsed. If it isn't, subtract the time slice from the remaining burst time, advance the
 * elapsed time by the time slice, and continue the loop until all processes complete.
 *
 * Algorithm:
 *
 * 1. Start the process.
 * 2. Accept the number of processes in the ready queue and the time quantum (time slice).
 * 3. For each process in the ready queue, assign a process ID and accept its CPU burst
 * time.
 * 4. Calculate the number of time slices for each process: no. of time slices for
 * process(n) = burst time of process(n) / time slice.
 * 5. If the burst time is less than the time slice, the number of time slices = 1.
 * 6. Treat the ready queue as a circular queue and calculate:
 * - a) Waiting time of process(n) = waiting time of process(n−1) + burst time of
 * process(n−1) + time between process(n−1) and process(n) getting the CPU
 * - b) Turnaround time of process(n) = waiting time of process(n) + burst time of
 * process(n) + time between process(n) getting the CPU
 * 7. Calculate:
 * - c) Average waiting time = total waiting time / number of processes
 * - d) Average turnaround time = total turnaround time / number of processes
 * 8. Stop the process.
 *
 * Source: OS_Lab_Manual.md, line 840
 */

#include <stdio.h>

int main()
{
    int n,i,tq,time=0,done,bt[20],rem[20],wt[20],tat[20];
    float total_wt=0,total_tat=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);
    printf("Enter burst time of each process:\n");
    for(i=0;i<n;i++)
    {
        printf("P%d: ",i+1);
        scanf("%d",&bt[i]);
        rem[i]=bt[i];
    }
    printf("Enter time quantum: ");
    scanf("%d",&tq);

    /* walk the ready queue as a circular queue until every process finishes */
    do
    {
        done=1;
        for(i=0;i<n;i++)
        {
            if(rem[i]==0)
                continue;
            done=0;
            if(rem[i]>tq)
            {
                time+=tq;
                rem[i]-=tq;
            }
            else
            {
                time+=rem[i];
                rem[i]=0;
                tat[i]=time;            /* completion time (arrival time 0) */
                wt[i]=tat[i]-bt[i];
            }
        }
    } while(!done);

    for(i=0;i<n;i++)
    {
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
 * Enter time quantum: 4
 *
 * Process Burst Time      Waiting Time    Turnaround Time
 * P1      24              6               30
 * P2      3               4               7
 * P3      3               7               10
 *
 * Average waiting time = 5.67
 * Average turnaround time = 15.67
 *
 * Gantt chart: | P1 0-4 | P2 4-7 | P3 7-10 | P1 10-30 |
 */

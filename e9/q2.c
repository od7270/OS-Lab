/*
 * Ex. No. 9 – SCHEDULING ALGORITHMS: FCFS, SJF
 * Q2. Write a program to implement the SJF scheduling algorithm
 *
 * ---- Background from the manual ----
 *
 * ## 2. Shortest Job First (SJF), non-preemptive
 *
 * Description: To find the average waiting time in SJF, sort the processes by burst time
 * in ascending order. The waiting time of each process is the sum of the burst times of
 * all processes before it.
 *
 * Algorithm:
 *
 * 1. Start the process.
 * 2. Accept the number of processes in the ready queue.
 * 3. For each process in the ready queue, assign a process ID and accept its CPU burst
 * time.
 * 4. Order the ready queue by shortest burst time, sorting from lowest to highest.
 * 5. Set the waiting time of the first process to 0 and its turnaround time to its burst
 * time.
 * 6. Sort the process names by their burst time.
 * 7. For each process in the ready queue, calculate:
 * - a) Waiting time(n) = waiting time(n−1) + burst time(n−1)
 * - b) Turnaround time(n) = waiting time(n) + burst time(n)
 * 8. Calculate:
 * - c) Average waiting time = total waiting time / number of processes
 * - d) Average turnaround time = total turnaround time / number of processes
 * 9. Stop the process.
 *
 * Source: OS_Lab_Manual.md, line 778
 */

#include <stdio.h>

int main()
{
    int n,i,j,temp,p[20],bt[20],wt[20],tat[20];
    float total_wt=0,total_tat=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);
    printf("Enter burst time of each process:\n");
    for(i=0;i<n;i++)
    {
        printf("P%d: ",i+1);
        scanf("%d",&bt[i]);
        p[i]=i+1;
    }

    /* sort by burst time, shortest first (process ids move with them) */
    for(i=0;i<n-1;i++)
        for(j=0;j<n-1-i;j++)
            if(bt[j]>bt[j+1])
            {
                temp=bt[j]; bt[j]=bt[j+1]; bt[j+1]=temp;
                temp=p[j];  p[j]=p[j+1];   p[j+1]=temp;
            }

    wt[0]=0;
    tat[0]=bt[0];
    for(i=1;i<n;i++)
    {
        wt[i]=wt[i-1]+bt[i-1];
        tat[i]=wt[i]+bt[i];
    }
    for(i=0;i<n;i++)
    {
        total_wt+=wt[i];
        total_tat+=tat[i];
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i=0;i<n;i++)
        printf("P%d\t%d\t\t%d\t\t%d\n",p[i],bt[i],wt[i],tat[i]);
    printf("\nAverage waiting time = %.2f\n",total_wt/n);
    printf("Average turnaround time = %.2f\n",total_tat/n);
    return 0;
}

/*
 * Output:
 * Enter number of processes: 4
 * Enter burst time of each process:
 * P1: 6
 * P2: 8
 * P3: 7
 * P4: 3
 *
 * Process Burst Time      Waiting Time    Turnaround Time
 * P4      3               0               3
 * P1      6               3               9
 * P3      7               9               16
 * P2      8               16              24
 *
 * Average waiting time = 7.00
 * Average turnaround time = 13.00
 */

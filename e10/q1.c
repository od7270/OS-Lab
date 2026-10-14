/*
 * Ex. No. 10 – SCHEDULING ALGORITHMS: Priority and Round Robin
 * Q1. Write a program to implement the priority scheduling algorithm
 *
 * ---- Background from the manual ----
 *
 * ## 1. Priority scheduling algorithm
 *
 * Aim: To write a C program that simulates the priority CPU scheduling algorithm.
 *
 * Description: To find the average waiting time in priority scheduling, sort the burst
 * times by priority and then calculate the average waiting time of the processes. The
 * waiting time of each process is the sum of the burst times of all previous processes.
 *
 * Algorithm:
 *
 * 1. Start the process.
 * 2. Accept the number of processes in the ready queue.
 * 3. For each process in the ready queue, assign a process ID and accept its CPU burst
 * time (and priority).
 * 4. Sort the ready queue by priority number.
 * 5. Set the waiting time of the first process to 0 and its turnaround time to its burst
 * time.
 * 6. Arrange the processes by priority.
 * 7. For each process in the ready queue, calculate:
 * 8. a) Waiting time(n) = waiting time(n−1) + burst time(n−1)
 * b) Turnaround time(n) = waiting time(n) + burst time(n)
 * 9. Calculate:
 * c) Average waiting time = total waiting time / number of processes
 * d) Average turnaround time = total turnaround time / number of processes
 * Print the results in order.
 * 10. Stop.
 *
 * Source: OS_Lab_Manual.md, line 812
 */

#include <stdio.h>

int main()
{
    int n,i,j,temp,p[20],bt[20],pr[20],wt[20],tat[20];
    float total_wt=0,total_tat=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);
    printf("Enter burst time and priority of each process (lower number = higher priority):\n");
    for(i=0;i<n;i++)
    {
        printf("P%d: ",i+1);
        scanf("%d %d",&bt[i],&pr[i]);
        p[i]=i+1;
    }

    /* sort the ready queue by priority number */
    for(i=0;i<n-1;i++)
        for(j=0;j<n-1-i;j++)
            if(pr[j]>pr[j+1])
            {
                temp=pr[j]; pr[j]=pr[j+1]; pr[j+1]=temp;
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

    printf("\nProcess\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i=0;i<n;i++)
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n",p[i],pr[i],bt[i],wt[i],tat[i]);
    printf("\nAverage waiting time = %.2f\n",total_wt/n);
    printf("Average turnaround time = %.2f\n",total_tat/n);
    return 0;
}

/*
 * Output:
 * Enter number of processes: 5
 * Enter burst time and priority of each process (lower number = higher priority):
 * P1: 10 3
 * P2: 1 1
 * P3: 2 4
 * P4: 1 5
 * P5: 5 2
 *
 * Process Priority        Burst Time      Waiting Time    Turnaround Time
 * P2      1               1               0               1
 * P5      2               5               1               6
 * P1      3               10              6               16
 * P3      4               2               16              18
 * P4      5               1               18              19
 *
 * Average waiting time = 8.20
 * Average turnaround time = 12.00
 */

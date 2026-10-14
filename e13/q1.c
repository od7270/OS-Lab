/*
 * Ex. No. 13 – DISK SCHEDULING ALGORITHMS: FCFS, SCAN, C-SCAN
 * Q1. Write a program to simulate the FCFS, SCAN and C-SCAN disk scheduling algorithms
 *
 * ---- Background from the manual ----
 *
 * Aim: To write a C program that simulates the disk scheduling algorithms a) FCFS b) SCAN
 * c) C-SCAN
 *
 * Description: One of the operating system's responsibilities is to use the hardware
 * efficiently. For disk drives, that means fast access time and high disk bandwidth. Both
 * can be improved by managing the order in which disk I/O requests are serviced, which is
 * called disk scheduling.
 *
 * - FCFS: the simplest form of disk scheduling. It is fair by nature but generally does
 * not give the fastest service.
 * - SCAN: the disk arm starts at one end and moves toward the other end, servicing
 * requests as it reaches each cylinder. At the other end, the head reverses direction and
 * keeps servicing. The head sweeps back and forth across the disk continuously.
 * - C-SCAN: a variant of SCAN designed to give a more uniform wait time. Like SCAN, it
 * moves the head from one end of the disk to the other, servicing requests along the way.
 * When the head reaches the other end, it returns immediately to the beginning of the disk
 * without servicing any requests on the way back.
 *
 * Source: OS_Lab_Manual.md, line 897
 */

#include <stdio.h>
#include <stdlib.h>

int n,head,size,dir,req[50];

void sort(int a[],int len)
{
    int i,j,t;
    for(i=0;i<len-1;i++)
        for(j=0;j<len-1-i;j++)
            if(a[j]>a[j+1]) { t=a[j]; a[j]=a[j+1]; a[j+1]=t; }
}

/* Moves the head through order[] and prints the path and total head movement */
int travel(char *name,int order[],int len)
{
    int i,pos=head,total=0;
    printf("\n---- %s ----\nHead movement: %d",name,head);
    for(i=0;i<len;i++)
    {
        total+=abs(order[i]-pos);
        pos=order[i];
        printf(" -> %d",pos);
    }
    printf("\nTotal head movement = %d cylinders\n",total);
    return total;
}

void fcfs()
{
    travel("FCFS",req,n);
}

/* SCAN (elevator): go to the end in the chosen direction, then reverse */
void scan()
{
    int s[50],order[52],i,k=0,split=0;
    for(i=0;i<n;i++) s[i]=req[i];
    sort(s,n);
    while(split<n && s[split]<head) split++;    /* s[split..] >= head */

    if(dir==1)          /* towards higher cylinders first */
    {
        for(i=split;i<n;i++) order[k++]=s[i];
        order[k++]=size-1;
        for(i=split-1;i>=0;i--) order[k++]=s[i];
    }
    else                /* towards 0 first */
    {
        for(i=split-1;i>=0;i--) order[k++]=s[i];
        order[k++]=0;
        for(i=split;i<n;i++) order[k++]=s[i];
    }
    travel("SCAN",order,k);
}

/* C-SCAN: go to the end in the chosen direction, jump to the other end
   without servicing, then continue in the same direction.
   The jump is counted in the total head movement. */
void cscan()
{
    int s[50],order[53],i,k=0,split=0;
    for(i=0;i<n;i++) s[i]=req[i];
    sort(s,n);
    while(split<n && s[split]<head) split++;

    if(dir==1)
    {
        for(i=split;i<n;i++) order[k++]=s[i];
        order[k++]=size-1;
        order[k++]=0;
        for(i=0;i<split;i++) order[k++]=s[i];
    }
    else
    {
        for(i=split-1;i>=0;i--) order[k++]=s[i];
        order[k++]=0;
        order[k++]=size-1;
        for(i=n-1;i>=split;i--) order[k++]=s[i];
    }
    travel("C-SCAN",order,k);
}

int main()
{
    int i;
    printf("Enter number of requests: ");
    scanf("%d",&n);
    printf("Enter the request queue:\n");
    for(i=0;i<n;i++)
        scanf("%d",&req[i]);
    printf("Enter initial head position: ");
    scanf("%d",&head);
    printf("Enter disk size (number of cylinders): ");
    scanf("%d",&size);
    printf("Enter direction (1 = towards higher cylinders, 0 = towards 0): ");
    scanf("%d",&dir);

    fcfs();
    scan();
    cscan();
    return 0;
}

/*
 * Output (head moving towards higher cylinders):
 * Enter number of requests: 8
 * Enter the request queue:
 * 98 183 37 122 14 124 65 67
 * Enter initial head position: 53
 * Enter disk size (number of cylinders): 200
 * Enter direction (1 = towards higher cylinders, 0 = towards 0): 1
 *
 * ---- FCFS ----
 * Head movement: 53 -> 98 -> 183 -> 37 -> 122 -> 14 -> 124 -> 65 -> 67
 * Total head movement = 640 cylinders
 *
 * ---- SCAN ----
 * Head movement: 53 -> 65 -> 67 -> 98 -> 122 -> 124 -> 183 -> 199 -> 37 -> 14
 * Total head movement = 331 cylinders
 *
 * ---- C-SCAN ----
 * Head movement: 53 -> 65 -> 67 -> 98 -> 122 -> 124 -> 183 -> 199 -> 0 -> 14 -> 37
 * Total head movement = 382 cylinders
 *
 * Same input with direction 0 (towards 0): FCFS 640, SCAN 236 (53 -> ... -> 0 -> 65 ->
 * ... -> 183), C-SCAN 386.
 * C-SCAN counts the 199 -> 0 return jump. Some textbooks leave the jump out, which would
 * give 382 - 199 = 183.
 */

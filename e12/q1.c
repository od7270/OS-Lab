/*
 * Ex. No. 12 – MEMORY ALLOCATION TECHNIQUES: FIRST, BEST, WORST FIT
 * Q1. Write a program to simulate the First, Best and Worst fit memory allocation techniques
 *
 * ---- Background from the manual ----
 *
 * Aim: To write a C program that simulates the following contiguous memory allocation
 * techniques: a) Worst-fit b) Best-fit c) First-fit
 *
 * Description: One of the simplest methods of memory allocation is to divide memory into
 * several fixed-size partitions, each holding exactly one process. In this multiple-
 * partition method, when a partition is free, a process is selected from the input queue
 * and loaded into it. When the process terminates, the partition becomes available for
 * another process. The OS keeps a table showing which parts of memory are free and which
 * are occupied. When a process arrives and needs memory, it is given a section of memory
 * large enough for it. When a process is loaded or swapped into main memory and more than
 * one free block is large enough, the OS must decide which block to allocate:
 *
 * - Best-fit: chooses the block closest in size to the request.
 * - First-fit: chooses the first available block that is large enough.
 * - Worst-fit: chooses the largest available block.
 *
 * Source: OS_Lab_Manual.md, line 878
 */

#include <stdio.h>

int nb,np,block[20],proc[20];

/* Each block is a fixed partition and holds at most one process.
   strategy: 1 = First fit, 2 = Best fit, 3 = Worst fit */
void allocate(int strategy,char *name)
{
    int alloc[20],used[20]={0},i,j,pick;

    for(i=0;i<np;i++)
    {
        pick=-1;
        for(j=0;j<nb;j++)
        {
            if(used[j] || block[j]<proc[i])
                continue;
            if(strategy==1) { pick=j; break; }                       /* first big enough */
            if(pick==-1 ||
               (strategy==2 && block[j]<block[pick]) ||               /* smallest that fits */
               (strategy==3 && block[j]>block[pick]))                 /* largest */
                pick=j;
        }
        alloc[i]=pick;
        if(pick!=-1)
            used[pick]=1;
    }

    printf("\n---- %s ----\n",name);
    printf("Process\tSize\tBlock No.\tBlock Size\tFragment\n");
    for(i=0;i<np;i++)
    {
        if(alloc[i]!=-1)
            printf("P%d\t%d\t%d\t\t%d\t\t%d\n",i+1,proc[i],alloc[i]+1,
                   block[alloc[i]],block[alloc[i]]-proc[i]);
        else
            printf("P%d\t%d\tNot Allocated\n",i+1,proc[i]);
    }
}

int main()
{
    int i;
    printf("Enter number of memory blocks: ");
    scanf("%d",&nb);
    printf("Enter size of each block:\n");
    for(i=0;i<nb;i++)
        scanf("%d",&block[i]);
    printf("Enter number of processes: ");
    scanf("%d",&np);
    printf("Enter size of each process:\n");
    for(i=0;i<np;i++)
        scanf("%d",&proc[i]);

    allocate(1,"First Fit");
    allocate(2,"Best Fit");
    allocate(3,"Worst Fit");
    return 0;
}

/*
 * Output:
 * Enter number of memory blocks: 5
 * Enter size of each block:
 * 100 500 200 300 600
 * Enter number of processes: 4
 * Enter size of each process:
 * 212 417 112 426
 *
 * ---- First Fit ----
 * Process Size    Block No.       Block Size      Fragment
 * P1      212     2               500             288
 * P2      417     5               600             183
 * P3      112     3               200             88
 * P4      426     Not Allocated
 *
 * ---- Best Fit ----
 * Process Size    Block No.       Block Size      Fragment
 * P1      212     4               300             88
 * P2      417     2               500             83
 * P3      112     3               200             88
 * P4      426     5               600             174
 *
 * ---- Worst Fit ----
 * Process Size    Block No.       Block Size      Fragment
 * P1      212     5               600             388
 * P2      417     2               500             83
 * P3      112     4               300             188
 * P4      426     Not Allocated
 *
 * Explanation: best fit is the only strategy that places all four processes. First and
 * worst fit use up the 500 and 600 blocks early, so nothing is left for the 426 process.
 * "Fragment" is the internal fragmentation (block size - process size).
 */

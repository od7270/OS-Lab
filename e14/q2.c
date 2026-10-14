/*
 * Ex. No. 14 – FILE ALLOCATION STRATEGIES: SEQUENTIAL and INDEXED
 * Q2. Write a program to implement the indexed file allocation method
 *
 * ---- Background from the manual ----
 *
 * ## B) Indexed
 *
 * Aim (as written in the manual): To implement an allocation method using the chained
 * method.
 *
 * Description: In the chained method, the file allocation table has a field that points to
 * the starting block of the file. Each block then holds a pointer to the next block, so
 * there is no external fragmentation.
 *
 * Algorithm:
 *
 * 1. Start the program.
 * 2. Get the number of files.
 * 3. Get the memory requirement of each file.
 * 4. Allocate the required locations by selecting a random location, q = random(100);
 * - a) Check whether the selected location is free.
 * - b) If it is free, allocate it and set flag=1:
 *          q=random(100);
 *          {
 *              if(b[q].flag==0)
 *              b[q].flag=1;
 *              b[q].fno=j;
 *              r[i][j]=q;
 * 5. Print the results: file no., length, blocks allocated.
 * 6. Stop the program.
 *
 * Manual note: the heading says *Indexed*, but the aim and description describe *chained
 * (linked)* allocation. Q2 asks for indexed allocation, where each file has an index block
 * that lists all of its data blocks.
 *
 * Source: OS_Lab_Manual.md, line 975
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DISK 100

struct block
{
    int flag;               /* 1 when allocated */
    int fno;                /* file that owns the block */
} b[DISK];

/* q = random(100) until a free block is found */
int get_free_block(int fno)
{
    int q;
    do
        q=rand()%DISK;
    while(b[q].flag!=0);
    b[q].flag=1;
    b[q].fno=fno;
    return q;
}

int main()
{
    int n,len[20],index[20],r[20][DISK],i,j,total=0;

    srand(time(NULL));
    for(i=0;i<DISK;i++)
        b[i].flag=0;

    printf("Enter number of files: ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("Enter memory requirement (blocks) of file %d: ",i+1);
        scanf("%d",&len[i]);
        total+=len[i]+1;    /* data blocks + one index block */
    }
    if(total>DISK)
    {
        printf("Not enough disk space (%d blocks needed, %d available)\n",total,DISK);
        return 1;
    }

    for(i=0;i<n;i++)
    {
        index[i]=get_free_block(i+1);           /* the file's index block */
        for(j=0;j<len[i];j++)
            r[i][j]=get_free_block(i+1);        /* data blocks, anywhere on disk */
    }

    printf("\nFile No.\tIndex Block\tLength\tBlocks Allocated (index block contents)\n");
    for(i=0;i<n;i++)
    {
        printf("%d\t\t%d\t\t%d\t",i+1,index[i],len[i]);
        for(j=0;j<len[i];j++)
            printf("%d ",r[i][j]);
        printf("\n");
    }

    printf("\nEnter a file number to view its index block: ");
    if(scanf("%d",&i)==1 && i>=1 && i<=n)
    {
        printf("Index block %d of file %d:\n",index[i-1],i);
        for(j=0;j<len[i-1];j++)
            printf("  entry %d -> block %d\n",j,r[i-1][j]);
    }
    return 0;
}

/*
 * Output (blocks are chosen randomly, so they change every run):
 * Enter number of files: 3
 * Enter memory requirement (blocks) of file 1: 4
 * Enter memory requirement (blocks) of file 2: 6
 * Enter memory requirement (blocks) of file 3: 3
 *
 * File No.        Index Block     Length  Blocks Allocated (index block contents)
 * 1               11              4       68 21 64 13
 * 2               16              6       36 87 75 46 10 62
 * 3               55              3       73 33 65
 *
 * Enter a file number to view its index block: 2
 * Index block 16 of file 2:
 *   entry 0 -> block 36
 *   entry 1 -> block 87
 *   entry 2 -> block 75
 *   entry 3 -> block 46
 *   entry 4 -> block 10
 *   entry 5 -> block 62
 *
 * Unlike sequential allocation, the data blocks can be anywhere on the disk. The
 * file's index block lists them in order, so there is no external fragmentation and
 * any block can be reached directly.
 */

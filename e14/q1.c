/*
 * Ex. No. 14 – FILE ALLOCATION STRATEGIES: SEQUENTIAL and INDEXED
 * Q1. Write a program to implement the sequential file allocation method
 *
 * ---- Background from the manual ----
 *
 * ## A) Sequential
 *
 * Aim: To write a C program that implements the sequential file allocation method.
 *
 * Description: The sequential file is the most common file structure. It uses a fixed
 * format for records: all records have the same length and consist of the same number of
 * fixed-length fields in a fixed order. Because the length and position of each field are
 * known, only the field values need to be stored. The field names and lengths are
 * attributes of the file structure.
 *
 * Algorithm:
 *
 * 1. Start the program.
 * 2. Get the number of files.
 * 3. Get the memory requirement of each file.
 * 4. Allocate the required locations to each file in sequential order:
 * - Randomly select a starting location from the available locations: s1 = random(100);
 * - a) Check whether the required locations starting at the selected location are free:
 *          if(b[s1].flag==0){
 *              for(j=s1;j<s1+p[i];j++){
 *                  if((b[j].flag)==0)count++;
 *              }
 *              if(count==p[i]) break;
 *          }
 * - b) Allocate the locations and set flag=1 for each one:
 *          for(s=s1;s<(s1+p[i]);s++)
 *          {
 *              k[i][j]=s; j=j+1; b[s].bno=s;
 *              b[s].flag=1;
 *          }
 * 5. Print the results: file no., length, blocks allocated.
 * 6. Stop the program.
 *
 * Source: OS_Lab_Manual.md, line 941
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DISK 100

struct block
{
    int bno,flag;           /* flag = 1 when the block is allocated */
} b[DISK];

int main()
{
    int n,p[20],k[20][DISK],start[20],i,j,s,s1,count,tries;

    srand(time(NULL));
    for(i=0;i<DISK;i++)
    {
        b[i].bno=i;
        b[i].flag=0;
    }

    printf("Enter number of files: ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("Enter memory requirement (blocks) of file %d: ",i+1);
        scanf("%d",&p[i]);
    }

    for(i=0;i<n;i++)
    {
        start[i]=-1;
        /* randomly pick a start location until p[i] contiguous blocks are free */
        for(tries=0;tries<1000;tries++)
        {
            s1=rand()%DISK;
            if(s1+p[i]>DISK || b[s1].flag!=0)
                continue;
            count=0;
            for(j=s1;j<s1+p[i];j++)
                if(b[j].flag==0)
                    count++;
            if(count==p[i])
            {
                start[i]=s1;
                break;
            }
        }
        if(start[i]==-1)
            continue;       /* no contiguous space found */
        j=0;
        for(s=s1;s<(s1+p[i]);s++)
        {
            k[i][j]=s;
            j=j+1;
            b[s].bno=s;
            b[s].flag=1;
        }
    }

    printf("\nFile No.\tLength\tStart\tBlocks Allocated\n");
    for(i=0;i<n;i++)
    {
        if(start[i]==-1)
        {
            printf("%d\t\t%d\t-\tNot allocated (no contiguous space)\n",i+1,p[i]);
            continue;
        }
        printf("%d\t\t%d\t%d\t",i+1,p[i],start[i]);
        for(j=0;j<p[i];j++)
            printf("%d ",k[i][j]);
        printf("\n");
    }
    return 0;
}

/*
 * Output (start blocks are chosen randomly, so they change every run):
 * Enter number of files: 3
 * Enter memory requirement (blocks) of file 1: 4
 * Enter memory requirement (blocks) of file 2: 6
 * Enter memory requirement (blocks) of file 3: 3
 *
 * File No.        Length  Start   Blocks Allocated
 * 1               4       11      11 12 13 14
 * 2               6       68      68 69 70 71 72 73
 * 3               3       21      21 22 23
 *
 * Each file gets one contiguous run of blocks starting at a random free location
 * (s1 = random(100)), and only if all p[i] blocks from s1 onward are free.
 */

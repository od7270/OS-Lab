/*
 * Ex. No. 11 – PAGE REPLACEMENT ALGORITHMS: FIFO, LRU, LFU
 * Q1. Write a program to simulate the FIFO, LRU and LFU page replacement algorithms
 *
 * ---- Background from the manual ----
 *
 * Aim: To implement different page replacement techniques: a) FIFO b) LRU c) LFU
 *
 * Description: Page replacement algorithms are an important part of virtual memory
 * management. They help the OS decide which page in memory to move out to make space for
 * the page that is needed now. The goal of every page replacement algorithm is to reduce
 * the number of page faults.
 *
 * - FIFO: the simplest page replacement algorithm. The OS keeps all pages in memory in a
 * queue, with the oldest page at the front. When a page must be replaced, the page at the
 * front of the queue is removed.
 * - LRU (Least Recently Used): tracks page usage over a short period of time. It assumes
 * that pages used heavily in the recent past are likely to be used heavily again soon, and
 * it removes the page that has gone unused for the longest time. LRU is the most widely
 * used algorithm because it gives fewer page faults than the other methods.
 * - LFU (Least Frequently Used): removes the page with the fewest accesses in a given
 * period of time. If several pages have the same frequency, the one that came first is
 * replaced first.
 *
 * Source: OS_Lab_Manual.md, line 859
 */

#include <stdio.h>

int n,nf,ref[50];

void print_frames(int frame[],int page,int fault)
{
    int j;
    printf("%d\t",page);
    for(j=0;j<nf;j++)
    {
        if(frame[j]==-1) printf("-  ");
        else printf("%-3d",frame[j]);
    }
    printf("%s\n",fault?"  Page Fault":"");
}

int find(int frame[],int page)
{
    int j;
    for(j=0;j<nf;j++)
        if(frame[j]==page)
            return j;
    return -1;
}

/* FIFO: replace the page that was loaded first (front of the queue) */
int fifo()
{
    int frame[10],i,j,front=0,faults=0;
    for(j=0;j<nf;j++) frame[j]=-1;
    printf("\n---- FIFO ----\nRef\tFrames\n");
    for(i=0;i<n;i++)
    {
        int fault=0;
        if(find(frame,ref[i])==-1)
        {
            frame[front]=ref[i];        /* empty frames fill in order too */
            front=(front+1)%nf;
            faults++;
            fault=1;
        }
        print_frames(frame,ref[i],fault);
    }
    printf("Total page faults (FIFO) = %d\n",faults);
    return faults;
}

/* LRU: replace the page whose last use is furthest in the past */
int lru()
{
    int frame[10],last[10],i,j,pos,faults=0;
    for(j=0;j<nf;j++) frame[j]=-1;
    printf("\n---- LRU ----\nRef\tFrames\n");
    for(i=0;i<n;i++)
    {
        int fault=0;
        pos=find(frame,ref[i]);
        if(pos==-1)
        {
            pos=0;
            for(j=0;j<nf;j++)
            {
                if(frame[j]==-1) { pos=j; break; }
                if(last[j]<last[pos]) pos=j;
            }
            frame[pos]=ref[i];
            faults++;
            fault=1;
        }
        last[pos]=i;                    /* time of most recent use */
        print_frames(frame,ref[i],fault);
    }
    printf("Total page faults (LRU) = %d\n",faults);
    return faults;
}

/* LFU: replace the page used least often since it was loaded;
   on a tie, replace the page that came in first */
int lfu()
{
    int frame[10],freq[10],arrival[10],i,j,pos,faults=0;
    for(j=0;j<nf;j++) frame[j]=-1;
    printf("\n---- LFU ----\nRef\tFrames\n");
    for(i=0;i<n;i++)
    {
        int fault=0;
        pos=find(frame,ref[i]);
        if(pos!=-1)
            freq[pos]++;
        else
        {
            pos=0;
            for(j=0;j<nf;j++)
            {
                if(frame[j]==-1) { pos=j; break; }
                if(freq[j]<freq[pos] || (freq[j]==freq[pos] && arrival[j]<arrival[pos]))
                    pos=j;
            }
            frame[pos]=ref[i];
            freq[pos]=1;
            arrival[pos]=i;
            faults++;
            fault=1;
        }
        print_frames(frame,ref[i],fault);
    }
    printf("Total page faults (LFU) = %d\n",faults);
    return faults;
}

int main()
{
    int i,f1,f2,f3;
    printf("Enter number of pages in reference string: ");
    scanf("%d",&n);
    printf("Enter the reference string:\n");
    for(i=0;i<n;i++)
        scanf("%d",&ref[i]);
    printf("Enter number of frames: ");
    scanf("%d",&nf);

    f1=fifo();
    f2=lru();
    f3=lfu();

    printf("\nSummary: FIFO = %d, LRU = %d, LFU = %d page faults\n",f1,f2,f3);
    return 0;
}

/*
 * Output:
 * Enter number of pages in reference string: 20
 * Enter the reference string:
 * 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
 * Enter number of frames: 3
 *
 * ---- FIFO ----
 * Ref	Frames
 * 7	7  -  -    Page Fault
 * 0	7  0  -    Page Fault
 * 1	7  0  1    Page Fault
 * 2	2  0  1    Page Fault
 * 0	2  0  1
 * 3	2  3  1    Page Fault
 * 0	2  3  0    Page Fault
 * 4	4  3  0    Page Fault
 * 2	4  2  0    Page Fault
 * 3	4  2  3    Page Fault
 * 0	0  2  3    Page Fault
 * 3	0  2  3
 * 2	0  2  3
 * 1	0  1  3    Page Fault
 * 2	0  1  2    Page Fault
 * 0	0  1  2
 * 1	0  1  2
 * 7	7  1  2    Page Fault
 * 0	7  0  2    Page Fault
 * 1	7  0  1    Page Fault
 * Total page faults (FIFO) = 15
 *
 * ---- LRU ----
 * Ref	Frames
 * 7	7  -  -    Page Fault
 * 0	7  0  -    Page Fault
 * 1	7  0  1    Page Fault
 * 2	2  0  1    Page Fault
 * 0	2  0  1
 * 3	2  0  3    Page Fault
 * 0	2  0  3
 * 4	4  0  3    Page Fault
 * 2	4  0  2    Page Fault
 * 3	4  3  2    Page Fault
 * 0	0  3  2    Page Fault
 * 3	0  3  2
 * 2	0  3  2
 * 1	1  3  2    Page Fault
 * 2	1  3  2
 * 0	1  0  2    Page Fault
 * 1	1  0  2
 * 7	1  0  7    Page Fault
 * 0	1  0  7
 * 1	1  0  7
 * Total page faults (LRU) = 12
 *
 * ---- LFU ----
 * Ref	Frames
 * 7	7  -  -    Page Fault
 * 0	7  0  -    Page Fault
 * 1	7  0  1    Page Fault
 * 2	2  0  1    Page Fault
 * 0	2  0  1
 * 3	2  0  3    Page Fault
 * 0	2  0  3
 * 4	4  0  3    Page Fault
 * 2	4  0  2    Page Fault
 * 3	3  0  2    Page Fault
 * 0	3  0  2
 * 3	3  0  2
 * 2	3  0  2
 * 1	3  0  1    Page Fault
 * 2	3  0  2    Page Fault
 * 0	3  0  2
 * 1	3  0  1    Page Fault
 * 7	3  0  7    Page Fault
 * 0	3  0  7
 * 1	3  0  1    Page Fault
 * Total page faults (LFU) = 13
 *
 * Summary: FIFO = 15, LRU = 12, LFU = 13 page faults
 *
 * Explanation:
 *  - FIFO evicts the oldest page, even one that is used heavily (it threw out 0 just
 *    before 0 was needed again).
 *  - LRU looks at recent use, which works best on this string (12 faults, the textbook value).
 *  - LFU keeps page 0 (used most often) and breaks ties between equal counts with FIFO,
 *    as the manual says.
 */

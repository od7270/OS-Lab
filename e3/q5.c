/*
 * Ex. No. 3 – PROCESS CREATION using `fork()` and usage of `getpid()`, `getppid()`, `wait()` functions
 * Q5. How many child processes are created for the following code?
 *
 * Hint: check with small values of n.
 *
 * Source: OS_Lab_Manual.md, line 142
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    int i,n;
    printf("Enter the value of n : ");
    scanf("%d",&n);
    fflush(stdout);
    for (i=0; i<n; i++)
        fork();
    printf("Process %d (parent %d)\n",getpid(),getppid());
    while(wait(NULL)>0);   /* let every parent wait so all lines are printed */
    return 0;
}

/*
 * Answer: 2^n - 1 child processes are created.
 * Each iteration doubles the number of processes, so after n iterations there are
 * 2^n processes in total. One of them is the original parent, so 2^n - 1 are children.
 *   n = 1 -> 1 child, n = 2 -> 3 children, n = 3 -> 7 children, n = 4 -> 15 children.
 */

/*
 * Output (n = 3; PIDs differ every run):
 * Enter the value of n : 3
 * Process 7158 (parent 7154)
 * Process 7159 (parent 7156)
 * Process 7160 (parent 7155)
 * Process 7157 (parent 7153)
 * Process 7156 (parent 7154)
 * Process 7155 (parent 7153)
 * Process 7154 (parent 7153)
 * Process 7153 (parent 7092)
 * 8 processes = 1 original (7153) + 7 children = 2^3 - 1 children.
 */

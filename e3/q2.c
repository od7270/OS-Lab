/*
 * Ex. No. 3 – PROCESS CREATION using `fork()` and usage of `getpid()`, `getppid()`, `wait()` functions
 * Q2. Rewrite the program in Q1 using `vfork()` and write the output
 *
 * Source: OS_Lab_Manual.md, line 93
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    int a=5,b=10,pid;
    printf("Before fork a=%d b=%d \n",a,b);
    pid=vfork();
    if(pid==0)
    {
        a=a+1; b=b+1;
        printf("In child a=%d b=%d \n",a,b);
        _exit(0);   /* a vfork() child must leave with _exit(), not return */
    }
    else
    {
        sleep(1);
        a=a-1; b=b-1;
        printf("In Parent a=%d b=%d \n",a,b);
    }
    return 0;
}

/*
 * Explanation:
 * vfork() does not copy memory: the child runs in the parent's address space and
 * the parent is suspended until the child calls _exit(). The child's update
 * (5,10 -> 6,11) is therefore made to the parent's own variables, and the parent
 * then decrements those (6,11 -> 5,10). Compare with Q1, where the parent printed 4 9.
 * Returning from main() in a vfork() child would destroy the parent's stack frame,
 * which is why the child uses _exit(0).
 */

/*
 * Output (Linux, gcc default -O0):
 * Before fork a=5 b=10
 * In child a=6 b=11
 * In Parent a=5 b=10
 *
 * Note: on macOS vfork() does not share the child's changes, so there the parent prints
 * "In Parent a=4 b=9", the same as fork(). Compiling with -O2 can also keep a and b in
 * registers and hide the sharing. The lab answer is the Linux output above.
 */

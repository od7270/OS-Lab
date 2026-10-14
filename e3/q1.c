/*
 * Ex. No. 3 – PROCESS CREATION using `fork()` and usage of `getpid()`, `getppid()`, `wait()` functions
 * Q1. Find the output of the following program
 *
 * ---- Background from the manual ----
 *
 * ## Syntax for process creation
 *
 *     int fork();
 *
 * Returns 0 in the child process and the child's process ID in the parent process.
 *
 * ## Other related functions
 *
 * | Function | Purpose |
 * |---|---|
 * | int getpid() | returns the current process ID |
 * | int getppid() | returns the parent process ID |
 * | wait() | makes a process wait for another process to complete |
 *
 * Virtual fork: vfork() is similar to fork(), but both processes share the same address
 * space.
 *
 * Source: OS_Lab_Manual.md, line 66
 */

#include <stdio.h>
#include <unistd.h>
int main()
{
    int a=5,b=10,pid;
    printf("Before fork a=%d b=%d \n",a,b);
    pid=fork();
    if(pid==0)
    {
        a=a+1; b=b+1;
        printf("In child a=%d b=%d \n",a,b);
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
 * fork() gives the child its own copy of the parent's memory. The child changes
 * its copy (5,10 -> 6,11) and the parent changes its own copy (5,10 -> 4,9), so
 * neither sees the other's update. sleep(1) in the parent makes the child print first.
 */

/*
 * Output (Linux terminal):
 * Before fork a=5 b=10
 * In child a=6 b=11
 * In Parent a=4 b=9
 *
 * Note: if output is redirected to a file (./a.out > out.txt), "Before fork" is printed
 * twice. stdout is then fully buffered, the line is still in the buffer at fork(), and
 * both processes flush their own copy. In a terminal stdout is line-buffered, so it
 * prints once.
 */

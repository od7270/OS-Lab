/*
 * Ex. No. 3 – PROCESS CREATION using `fork()` and usage of `getpid()`, `getppid()`, `wait()` functions
 * Q6. Print the Child process ID and Parent process ID in both the Child and the Parent processes
 *
 * Sample output:
 *
 *     In Child Process
 *     Parent Process ID : 18
 *     Child Process ID : 20
 *     In Parent Process
 *     Parent Process ID : 18
 *     Child Process ID : 20
 *
 * Source: OS_Lab_Manual.md, line 153
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    int pid;
    pid=fork();
    if(pid==0)
    {
        printf("In Child Process\n");
        printf("Parent Process ID : %d\n",getppid());
        printf("Child Process ID : %d\n",getpid());
    }
    else
    {
        wait(NULL);   /* so the child's lines come first */
        printf("In Parent Process\n");
        printf("Parent Process ID : %d\n",getpid());
        printf("Child Process ID : %d\n",pid);
    }
    return 0;
}

/*
 * Output (PIDs differ every run):
 * In Child Process
 * Parent Process ID : 7161
 * Child Process ID : 7162
 * In Parent Process
 * Parent Process ID : 7161
 * Child Process ID : 7162
 */

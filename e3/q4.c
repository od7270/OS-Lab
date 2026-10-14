/*
 * Ex. No. 3 – PROCESS CREATION using `fork()` and usage of `getpid()`, `getppid()`, `wait()` functions
 * Q4. Complete the program
 *
 * The child process calculates the sum of odd numbers and the parent process calculates
 * the sum of even numbers up to the number n. Make sure the parent process waits for the
 * child process to finish.
 *
 * Sample output:
 *
 *     Enter the value of n 10
 *     Sum of odd numbers 25
 *     Sum of even numbers : 30
 *
 * Manual note: printf("Enter the value of n : ",a); refers to an undeclared variable a, so
 * drop the ,a. wait() needs #include <sys/wait.h>.
 *
 * Source: OS_Lab_Manual.md, line 114
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    int pid,n,oddsum=0,evensum=0,i;
    printf("Enter the value of n : ");
    scanf("%d",&n);
    pid=fork();
    if(pid==0)
    {
        /* child: sum of odd numbers up to n */
        for(i=1;i<=n;i+=2)
            oddsum=oddsum+i;
        printf("Sum of odd numbers %d\n",oddsum);
    }
    else
    {
        wait(NULL);   /* parent waits for the child to finish */
        /* parent: sum of even numbers up to n */
        for(i=2;i<=n;i+=2)
            evensum=evensum+i;
        printf("Sum of even numbers : %d\n",evensum);
    }
    return 0;
}

/*
 * Output:
 * Enter the value of n : 10
 * Sum of odd numbers 25
 * Sum of even numbers : 30
 */

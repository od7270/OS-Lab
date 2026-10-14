/*
 * Ex. No. 3 – PROCESS CREATION using `fork()` and usage of `getpid()`, `getppid()`, `wait()` functions
 * Q7. How many child processes are created for the following code?
 *
 * Source: OS_Lab_Manual.md, line 175
 */

#include <stdio.h>
#include <unistd.h>
int main()
{
    fork();
    fork()&&fork()||fork();
    fork();
    printf("Yes ");
    return 0;
}

/*
 * Answer: 19 child processes are created ("Yes " is printed 20 times).
 *
 * Line 1, fork(): 1 process -> 2.
 * Line 2, fork()&&fork()||fork(), for each process (A && B || C):
 *   - A returns non-zero in the parent, so B runs:
 *       - B non-zero (parent): A && B is true, so C is skipped.
 *       - B == 0 (child): A && B is false, so C runs and forks once more.
 *   - A == 0 in its child: && short-circuits to false, so C runs and forks.
 *   Each process becomes 5 processes, so 2 -> 10.
 * Line 3, fork(): 10 -> 20.
 * Total 20 processes = 1 original parent + 19 children.
 */

/*
 * Output:
 * Yes Yes Yes Yes Yes Yes Yes Yes Yes Yes Yes Yes Yes Yes Yes Yes Yes Yes Yes Yes
 * ("Yes " x 20 -> 20 processes -> 19 child processes)
 */

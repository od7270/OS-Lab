/*
 * Ex. No. 3 – PROCESS CREATION using `fork()` and usage of `getpid()`, `getppid()`, `wait()` functions
 * Q3. Calculate the number of times the text "SRMIST" is printed
 *
 * Manual note: the PDF uses curly quotes (“SRMIST\n”), which will not compile. Use
 * straight quotes.
 *
 * Source: OS_Lab_Manual.md, line 95
 */

#include <stdio.h>
#include <unistd.h>
int main()
{
    fork();
    fork();
    fork();
    printf("SRMIST\n");
    return 0;
}

/*
 * Answer: "SRMIST" is printed 8 times.
 * Each fork() doubles the number of processes: 1 -> 2 -> 4 -> 8. All 8 processes
 * reach the printf, so the text is printed 2^3 = 8 times (7 of them by child processes).
 */

/*
 * Output:
 * SRMIST
 * SRMIST
 * SRMIST
 * SRMIST
 * SRMIST
 * SRMIST
 * SRMIST
 * SRMIST
 */

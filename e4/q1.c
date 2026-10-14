/*
 * Ex. No. 4 – MULTI-THREADING
 * Q1. Program: implementing a program using threads
 *
 * Program description: Create 3 threads. The first finds the sum of odd numbers, the
 * second finds the sum of even numbers, and the third finds the sum of natural numbers.
 * The program also displays the lists of odd and even numbers.
 *
 * Complete the code wherever applicable. The parts to complete are highlighted in red in
 * the PDF and appear here as plain-English placeholders.
 *
 * Manual note: the missing header is <pthread.h>. Odd() and SumN() use threadid but don't
 * declare it, so give them the signature void *Odd(void *threadid). On 64-bit systems, the
 * (int)threadid and (void *)t casts give warnings; use (long) / (intptr_t) instead. Odd
 * numbers also need to be stored in oddarr[jo++].
 *
 * Result: The program was executed successfully by creating three threads.
 *
 * ---- Background from the manual ----
 *
 * Aim: Write a C program to demonstrate various thread-related concepts.
 *
 * ## Threads
 *
 * A thread is a path that is followed during a program's execution. Most programs written
 * today run as a single thread. For example, a program may not be able to read keystrokes
 * while it is drawing, because those tasks cannot run at the same time. Multitasking
 * solves this by letting two or more tasks run simultaneously.
 *
 * There are two types of multitasking: process-based and thread-based. Process-based
 * multitasking is managed entirely by the OS. Multitasking through multithreading can be
 * controlled by the programmer to some extent.
 *
 * - A process is a program being executed. A process can be divided further into
 * independent units called threads.
 * - A thread is like a small, lightweight process within a process. A collection of
 * threads makes up a process.
 *
 * *(Figure in PDF: a single-threaded process has one thread of execution, a single
 * instruction stream. A multi-threaded process has several threads of execution, multiple
 * instruction streams. Both share a common process.)*
 *
 * Why multithreading? Threads are a popular way to improve applications through
 * parallelism. For example, each browser tab can be a different thread, and MS Word uses
 * one thread to format text and another to process input.
 *
 * Threads operate faster than processes because:
 *
 * 1. Thread creation is much faster.
 * 2. Context switching between threads is much faster.
 * 3. Threads can be terminated easily.
 * 4. Communication between threads is faster.
 *
 * Unlike Java, C does not support multithreading in its language standard. POSIX Threads
 * (Pthreads) is the POSIX standard for threads, and an implementation is available with
 * gcc. Include pthread.h to use the pthreads library.
 *
 * ## Pthread functions
 *
 * a. pthread_create: creates a new thread.
 *
 *     int pthread_create(pthread_t *thread,
 *                        const pthread_attr_t *attr,
 *                        void *(*start_routine)(void *),
 *                        void *arg);
 *
 * - thread: pointer to an unsigned integer value that returns the ID of the created
 * thread.
 * - attr: pointer to a structure that defines thread attributes such as detached state,
 * scheduling policy and stack address. Set it to NULL for default attributes.
 * - start_routine: pointer to the subroutine that the thread executes. Its return type and
 * parameter type must be void *. It takes a single argument, so pass a struct when you
 * need several values.
 * - arg: pointer to void that holds the argument for the function in the previous
 * parameter.
 *
 * b. pthread_exit: terminates a thread.
 *
 *     void pthread_exit(void *retval);
 *
 * retval is a mandatory pointer to an integer that stores the return status of the
 * terminated thread. It must have global scope so that any thread waiting to join this
 * thread can read the return status.
 *
 * c. pthread_join: waits for a thread to terminate.
 *
 *     int pthread_join(pthread_t th, void thread_return);
 *
 * - th: ID of the thread that the current thread waits for.
 * - thread_return: pointer to the location where the exit status of thread th is stored.
 *
 * d. pthread_self: returns the ID of the current thread.
 *
 *     pthread_t pthread_self(void);
 *
 * e. pthread_equal: checks whether two threads are the same. Returns non-zero if they are
 * equal, otherwise zero.
 *
 *     int pthread_equal(pthread_t t1, pthread_t t2);
 *
 * - t1: ID of the first thread
 * - t2: ID of the second thread
 *
 * ## Applications
 *
 * Threading is used widely in almost every field. It is most visible on the internet,
 * where every kind of transaction is processed (recharges, online transfers, banking and
 * so on). Threading divides code into small, lightweight parts that put less load on CPU
 * and memory, so the work gets done faster.
 *
 * Source: OS_Lab_Manual.md, line 278
 */

#include <pthread.h>
#include <stdint.h>
#include<stdio.h>
#define NUM_THREADS 3
int je,jo,evensum=0,sumn=0,oddsum=0,evenarr[50],oddarr[50];

void *Even(void *threadid)
{
    int i,n; je=0;
    n=(int)(intptr_t)threadid;
    for(i=1;i<=n;i++)
    {
        if(i%2==0)
        {
            evenarr[je]=i;
            evensum=evensum+i;
            je++;
        }
    }
    return NULL;
}

void *Odd(void *threadid)
{
    int i,n; jo=0;
    n=(int)(intptr_t)threadid;
    for(i=0;i<=n;i++)
    {
        if(i%2!=0)
        {
            oddarr[jo]=i;
            oddsum=oddsum+i;
            jo++;
        }
    }
    return NULL;
}

void *SumN(void *threadid)
{
    int i,n;
    n=(int)(intptr_t)threadid;
    for(i=1;i<=n;i++)
    {
        sumn=sumn+i;
    }
    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int i,t;
    printf("Enter a number\n");
    scanf("%d",&t);
    pthread_create(&threads[0], NULL, Even, (void *)(intptr_t)t);
    pthread_create(&threads[1], NULL, Odd, (void *)(intptr_t)t);
    pthread_create(&threads[2], NULL, SumN, (void *)(intptr_t)t);
    for(i=0;i<NUM_THREADS;i++)
    {
        pthread_join(threads[i],NULL);
    }
    printf("The sum of first N natural numbers is %d\n",sumn);
    printf("The sum of first N even numbers is %d\n",evensum);
    printf("The sum of first N odd numbers is %d\n",oddsum);
    printf("The first N Even numbers are ---- \n");
    for(i=0;i<je;i++)
        printf("%d ",evenarr[i]);
    printf("\n");
    printf("The first N Odd numbers are ---- \n");
    for(i=0;i<jo;i++)
        printf("%d ",oddarr[i]);
    printf("\n");
    pthread_exit(NULL);
}

/*
 * Compile: gcc q1.c -o q1 -lpthread
 * Each thread writes only its own globals (evensum/evenarr/je, oddsum/oddarr/jo, sumn),
 * so no locking is needed. main() reads them only after pthread_join() on all three.
 * Inputs above 99 overflow evenarr[50]/oddarr[50].
 */

/*
 * Output:
 * Enter a number
 * 10
 * The sum of first N natural numbers is 55
 * The sum of first N even numbers is 30
 * The sum of first N odd numbers is 25
 * The first N Even numbers are ----
 * 2 4 6 8 10
 * The first N Odd numbers are ----
 * 1 3 5 7 9
 */

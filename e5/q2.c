/*
 * Ex. No. 5 – Mutual Exclusion using Semaphore and Monitor
 * Q2. Two threads with a shared variable
 *
 * The program creates two threads. One increments the value of a shared variable and the
 * other decrements it. Both threads use a semaphore so that only one thread at a time is
 * in its critical section. Execute the program and write the output.
 *
 * Explanation (from the manual): The final value of shared will be 1. When either thread
 * executes the wait operation, the value of s becomes 0. The other thread, even if it
 * preempts the running thread, cannot complete its wait operation on s, so it cannot read
 * an inconsistent value of the shared variable. Only one thread can be in its critical
 * section at any given time.
 *
 * ---- Background from the manual ----
 *
 * ## POSIX semaphore
 *
 * Linux provides a built-in POSIX semaphore library. Include semaphore.h and compile with
 * -lpthread -lrt.
 *
 * | Operation | Call |
 * |---|---|
 * | Lock / wait | int sem_wait(sem_t *sem); |
 * | Release / signal | int sem_post(sem_t *sem); |
 * | Initialize | sem_init(sem_t *sem, int pshared, unsigned int value); |
 * | Destroy | sem_destroy(sem_t *mutex); |
 *
 * sem_init parameters:
 *
 * - sem: the semaphore to initialize.
 * - pshared: whether the new semaphore is shared between processes or between threads.
 * Non-zero means it is shared between processes. Zero means it is shared between threads.
 * - value: the initial value of the semaphore.
 *
 * Source: OS_Lab_Manual.md, line 468
 */

#include<pthread.h>
#include<stdio.h>
#include<semaphore.h>
#include<unistd.h>
void *fun1();
void *fun2();
int shared=1; //shared variable
sem_t s; //semaphore variable
int main()
{
    sem_init(&s,0,1); //initialize semaphore variable - 1st argument is
    //address of variable, 2nd is number of processes sharing semaphore,
    //3rd argument is the initial value of semaphore variable
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, fun1, NULL);
    sleep(1);
    pthread_create(&thread2, NULL, fun2, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2,NULL);
    printf("Final value of shared is %d\n",shared); //prints the last
    //updated value of shared variable
    sem_destroy(&s);
    return 0;
}
void *fun1()
{
    int x;
    sem_wait(&s); //executes wait operation on s
    x=shared;//thread1 reads value of shared variable
    printf("Thread1 reads the value as %d\n",x);
    x++; //thread1 increments its value
    printf("Local updation by Thread1: %d\n",x);
    sleep(1); //thread1 is preempted by thread 2
    shared=x; //thread one updates the value of shared variable
    printf("Value of shared variable updated by Thread1 is: %d\n",shared);
    sem_post(&s);
    return NULL;
}
void *fun2()
{
    int y;
    sem_wait(&s);
    y=shared;//thread2 reads value of shared variable
    printf("Thread2 reads the value as %d\n",y);
    y--; //thread2 decrements its value
    printf("Local updation by Thread2: %d\n",y);
    sleep(1); //thread2 is preempted by thread 1
    shared=y; //thread2 updates the value of shared variable
    printf("Value of shared variable updated by Thread2 is: %d\n",shared);
    sem_post(&s);
    return NULL;
}

/*
 * Compile: gcc q2.c -o q2 -lpthread
 * Thread2 is created while Thread1 still holds s, so Thread2 blocks in sem_wait()
 * until Thread1 posts. Thread2 therefore reads 2 (not the stale 1), and the final
 * value is 1 + 1 - 1 = 1. Without the semaphore, Thread2 would read 1, and the final
 * value would be 0 because Thread2 writes last.
 */

/*
 * Output (Linux):
 * Thread1 reads the value as 1
 * Local updation by Thread1: 2
 * Value of shared variable updated by Thread1 is: 2
 * Thread2 reads the value as 2
 * Local updation by Thread2: 1
 * Value of shared variable updated by Thread2 is: 1
 * Final value of shared is 1
 *
 * Note: run this on Linux. macOS does not implement unnamed POSIX semaphores (sem_init),
 * so there the semaphore doesn't block and the output is wrong.
 */

/*
 * Ex. No. 7 – Dining Philosopher Problem
 * Q1. Program: complete the code
 *
 * Hint from the code: room starts at 4, so at most 4 philosophers can try to pick up
 * chopsticks at once. This breaks circular wait and prevents deadlock. eat() is called
 * after philosopher() but defined below it, so add a prototype void eat(int); above
 * philosopher().
 *
 * ---- Background from the manual ----
 *
 * Aim: To write C programs that simulate solutions to the Dining Philosophers Problem.
 *
 * Description: The dining-philosophers problem is a classic synchronization problem
 * because it represents a large class of concurrency-control problems. It is a simple
 * model of allocating several resources among several processes without deadlock and
 * without starvation.
 *
 * Five philosophers spend their lives thinking and eating. They share a circular table
 * with five chairs, one per philosopher. In the center of the table is a bowl of rice, and
 * five single chopsticks are laid on the table. While a philosopher is thinking, she does
 * not interact with her colleagues. From time to time a philosopher gets hungry and tries
 * to pick up the two chopsticks closest to her, which are the ones between her and her
 * left and right neighbours. She can pick up only one chopstick at a time, and she cannot
 * pick up a chopstick that a neighbour is already holding. When a hungry philosopher holds
 * both chopsticks, she eats without releasing them. When she finishes eating, she puts
 * both chopsticks down and starts thinking again.
 *
 * The problem can lead to deadlock, so rules are needed to avoid it.
 *
 * *(Figure in PDF: round table with bowl in the center. Philosophers 0–4 sit around it,
 * with chopstick i between philosopher i and philosopher i-1.)*
 *
 * Source: OS_Lab_Manual.md, line 624
 */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t room;
sem_t chopstick[5];

void eat(int);

void * philosopher(void * num)
{
    int phil=*(int *)num;

    sem_wait(&room);                        /* at most 4 philosophers at the table */
    printf("\nPhilosopher %d has entered room",phil);
    sem_wait(&chopstick[phil]);             /* left chopstick */
    sem_wait(&chopstick[(phil+1)%5]);       /* right chopstick */

    eat(phil);
    sleep(2);
    printf("\nPhilosopher %d has finished eating",phil);

    sem_post(&chopstick[(phil+1)%5]);
    sem_post(&chopstick[phil]);
    sem_post(&room);
    return NULL;
}

void eat(int phil)
{
    printf("\nPhilosopher %d is eating",phil);
}

int main()
{
    int i,a[5];
    pthread_t tid[5];
    sem_init(&room,0,4);
    for(i=0;i<5;i++)
        sem_init(&chopstick[i],0,1);
    for(i=0;i<5;i++)
    {
        a[i]=i;
        pthread_create(&tid[i],NULL,philosopher,(void *)&a[i]);
    }
    for(i=0;i<5;i++)
        pthread_join(tid[i],NULL);
    printf("\n");
    return 0;
}

/*
 * Compile: gcc q1.c -o q1 -lpthread
 * Deadlock would need all 5 philosophers to each hold their left chopstick and wait
 * for the right one. The room semaphore (initial value 4) lets at most 4 sit down at
 * once, so at least one of them can always get both chopsticks, eat and release them.
 * Neighbours never eat at the same time because they share a chopstick.
 * Thread scheduling changes the order between runs.
 */

/*
 * Output (Linux, one possible run; the order varies with scheduling):
 * Philosopher 0 has entered room
 * Philosopher 0 is eating
 * Philosopher 1 has entered room
 * Philosopher 2 has entered room
 * Philosopher 2 is eating
 * Philosopher 3 has entered room
 * Philosopher 0 has finished eating
 * Philosopher 4 has entered room
 * Philosopher 4 is eating
 * Philosopher 2 has finished eating
 * Philosopher 1 is eating
 * Philosopher 4 has finished eating
 * Philosopher 1 has finished eating
 * Philosopher 3 is eating
 * Philosopher 3 has finished eating
 *
 * Philosopher 4 can't enter until a seat frees up (room = 4). Neighbours never eat at
 * the same time.
 * Note: run this on Linux. macOS does not implement sem_init.
 */

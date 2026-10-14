/*
 * Ex. No. 5 – Mutual Exclusion using Semaphore and Monitor
 * Q1. Execute and write the output of the following program for mutual exclusion using a System V semaphore
 *
 * Manual note: add #include <stdio.h> and #include <unistd.h> (for printf, fork and
 * sleep).
 *
 * ---- Background from the manual ----
 *
 * ## Semaphore
 *
 * A semaphore is used to implement process synchronization. It protects a critical region
 * that is shared among multiple processes.
 *
 * ## System V semaphore system calls
 *
 * Header files: <sys/ipc.h>, <sys/sem.h>, <sys/types.h>
 *
 * Create a semaphore array:
 *
 *     int semget(key_t key, int nsems, int semflg)
 *
 * - key: semaphore ID
 * - nsems: number of semaphores in the semaphore array
 * - semflg:
 * - IPC_CREAT|0664 creates a new semaphore.
 * - IPC_EXCL|IPC_CREAT|0664 creates a new semaphore, and the call fails if the semaphore
 * already exists.
 *
 * Operate on a semaphore set (allocate resources, wait for resources, free resources):
 *
 *     int semop(int semid, struct sembuf *semops, size_t nsemops)
 *
 * - semid: semaphore ID returned by semget()
 * - nsemops: number of operations in the array
 * - semops: pointer to the array of operations to perform on the semaphore set:
 *
 *     struct sembuf {
 *         unsigned short sem_num;  /* Semaphore set num * /
 *         short sem_op;            /* Semaphore operation * /
 *         short sem_flg;           /* Operation flags, IPC_NOWAIT, SEM_UNDO * /
 *     };
 *
 * sem_op sets the operation:
 *
 * - negative: allocates or obtains resources. The calling process blocks until other
 * processes free enough resources for it to allocate.
 * - zero: the calling process waits (sleeps) until the semaphore value reaches 0.
 * - positive: releases resources.
 *
 * Control operations on a semaphore:
 *
 *     int semctl(int semid, int semnum, int cmd, ...);
 *
 * - semid: semaphore identifier returned by semget()
 * - semnum: semaphore number
 * - cmd: command to perform on the semaphore, for example GETVAL or SETVAL
 * - semun: its value depends on cmd. Some commands don't use it.
 *
 * Source: OS_Lab_Manual.md, line 411
 */

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
int main()
{
    int pid,semid,val;
    struct sembuf sop;
    semid=semget((key_t)6,1,IPC_CREAT|0666);
    pid=fork();
    sop.sem_num=0;
    sop.sem_op=0;
    sop.sem_flg=0;
    if (pid!=0)
    {
        sleep(1);
        printf("The Parent waits for WAIT signal\n");
        semop(semid,&sop,1);
        printf("The Parent WAKED UP & doing her job\n");
        sleep(10);
        printf("Parent Over\n");
        semctl(semid,0,IPC_RMID);   /* remove the semaphore so the next run starts clean */
    }
    else
    {
        printf("The Child sets WAIT signal & doing her job\n");
        semctl(semid,0,SETVAL,1);
        sleep(10);
        printf("The Child sets WAKE signal & finished her job\n");
        semctl(semid,0,SETVAL,0);
        printf("Child Over\n");
    }
    return 0;
}

/*
 * Explanation:
 * The child sets the semaphore to 1 (WAIT) at once. The parent wakes after 1 s and
 * calls semop() with sem_op = 0, which blocks until the value becomes 0. The child
 * works for 10 s, then sets the value to 0 (WAKE), which unblocks the parent. The
 * parent then does its 10 s of work. Total run time is about 21 seconds.
 * "Child Over" and "The Parent WAKED UP ..." happen at the same moment, so on some
 * runs these two lines print in the opposite order.
 */

/*
 * Output (about 20 seconds in total):
 * The Child sets WAIT signal & doing her job
 * The Parent waits for WAIT signal
 * The Child sets WAKE signal & finished her job
 * Child Over
 * The Parent WAKED UP & doing her job
 * Parent Over
 */

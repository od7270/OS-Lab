/*
 * Ex. No. 8 – BANKER'S ALGORITHM – DEADLOCK AVOIDANCE
 * Q1. Write a program to simulate the Banker's algorithm
 *
 * ---- Background from the manual ----
 *
 * Aim: To simulate the Banker's algorithm for deadlock avoidance.
 *
 * Description: Deadlock is a situation in which two or more competing actions are each
 * waiting for the other to finish, so none of them ever does. When a new process enters
 * the system, it must declare the maximum number of instances of each resource type it may
 * need. This number may exceed the total number of resources in the system. When a user
 * requests a set of resources, the system must determine whether allocating them will
 * leave the system in a safe state. If it will, the resources are allocated. Otherwise the
 * process must wait until some other process releases resources.
 *
 * ## Data structures
 *
 * - n: number of processes
 * - m: number of resource types
 * - Available: Available[j] = k means k instances of resource type Rj are available.
 * - Max: Max[i][j] = k means Pi may request at most k instances of resource Rj.
 * - Allocation: Allocation[i][j] = k means Pi is currently allocated k instances of
 * resource Rj.
 * - Need: Need[i][j] = k means Pi may need k more instances of resource type Rj.
 * Need[i][j] = Max[i][j] - Allocation[i][j]
 *
 * ## Safety algorithm
 *
 * 1. Let Work and Finish be vectors of length m and n. Initialize Work = Available and
 * Finish[i] = False.
 * 2. Find an i such that Finish[i] == False and Need_i <= Work. If no such i exists, go to
 * step 4.
 * 3. Work = Work + Allocation_i, Finish[i] = True. Go to step 2.
 * 4. If Finish[i] == True for all i, the system is in a safe state.
 *
 * ## Resource-request algorithm
 *
 * Let Request_i be the request vector for process Pi. If Request_i[j] = k, process Pi
 * wants k instances of resource type Rj.
 *
 * 1. If Request_i <= Need_i, go to step 2. Otherwise raise an error condition (the process
 * has exceeded its maximum claim).
 * 2. If Request_i <= Available, go to step 3. Otherwise Pi must wait, because the
 * resources are not available.
 * 3. The system pretends to allocate the requested resources to Pi by changing the state
 * as follows:
 *        Available    = Available    - Request_i
 *        Allocation_i = Allocation_i + Request_i
 *        Need_i       = Need_i       - Request_i
 * If the resulting resource-allocation state is safe, the transaction completes and Pi
 * gets its resources. If the state is unsafe, Pi must wait for Request_i and the old
 * resource-allocation state is restored.
 *
 * ## Algorithm
 *
 * 1. Start the program.
 * 2. Get the values of resources and processes.
 * 3. Get the available values.
 * 4. After allocation, find the need values.
 * 5. Check whether allocation is possible.
 * 6. If it is possible, the system is in a safe state.
 * 7. Otherwise the system is not in a safe state.
 * 8. If a new request arrives, check whether the system stays safe
 * 9. if the request is granted.
 * 10. Stop the program.
 * 11. End.
 *
 * Source: OS_Lab_Manual.md, line 720
 */

#include <stdio.h>

int n,m;
int alloc[10][10],max[10][10],need[10][10],avail[10];

/* Safety algorithm: returns 1 and fills seq[] if the current state is safe. */
int is_safe(int seq[])
{
    int work[10],finish[10]={0},i,j,count=0,found;
    for(j=0;j<m;j++)
        work[j]=avail[j];
    while(count<n)
    {
        found=0;
        for(i=0;i<n;i++)
        {
            if(finish[i])
                continue;
            for(j=0;j<m;j++)
                if(need[i][j]>work[j])
                    break;
            if(j==m)        /* Need_i <= Work */
            {
                for(j=0;j<m;j++)
                    work[j]+=alloc[i][j];
                finish[i]=1;
                seq[count++]=i;
                found=1;
            }
        }
        if(!found)
            return 0;       /* no process can finish: unsafe */
    }
    return 1;
}

void print_state()
{
    int i,j;
    printf("\nProcess\tAllocation\tMax\t\tNeed\n");
    for(i=0;i<n;i++)
    {
        printf("P%d\t",i);
        for(j=0;j<m;j++) printf("%d ",alloc[i][j]);
        printf("\t\t");
        for(j=0;j<m;j++) printf("%d ",max[i][j]);
        printf("\t\t");
        for(j=0;j<m;j++) printf("%d ",need[i][j]);
        printf("\n");
    }
    printf("Available: ");
    for(j=0;j<m;j++) printf("%d ",avail[j]);
    printf("\n");
}

void report(int seq[])
{
    int i;
    if(is_safe(seq))
    {
        printf("System is in safe state.\nSafe sequence: ");
        for(i=0;i<n;i++)
            printf("P%d%s",seq[i],i<n-1?" -> ":"\n");
    }
    else
        printf("System is NOT in safe state.\n");
}

int main()
{
    int i,j,p,req[10],seq[10],ch;

    printf("Enter number of processes: ");
    scanf("%d",&n);
    printf("Enter number of resource types: ");
    scanf("%d",&m);
    printf("Enter Allocation matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&alloc[i][j]);
    printf("Enter Max matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&max[i][j]);
    printf("Enter Available resources:\n");
    for(j=0;j<m;j++)
        scanf("%d",&avail[j]);

    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            need[i][j]=max[i][j]-alloc[i][j];   /* Need = Max - Allocation */

    print_state();
    report(seq);

    /* Resource-request algorithm */
    printf("\nIs there a new request? (1 = yes, 0 = no): ");
    if(scanf("%d",&ch)!=1 || ch!=1)
        return 0;
    printf("Enter process number: ");
    scanf("%d",&p);
    printf("Enter request vector:\n");
    for(j=0;j<m;j++)
        scanf("%d",&req[j]);

    for(j=0;j<m;j++)
        if(req[j]>need[p][j])
        {
            printf("Error: P%d has exceeded its maximum claim.\n",p);
            return 0;
        }
    for(j=0;j<m;j++)
        if(req[j]>avail[j])
        {
            printf("Resources not available. P%d must wait.\n",p);
            return 0;
        }

    for(j=0;j<m;j++)        /* pretend to allocate */
    {
        avail[j]-=req[j];
        alloc[p][j]+=req[j];
        need[p][j]-=req[j];
    }
    if(is_safe(seq))
    {
        printf("Request can be granted. New state:\n");
        print_state();
        report(seq);
    }
    else
    {
        for(j=0;j<m;j++)    /* restore the old state */
        {
            avail[j]+=req[j];
            alloc[p][j]-=req[j];
            need[p][j]+=req[j];
        }
        printf("Request would leave the system unsafe. P%d must wait; old state restored.\n",p);
    }
    return 0;
}

/*
 * Output (textbook example: 5 processes, 3 resource types A B C):
 * Enter number of processes: 5
 * Enter number of resource types: 3
 * Enter Allocation matrix:
 * 0 1 0
 * 2 0 0
 * 3 0 2
 * 2 1 1
 * 0 0 2
 * Enter Max matrix:
 * 7 5 3
 * 3 2 2
 * 9 0 2
 * 2 2 2
 * 4 3 3
 * Enter Available resources:
 * 3 3 2
 *
 * Process Allocation      Max             Need
 * P0      0 1 0           7 5 3           7 4 3
 * P1      2 0 0           3 2 2           1 2 2
 * P2      3 0 2           9 0 2           6 0 0
 * P3      2 1 1           2 2 2           0 1 1
 * P4      0 0 2           4 3 3           4 3 1
 * Available: 3 3 2
 * System is in safe state.
 * Safe sequence: P1 -> P3 -> P4 -> P0 -> P2
 *
 * Is there a new request? (1 = yes, 0 = no): 1
 * Enter process number: 1
 * Enter request vector:
 * 1 0 2
 * Request can be granted. New state:
 *
 * Process Allocation      Max             Need
 * P0      0 1 0           7 5 3           7 4 3
 * P1      3 0 2           3 2 2           0 2 0
 * P2      3 0 2           9 0 2           6 0 0
 * P3      2 1 1           2 2 2           0 1 1
 * P4      0 0 2           4 3 3           4 3 1
 * Available: 2 3 0
 * System is in safe state.
 * Safe sequence: P1 -> P3 -> P4 -> P0 -> P2
 */

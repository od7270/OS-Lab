/*
 * Ex. No. 15 – FILE ORGANIZATION SCHEMES FOR SINGLE-LEVEL AND TWO-LEVEL DIRECTORY
 * Q1. A) Single-level directory
 *
 * Aim: A program to simulate the single-level directory file organization technique.
 *
 * Description: A directory structure organizes files into a hierarchy of folders. In a
 * single-level directory system, all files are in one directory: a root directory that
 * holds every file, with no subdirectories. The structure is simple, and its advantage is
 * that finding a file in the directory is easy.
 *
 * Source code (skeleton):
 *
 * Source: OS_Lab_Manual.md, line 986
 */

#include<stdio.h>
#include<string.h>

struct
{
    char dname[10],fname[10][10];
    int fcnt;
}dir;

int main()
{
    int i,ch;
    char f[30];

    dir.fcnt=0;
    printf("Enter name of directory: ");
    scanf("%9s",dir.dname);

    while(1)
    {
        printf("\n1. Create File\t2. Delete File\t3. Search File\n4. Display Files\t5. Exit\nEnter your choice: ");
        if(scanf("%d",&ch)!=1)
            break;
        switch(ch)
        {
        case 1:
            if(dir.fcnt==10)
            {
                printf("Directory is full\n");
                break;
            }
            printf("Enter the name of the file: ");
            scanf("%9s",f);
            for(i=0;i<dir.fcnt;i++)
                if(strcmp(f,dir.fname[i])==0)
                    break;
            if(i<dir.fcnt)
                printf("File %s already exists\n",f);
            else
            {
                strcpy(dir.fname[dir.fcnt],f);
                dir.fcnt++;
                printf("File %s created\n",f);
            }
            break;
        case 2:
            printf("Enter the name of the file: ");
            scanf("%29s",f);
            for(i=0;i<dir.fcnt;i++)
                if(strcmp(f,dir.fname[i])==0)
                    break;
            if(i<dir.fcnt)
            {
                printf("File %s is deleted\n",f);
                strcpy(dir.fname[i],dir.fname[dir.fcnt-1]);    /* move last file into the gap */
                dir.fcnt--;
            }
            else
                printf("File %s not found\n",f);
            break;
        case 3:
            printf("Enter the name of the file: ");
            scanf("%29s",f);
            for(i=0;i<dir.fcnt;i++)
                if(strcmp(f,dir.fname[i])==0)
                    break;
            if(i<dir.fcnt)
                printf("File %s is found\n",f);
            else
                printf("File %s not found\n",f);
            break;
        case 4:
            if(dir.fcnt==0)
                printf("Directory is empty\n");
            else
            {
                printf("The files in directory %s are:\n",dir.dname);
                for(i=0;i<dir.fcnt;i++)
                    printf("\t%s\n",dir.fname[i]);
            }
            break;
        default:
            return 0;
        }
    }
    return 0;
}

/*
 * Output:
 * Enter name of directory: CSE
 * 1. Create File  2. Delete File  3. Search File
 * 4. Display Files        5. Exit
 * Enter your choice: 1
 * Enter the name of the file: a.c
 * File a.c created
 * Enter your choice: 1
 * Enter the name of the file: b.txt
 * File b.txt created
 * Enter your choice: 1
 * Enter the name of the file: os.pdf
 * File os.pdf created
 * Enter your choice: 1
 * Enter the name of the file: a.c
 * File a.c already exists
 * Enter your choice: 4
 * The files in directory CSE are:
 *         a.c
 *         b.txt
 *         os.pdf
 * Enter your choice: 3
 * Enter the name of the file: b.txt
 * File b.txt is found
 * Enter your choice: 3
 * Enter the name of the file: x.c
 * File x.c not found
 * Enter your choice: 2
 * Enter the name of the file: b.txt
 * File b.txt is deleted
 * Enter your choice: 4
 * The files in directory CSE are:
 *         a.c
 *         os.pdf
 * Enter your choice: 5
 * (the menu is printed before every "Enter your choice"; repeats omitted)
 *
 * Every file is in the one directory, so file names must be unique. A second a.c is rejected.
 */

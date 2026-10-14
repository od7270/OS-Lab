/*
 * Ex. No. 15 – FILE ORGANIZATION SCHEMES FOR SINGLE-LEVEL AND TWO-LEVEL DIRECTORY
 * Q2. B) Two-level directory
 *
 * Aim: A program to simulate the two-level directory file organization technique.
 *
 * Description: In a two-level directory system, each user has their own user file
 * directory (UFD). The system keeps a master block with one entry per user, and that
 * master block holds the addresses of the users' directories. When a user job starts or a
 * user logs in, the system's master file directory (MFD) is searched. When a user refers
 * to a particular file, only that user's own UFD is searched.
 *
 * Source code (skeleton):
 *
 * Manual note: after this skeleton, page 47 of the PDF shows leftover fragments of a menu-
 * driven program: } } break; default:exit(0));; } } getch(); }. The full program is meant
 * to be a switch menu (create directory, create file, delete file, search file, display,
 * exit) that uses exit() and getch(). getch() comes from <conio.h> and isn't available on
 * Linux, so use getchar() instead. Include <stdlib.h> for exit() and <string.h> for
 * strcmp/strcpy.
 *
 * Source: OS_Lab_Manual.md, line 1008
 */

#include<stdio.h>
#include<string.h>

struct
{
    char dname[10],fname[10][10];
    int fcnt;
}dir[10];

/* Master file directory lookup: returns the user's directory index or -1 */
int find_dir(char *d,int dcnt)
{
    int i;
    for(i=0;i<dcnt;i++)
        if(strcmp(d,dir[i].dname)==0)
            return i;
    return -1;
}

/* User file directory lookup: only this user's files are searched */
int find_file(int k,char *f)
{
    int i;
    for(i=0;i<dir[k].fcnt;i++)
        if(strcmp(f,dir[k].fname[i])==0)
            return i;
    return -1;
}

int main()
{
    int i,j,k,ch,dcnt=0;
    char f[30],d[30];

    while(1)
    {
        printf("\n1. Create Directory\t2. Create File\t3. Delete File\n4. Search File\t\t5. Display\t6. Exit\nEnter your choice: ");
        if(scanf("%d",&ch)!=1)
            break;
        switch(ch)
        {
        case 1:
            if(dcnt==10)
            {
                printf("Maximum number of directories reached\n");
                break;
            }
            printf("Enter name of directory: ");
            scanf("%9s",d);
            if(find_dir(d,dcnt)!=-1)
            {
                printf("Directory %s already exists\n",d);
                break;
            }
            strcpy(dir[dcnt].dname,d);
            dir[dcnt].fcnt=0;
            dcnt++;
            printf("Directory %s created\n",d);
            break;
        case 2:
            printf("Enter name of the directory: ");
            scanf("%29s",d);
            k=find_dir(d,dcnt);
            if(k==-1)
            {
                printf("Directory %s not found\n",d);
                break;
            }
            if(dir[k].fcnt==10)
            {
                printf("Directory %s is full\n",d);
                break;
            }
            printf("Enter name of the file: ");
            scanf("%9s",f);
            if(find_file(k,f)!=-1)
            {
                printf("File %s already exists in %s\n",f,d);
                break;
            }
            strcpy(dir[k].fname[dir[k].fcnt],f);
            dir[k].fcnt++;
            printf("File %s created in %s\n",f,d);
            break;
        case 3:
            printf("Enter name of the directory: ");
            scanf("%29s",d);
            k=find_dir(d,dcnt);
            if(k==-1)
            {
                printf("Directory %s not found\n",d);
                break;
            }
            printf("Enter name of the file: ");
            scanf("%29s",f);
            i=find_file(k,f);
            if(i==-1)
            {
                printf("File %s not found in %s\n",f,d);
                break;
            }
            dir[k].fcnt--;
            strcpy(dir[k].fname[i],dir[k].fname[dir[k].fcnt]);
            printf("File %s is deleted from %s\n",f,d);
            break;
        case 4:
            printf("Enter name of the directory: ");
            scanf("%29s",d);
            k=find_dir(d,dcnt);
            if(k==-1)
            {
                printf("Directory %s not found\n",d);
                break;
            }
            printf("Enter name of the file: ");
            scanf("%29s",f);
            if(find_file(k,f)!=-1)
                printf("File %s is found in %s\n",f,d);
            else
                printf("File %s not found in %s\n",f,d);
            break;
        case 5:
            if(dcnt==0)
            {
                printf("No directories\n");
                break;
            }
            printf("\nDirectory\tFiles\n");
            for(i=0;i<dcnt;i++)
            {
                printf("%s\t\t",dir[i].dname);
                for(j=0;j<dir[i].fcnt;j++)
                    printf("%s ",dir[i].fname[j]);
                printf("\n");
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
 * 1. Create Directory     2. Create File  3. Delete File
 * 4. Search File          5. Display      6. Exit
 * Enter your choice: 1
 * Enter name of directory: user1
 * Directory user1 created
 * Enter your choice: 1
 * Enter name of directory: user2
 * Directory user2 created
 * Enter your choice: 2
 * Enter name of the directory: user1
 * Enter name of the file: a.c
 * File a.c created in user1
 * Enter your choice: 2
 * Enter name of the directory: user1
 * Enter name of the file: b.c
 * File b.c created in user1
 * Enter your choice: 2
 * Enter name of the directory: user2
 * Enter name of the file: a.c
 * File a.c created in user2
 * Enter your choice: 2
 * Enter name of the directory: user3
 * Directory user3 not found
 * Enter your choice: 5
 *
 * Directory       Files
 * user1           a.c b.c
 * user2           a.c
 * Enter your choice: 4
 * Enter name of the directory: user2
 * Enter name of the file: a.c
 * File a.c is found in user2
 * Enter your choice: 4
 * Enter name of the directory: user2
 * Enter name of the file: b.c
 * File b.c not found in user2
 * Enter your choice: 3
 * Enter name of the directory: user1
 * Enter name of the file: a.c
 * File a.c is deleted from user1
 * Enter your choice: 5
 *
 * Directory       Files
 * user1           b.c
 * user2           a.c
 * Enter your choice: 6
 * (the menu is printed before every "Enter your choice"; repeats omitted)
 *
 * The MFD (dir[]) is searched for the user's directory, then only that user's UFD is
 * searched. That is why user1 and user2 can both have a file named a.c, and why searching
 * user2 for b.c fails even though b.c exists in user1.
 */

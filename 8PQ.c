// Implement a Priority Queue using Heap Data Structure
// and apply it to Job Scheduling Applications.
//
// • Implement insertion and deletion operations
// • Construct Max Heap
// • Simulate job scheduling based on priorities
// • Display execution order of jobs

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Job
{ 
    int id;
    int priority;
};

struct Job heap[MAX];
int size=0;

void swap(struct Job *a,struct Job *b)
{
    struct Job temp=*a;
    *a=*b;
    *b=temp;
}

void insertJob(int id,int priority)
{
    if(size==MAX)
    {
        printf("Priority Queue is Full\n");
        return;
    }

    int i=size;

    heap[i].id=id;
    heap[i].priority=priority;

    size++;

    while(i!=0 && heap[(i-1)/2].priority<heap[i].priority)
    {
        swap(&heap[i],&heap[(i-1)/2]);
        i=(i-1)/2;
    }

    printf("Job Inserted Successfully\n");
}

void heapify(int i)
{
    int largest=i;
    int left=2*i+1;
    int right=2*i+2;

    if(left<size && heap[left].priority>heap[largest].priority)
    {
        largest=left;
    }

    if(right<size && heap[right].priority>heap[largest].priority)
    {
        largest=right;
    }

    if(largest!=i)
    {
        swap(&heap[i],&heap[largest]);
        heapify(largest);
    }
}

void deleteJob()
{
    if(size<=0)
    {
        printf("Priority Queue is Empty\n");
        return;
    }

    printf("Executed Job ID: %d\n",heap[0].id);
    printf("Priority: %d\n",heap[0].priority);

    heap[0]=heap[size-1];   

    size--;

    heapify(0);
}

void display()
{
    if(size==0)
    {
        printf("No Jobs Available\n");
        return;
    }

    printf("\nJobs in Priority Queue:\n");

    for(int i=0;i<size;i++)
    {
        printf("Job ID: %d  Priority: %d\n",
               heap[i].id,
               heap[i].priority);
    }
}

void executeAllJobs()
{
    if(size==0)
    {
        printf("No Jobs to Execute\n");
        return;
    }

    printf("\nExecution Order of Jobs:\n");

    while(size>0)
    {
        printf("Job ID: %d executed with Priority: %d\n",
               heap[0].id,
               heap[0].priority);

        heap[0]=heap[size-1];

        size--;

        heapify(0);
    }
}

int main()
{
    int choice;
    int id,priority;

    while(1)
    {
        printf("\n===== PRIORITY QUEUE USING HEAP =====\n");

        printf("1. Insert Job\n");
        printf("2. Delete Highest Priority Job\n");
        printf("3. Display Jobs\n");
        printf("4. Execute All Jobs\n");
        printf("5. Exit\n");

        printf("Enter Your Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                printf("Enter Job ID: ");
                scanf("%d",&id);

                printf("Enter Priority: ");
                scanf("%d",&priority);

                insertJob(id,priority);

                break;

            case 2:
                deleteJob();
                break;

            case 3:
                display();
                break;

            case 4:
                executeAllJobs();
                break;

            case 5:
                printf("Program Exited\n");
                exit(0);

            default:
                printf("Invalid Choice\n");
        }
    }

    return 0;
}

/*
Input:
1
101
5

Output:
Job Inserted Successfully
*/
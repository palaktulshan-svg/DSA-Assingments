#include <stdio.h>
#include <string.h>

struct PrintJob
{
    int jobId;
    char title[50];
};

void addPrintJob(struct PrintJob queue[], int *front, int *rear, int size)
{
    struct PrintJob job;

    if (*rear == size - 1)
    {
        printf("\nQueue is FULL! Cannot add more print jobs.\n");
        return;
    }

    printf("\nEnter Job ID: ");
    scanf("%d", &job.jobId);

    printf("Enter Document Title: ");
    scanf(" %[^\n]", job.title);

    if (*front == -1)
    {
        *front = 0;
    }

    (*rear)++;
    queue[*rear] = job;

    printf("\nPrint job added successfully!\n");
}

void deletePrintJob(struct PrintJob queue[], int *front, int *rear)
{
    if (*front == -1 || *front > *rear)
    {
        printf("\nQueue is EMPTY! No print job to delete.\n");
        return;
    }

    printf("\nDeleted Print Job:\n");
    printf("Job ID: %d\n", queue[*front].jobId);
    printf("Document Title: %s\n", queue[*front].title);

    (*front)++;

    if (*front > *rear)
    {
        *front = -1;
        *rear = -1;
    }
}

void displayPrintJobs(struct PrintJob queue[], int front, int rear)
{
    int i;

    if (front == -1)
    {
        printf("\nQueue is EMPTY!\n");
        return;
    }

    printf("\n----- PRINT JOBS IN QUEUE -----\n");

    for (i = front; i <= rear; i++)
    {
        printf("\nJob ID: %d", queue[i].jobId);
        printf("\nDocument Title: %s\n", queue[i].title);
    }
}

int main()
{
    struct PrintJob queue[5];

    int front = -1;
    int rear = -1;
    int choice;
    int size = 5;

    do
    {
        printf("\n\n===== SHARED PRINTER MANAGEMENT =====");
        printf("\n1. Add Print Job");
        printf("\n2. Delete Print Job");
        printf("\n3. Display Print Jobs");
        printf("\n4. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addPrintJob(queue, &front, &rear, size);
                break;

            case 2:
                deletePrintJob(queue, &front, &rear);
                break;

            case 3:
                displayPrintJobs(queue, front, rear);
                break;

            case 4:
                printf("\nExiting program...\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while (choice != 4);

    return 0;
}
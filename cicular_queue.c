#include <stdio.h>

struct PrintJob
{
    int jobId;
    char title[50];
};

int isEmpty(int front)
{
    if (front == -1)
    {
        return 1;
    }

    return 0;
}

int isFull(int front, int rear, int size)
{
    if ((front == 0 && rear == size - 1) ||
        ((rear + 1) % size == front))
    {
        return 1;
    }

    return 0;
}

int addPrintJob(struct PrintJob queue[],
                int *front,
                int *rear,
                int size,
                int jobId,
                char title[])
{
    struct PrintJob job;

    if (isFull(*front, *rear, size))
    {
        return 0;
    }

    job.jobId = jobId;

    int i = 0;

    while (title[i] != '\0')
    {
        job.title[i] = title[i];
        i++;
    }

    job.title[i] = '\0';

    if (*front == -1)
    {
        *front = 0;
        *rear = 0;
    }
    else
    {
        *rear = (*rear + 1) % size;
    }

    queue[*rear] = job;

    return 1;
}

int deletePrintJob(struct PrintJob queue[],
                   int *front,
                   int *rear,
                   int size,
                   struct PrintJob *deletedJob)
{
    if (isEmpty(*front))
    {
        return 0;
    }
    *deletedJob = queue[*front];

    if (*front == *rear)
    {
        *front = -1;
        *rear = -1;
    }
    else
    {
        *front = (*front + 1) % size;
    }

    return 1;
}

int displayPrintJobs(struct PrintJob queue[],
                     int front,
                     int rear,
                     int size,
                     int displayIndex[])
{
    int i;
    int count = 0;

    if (front == -1)
    {
        return 0;
    }

    i = front;

    while (1)
    {
        displayIndex[count] = i;
        count++;

        if (i == rear)
        {
            break;
        }

        i = (i + 1) % size;
    }

    return count;
}

int main()
{
    struct PrintJob queue[5];

    struct PrintJob deletedJob;

    int front = -1;
    int rear = -1;
    int size = 5;

    int choice;
    int result;

    int jobId;
    char title[50];

    int displayIndex[5];
    int count;
    int i;

    do
    {
        printf("\n\n===== CIRCULAR PRINTER QUEUE =====");
        printf("\n1. Add Print Job");
        printf("\n2. Delete Print Job");
        printf("\n3. Display Print Jobs");
        printf("\n4. Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:

            if (isFull(front, rear, size))
            {
                printf("\nQueue is FULL!\n");
            }
            else
            {
                printf("\nEnter Job ID: ");
                scanf("%d", &jobId);

                printf("Enter Document Title: ");
                scanf(" %49[^\n]", title);

                result = addPrintJob(
                    queue,
                    &front,
                    &rear,
                    size,
                    jobId,
                    title);

                if (result == 1)
                {
                    printf("\nPrint Job Added Successfully!\n");
                }
            }

            break;

        case 2:

            if (isEmpty(front))
            {
                printf("\nQueue is EMPTY!\n");
            }
            else
            {
                result = deletePrintJob(
                    queue,
                    &front,
                    &rear,
                    size,
                    &deletedJob);

                if (result == 1)
                {
                    printf("\nDeleted Print Job:\n");
                    printf("Job ID: %d\n", deletedJob.jobId);
                    printf("Document Title: %s\n",
                           deletedJob.title);
                }
            }

            break;

        case 3:

            if (isEmpty(front))
            {
                printf("\nQueue is EMPTY!\n");
            }
            else
            {
                count = displayPrintJobs(
                    queue,
                    front,
                    rear,
                    size,
                    displayIndex);

                printf("\n----- PRINT JOBS IN QUEUE -----\n");

                for (i = 0; i < count; i++)
                {
                    printf("\nJob ID: %d",
                           queue[displayIndex[i]].jobId);

                    printf("\nDocument Title: %s\n",
                           queue[displayIndex[i]].title);
                }
            }

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

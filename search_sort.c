#include <stdio.h>
#include <string.h>

struct Employee
{
    int empId;
    char name[50];
    float salary;
};

// Function to accept employee details
void accept(struct Employee emp[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("\nEnter employee Details (%d of %d):\n", i + 1, n);

        printf("Enter the name: ");
        scanf(" %49[^\n]", emp[i].name);

        printf("Enter the employee ID: ");
        scanf("%d", &emp[i].empId);

        printf("Enter the salary of Employee: ");
        scanf("%f", &emp[i].salary);
    }
}

// Function to display employee details
void display(struct Employee emp[], int n)
{
    int i;
    printf("\n------ Employee Database ------\n");
    printf("ID\tName\t\tSalary\n");
    printf("-------------------------------\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%s\t\t%.2f\n",
               emp[i].empId,
               emp[i].name,
               emp[i].salary);
    }
}

// ==================== SEARCH FUNCTIONS ====================

// Linear Search by Employee ID
int linearSearch(struct Employee emp[], int n, int searchId)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (emp[i].empId == searchId)
        {
            return i;
        }
    }
    return -1;
}

// Linear Search by Employee Name
int linearSearchByName(struct Employee emp[], int n, char searchName[])
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (strcmp(emp[i].name, searchName) == 0)
        {
            return i;
        }
    }
    return -1;
}

// Binary Search by Employee ID
int binarySearch(struct Employee emp[], int n, int searchId)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (emp[mid].empId == searchId)
        {
            return mid;
        }
        if (emp[mid].empId < searchId)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}

// ==================== SORT FUNCTIONS ====================

// Bubble Sort by salary in ascending order
void bubbleSortAscending(struct Employee emp[], int n)
{
    int i, j;
    struct Employee temp;

    for (j = 0; j < n - 1; j++)
    {
        for (i = 0; i < n - j - 1; i++)
        {
            if (emp[i].salary > emp[i + 1].salary)
            {
                temp = emp[i];
                emp[i] = emp[i + 1];
                emp[i + 1] = temp;
            }
        }
    }
}

// Bubble Sort by salary in descending order
void bubbleSortDescending(struct Employee emp[], int n)
{
    int i, j;
    struct Employee temp;

    for (j = 0; j < n - 1; j++)
    {
        for (i = 0; i < n - j - 1; i++)
        {
            if (emp[i].salary < emp[i + 1].salary)
            {
                temp = emp[i];
                emp[i] = emp[i + 1];
                emp[i + 1] = temp;
            }
        }
    }
}

// Selection Sort by Employee ID
void selectionSortById(struct Employee emp[], int n)
{
    int i, j, minIndex;
    struct Employee temp;

    for (i = 0; i < n - 1; i++)
    {
        minIndex = i;

        for (j = i + 1; j < n; j++)
        {
            if (emp[j].empId < emp[minIndex].empId)
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            temp = emp[i];
            emp[i] = emp[minIndex];
            emp[minIndex] = temp;
        }
    }
}

// Insertion Sort by Employee ID
void insertionSortById(struct Employee emp[], int n)
{
    int i, j;
    struct Employee key;

    for (i = 1; i < n; i++)
    {
        key = emp[i];
        j = i - 1;

        while (j >= 0 && emp[j].empId > key.empId)
        {
            emp[j + 1] = emp[j];
            j--;
        }

        emp[j + 1] = key;
    }
}

// Shell Sort by Employee ID 
void shellSortById(struct Employee emp[], int n)
{
    int gap, i, j;
    struct Employee temp;

    for (gap = n / 2; gap > 0; gap = gap / 2)
    {
        for (i = gap; i < n; i++)
        {
            for (j = i; j >= gap; j = j - gap)
            {
                if (emp[j - gap].empId > emp[j].empId)
                {

                    temp = emp[j];
                    emp[j] = emp[j - gap];
                    emp[j - gap] = temp;
                }
                else
                {

                    break;
                }
            }
        }
    }
}


int main()
{
    struct Employee emp[100];
    int n = 0, choice, searchId, result;
    char searchName[50];

    do
    {
        printf("\n=====================================\n");
        printf("       EMPLOYEE MANAGEMENT           \n");
        printf("=====================================\n");
        printf("1. Accept Employee Details\n");
        printf("2. Display Employee Database\n");
        printf("--- SEARCH OPERATIONS ---\n");
        printf("3. Linear Search by Employee ID\n");
        printf("4. Linear Search by Employee Name\n");
        printf("5. Binary Search by Employee ID\n");
        printf("--- SORT OPERATIONS ---\n");
        printf("6. Bubble Sort by Salary (Ascending)\n");
        printf("7. Bubble Sort by Salary (Descending)\n");
        printf("8. Selection Sort by Employee ID\n");
        printf("9. Insertion Sort by Employee ID\n");
        printf("10. Shell Sort by Employee ID\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter number of employees: ");
            scanf("%d", &n);

            if (n > 100 || n <= 0)
            {
                printf("Invalid number of employees!\n");
                n = 0;
            }
            else
            {
                accept(emp, n);
            }
            break;

        case 2:
            if (n == 0)
                printf("\nDatabase is empty!\n");
            else
                display(emp, n);
            break;

         

        case 3: // Linear Search by ID
            if (n == 0)
            {
                printf("\nDatabase is empty!\n");
            }
            else
            {
                printf("Enter Employee ID: ");
                scanf("%d", &searchId);

                result = linearSearch(emp, n, searchId);

                if (result != -1)
                {
                    printf("\nEmployee Found!\n");
                    printf("ID: %d\n", emp[result].empId);
                    printf("Name: %s\n", emp[result].name);
                    printf("Salary: %.2f\n", emp[result].salary);
                }
                else
                {
                    printf("Employee not found.\n");
                }
            }
            break;

        case 4: 
            if (n == 0)
            {
                printf("\nDatabase is empty!\n");
            }
            else
            {
                printf("Enter Employee Name: ");
                scanf(" %49[^\n]", searchName);

                result = linearSearchByName(emp, n, searchName);

                if (result != -1)
                {
                    printf("\nEmployee Found!\n");
                    printf("ID: %d\n", emp[result].empId);
                    printf("Name: %s\n", emp[result].name);
                    printf("Salary: %.2f\n", emp[result].salary);
                }
                else
                {
                    printf("Employee not found.\n");
                }
            }
            break;

        case 5: 
            if (n == 0)
            {
                printf("\nDatabase is empty!\n");
            }
            else
            {
                selectionSortById(emp, n); 

                printf("Enter Employee ID: ");
                scanf("%d", &searchId);

                result = binarySearch(emp, n, searchId);

                if (result != -1)
                {
                    printf("\nEmployee Found!\n");
                    printf("ID: %d\n", emp[result].empId);
                    printf("Name: %s\n", emp[result].name);
                    printf("Salary: %.2f\n", emp[result].salary);
                }
                else
                {
                    printf("Employee not found.\n");
                }
            }
            break;

           

        case 6: // Bubble Sort Salary (Ascending)
            if (n == 0)
                printf("\nDatabase is empty!\n");
            else
            {
                bubbleSortAscending(emp, n);
                printf("\nEmployees sorted in Ascending Salary.\n");
                display(emp, n);
            }
            break;

        case 7: 
            if (n == 0)
                printf("\nDatabase is empty!\n");
            else
            {
                bubbleSortDescending(emp, n);
                printf("\nEmployees sorted in Descending Salary.\n");
                display(emp, n);
            }
            break;

        case 8: 
            if (n == 0)
                printf("\nDatabase is empty!\n");
            else
            {
                selectionSortById(emp, n);
                printf("\nEmployees sorted by Employee ID using Selection Sort.\n");
                display(emp, n);
            }
            break;

        case 9: 
            if (n == 0)
                printf("\nDatabase is empty!\n");
            else
            {
                insertionSortById(emp, n);
                printf("\nEmployees sorted by Employee ID using Insertion Sort.\n");
                display(emp, n);
            }
            break;

        case 10: 
            if (n == 0)

            {
                printf("\nDatabase is empty!\n");
            }
            else
            {
                shellSortById(emp, n);
                printf("\nEmployees sorted by Employee ID using Shell Sort.\n");
                display(emp, n);
            }
            break;

        case 11:
            printf("\nThank you! Exiting the program...\n");
            break;

        default:
            printf("\nInvalid choice! Please try again.\n");
            break;
        }

    } while (choice != 11);

    return 0;
}
#include <stdio.h>
#define MAX 100

// Accept Matrix
void acceptMatrix(int a[20][20], int r, int c)
{
    int i, j;
    for(i = 0; i < r; i++)
        for(j = 0; j < c; j++)
            scanf("%d", &a[i][j]);
}

// Display Matrix
void displayMatrix(int a[20][20], int r, int c)
{
    int i, j;
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
            printf("%d\t", a[i][j]);
        printf("\n");
    }
}

// Convert into Compact Form
void CompactForm(int a[20][20], int row, int col, int Compact[20][3])
{
    int i, j, k = 1;

    Compact[0][0] = row;
    Compact[0][1] = col;
    Compact[0][2] = 0;

    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            if(a[i][j] != 0)
            {
                Compact[k][0] = i;
                Compact[k][1] = j;
                Compact[k][2] = a[i][j];
                k++;
                Compact[0][2]++;
            }
        }
    }
}

// Display Compact Matrix
void displayCompact(int Compact[20][3])
{
    int i;

    printf("Row\tCol\tValue\n");
    printf("----------------------\n");

    for(i = 0; i <= Compact[0][2]; i++)
    {
        printf("%d\t%d\t%d\n",
               Compact[i][0],
               Compact[i][1],
               Compact[i][2]);
    }
}

// Simple Transpose
void simpleTranspose(int Compact[20][3], int trans[20][3])
{
    int i, j, k = 1;

    trans[0][0] = Compact[0][1];
    trans[0][1] = Compact[0][0];
    trans[0][2] = Compact[0][2];

    for(i = 0; i < Compact[0][1]; i++)
    {
        for(j = 1; j <= Compact[0][2]; j++)
        {
            if(Compact[j][1] == i)
            {
                trans[k][0] = Compact[j][1];
                trans[k][1] = Compact[j][0];
                trans[k][2] = Compact[j][2];
                k++;
            }
        }
    }
}

// Fast Transpose
void fastTranspose(int Compact[20][3], int fast[20][3])
{
    int rowTerms[20], startPos[20];
    int i, j, numCols, numTerms;

    numCols = Compact[0][1];
    numTerms = Compact[0][2];

    fast[0][0] = Compact[0][1];
    fast[0][1] = Compact[0][0];
    fast[0][2] = numTerms;

    // Initialize rowTerms
    for(i = 0; i < numCols; i++)
        rowTerms[i] = 0;

    // Count number of elements in each column
    for(i = 1; i <= numTerms; i++)
        rowTerms[Compact[i][1]]++;

    // Calculate starting positions
    startPos[0] = 1;
    for(i = 1; i < numCols; i++)
        startPos[i] = startPos[i - 1] + rowTerms[i - 1];

    // Perform fast transpose
    for(i = 1; i <= numTerms; i++)
    {
        j = startPos[Compact[i][1]];

        fast[j][0] = Compact[i][1];
        fast[j][1] = Compact[i][0];
        fast[j][2] = Compact[i][2];

        startPos[Compact[i][1]]++;
    }
}

//addition of matrix(compact form)
void addCompact(int c1[100][3], int c2[100][3], int sum[100][3])
{
    int i=1;
    int j=1;
    int k=1;

    if(c1[0][0]!=c2[0][0] || c1[0][1]!=c2[0][1])
    {
        printf("Addition not possible.\n");
        return;
    }

    sum[0][0]=c1[0][0];
    sum[0][1]=c1[0][1];
    sum[0][2]=0;

    while(i<=c1[0][2] && j<=c2[0][2])
    {
        if(c1[i][0]==c2[j][0] && c1[i][1]==c2[j][1])
        {
            sum[k][0]=c1[i][0];
            sum[k][1]=c1[i][1];
            sum[k][2]=c1[i][2]+c2[j][2];

            i++;
            j++;
            k++;
            sum[0][2]++;
        }

        else if(c1[i][0]<c2[j][0] ||
               (c1[i][0]==c2[j][0] && c1[i][1]<c2[j][1]))
        {
            sum[k][0]=c1[i][0];
            sum[k][1]=c1[i][1];
            sum[k][2]=c1[i][2];

            i++;
            k++;
            sum[0][2]++;
        }

        else
        {
            sum[k][0]=c2[j][0];
            sum[k][1]=c2[j][1];
            sum[k][2]=c2[j][2];

            j++;
            k++;
            sum[0][2]++;
        }
    }

    while(i<=c1[0][2])
    {
        sum[k][0]=c1[i][0];
        sum[k][1]=c1[i][1];
        sum[k][2]=c1[i][2];

        i++;
        k++;
        sum[0][2]++;
    }

    while(j<=c2[0][2])
    {
        sum[k][0]=c2[j][0];
        sum[k][1]=c2[j][1];
        sum[k][2]=c2[j][2];

        j++;
        k++;
        sum[0][2]++;
    }
}

int main()
{
    int a[20][20], b[20][20];
    int Compact1[100][3], Compact2[100][3];
    int sum[100][3];
    int trans[100][3];
    int fast[100][3];

    int row1, col1, row2, col2;
    int choice;

    int m1 = 0, m2 = 0;

    do
    {
        printf("\n====================================\n");
        printf("        SPARSE MATRIX MENU\n");
        printf("====================================\n");
        printf("1. Enter Matrix 1\n");
        printf("2. Enter Matrix 2\n");
        printf("3. Display Matrix 1\n");
        printf("4. Display Matrix 2\n");
        printf("5. Display Compact Form of Matrix 1\n");
        printf("6. Display Compact Form of Matrix 2\n");
        printf("7. Addition of Sparse Matrices\n");
        printf("8. Simple Transpose (Matrix 1)\n");
        printf("9. Fast Transpose (Matrix 1)\n");
        printf("10. Exit\n");

        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:

                printf("Enter rows and columns of Matrix 1: ");
                scanf("%d%d",&row1,&col1);

                printf("Enter Matrix 1:\n");
                acceptMatrix(a,row1,col1);

                CompactForm(a,row1,col1,Compact1);

                m1=1;

                break;

            case 2:

                printf("Enter rows and columns of Matrix 2: ");
                scanf("%d%d",&row2,&col2);

                printf("Enter Matrix 2:\n");
                acceptMatrix(b,row2,col2);

                CompactForm(b,row2,col2,Compact2);

                m2=1;

                break;

            case 3:

                if(m1)
                {
                    printf("\nMatrix 1:\n");
                    displayMatrix(a,row1,col1);
                }
                else
                    printf("Enter Matrix 1 first.\n");

                break;

            case 4:

                if(m2)
                {
                    printf("\nMatrix 2:\n");
                    displayMatrix(b,row2,col2);
                }
                else
                    printf("Enter Matrix 2 first.\n");

                break;

            case 5:

                if(m1)
                {
                    printf("\nCompact Form of Matrix 1\n");
                    displayCompact(Compact1);
                }
                else
                    printf("Enter Matrix 1 first.\n");

                break;

            case 6:

                if(m2)
                {
                    printf("\nCompact Form of Matrix 2\n");
                    displayCompact(Compact2);
                }
                else
                    printf("Enter Matrix 2 first.\n");

                break;

            case 7:

                if(m1 && m2)
                {
                    addCompact(Compact1,Compact2,sum);

                    printf("\nAddition of Compact Matrices:\n");
                    displayCompact(sum);
                }
                else
                    printf("Enter both matrices first.\n");

                break;

            case 8:

                if(m1)
                {
                    simpleTranspose(Compact1,trans);

                    printf("\nSimple Transpose:\n");
                    displayCompact(trans);
                }
                else
                    printf("Enter Matrix 1 first.\n");

                break;

            case 9:

                if(m1)
                {
                    fastTranspose(Compact1,fast);

                    printf("\nFast Transpose:\n");
                    displayCompact(fast);
                }
                else
                    printf("Enter Matrix 1 first.\n");

                break;

            case 10:

                printf("\nProgram terminated successfully.\n");

                break;

            default:

                printf("Invalid Choice!\n");
        }

    }while(choice!=10);

    return 0;
}
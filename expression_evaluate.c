
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define MAX 100

int evalStk[MAX];
int evalTop = -1;

int isFull()
{
    return evalTop == MAX - 1;
}

int isEmpty()
{
    return evalTop == -1;
}

void pushEval(int val)
{
    if (!isFull())
    {
        evalStk[++evalTop] = val;
    }
}

int popEval()
{
    if (isEmpty())
    {
        return 0;
    }

    return evalStk[evalTop--];
}

bool isOp(char op)
{
    return op == '+' || op == '-' || op == '*' ||
           op == '/' || op == '%' || op == '^';
}

int applyOp(int a, int b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;

    case '/':
        return a / b;

    case '%':
        return a % b;

    case '^':
        return (int)pow(a, b);

    default:
        return 0;
    }
}

int evalPostfix(char psf[], int valTable[])
{
    evalTop = -1;

    for (int i = 0; psf[i] != '\0'; i++)
    {
        char ch = psf[i];

        if (ch == ' ' || ch == '\t')
        {
            continue;
        }

        if (isalpha((unsigned char)ch))
        {
            pushEval(valTable[tolower((unsigned char)ch) - 'a']);
        }
        else if (isdigit((unsigned char)ch))
        {
            pushEval(ch - '0');
        }
        else if (isOp(ch))
        {
            if (evalTop < 1)
            {
                return 0;
            }

            int op2 = popEval();
            int op1 = popEval();

            if ((ch == '/' || ch == '%') && op2 == 0)
            {
                return 0;
            }

            pushEval(applyOp(op1, op2, ch));
        }
        else
        {
            return 0;
        }
    }

    if (evalTop == 0)
    {
        return popEval();
    }

    return 0;
}

int main()
{
    char psfExp[MAX];
    int valTable[26];
    bool hasVal[26];
    int choice, result;

    do
    {
        printf("\nEnter 1 to Evaluate Postfix Expression\n");
        printf("Enter 0 to Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter Postfix Expression: ");
            scanf(" %99[^\n]", psfExp);

            for (int i = 0; i < 26; i++)
            {
                hasVal[i] = false;
            }

            for (int i = 0; psfExp[i] != '\0'; i++)
            {
                if (isalpha((unsigned char)psfExp[i]))
                {
                    int idx = tolower((unsigned char)psfExp[i]) - 'a';

                    if (!hasVal[idx])
                    {
                        printf("Enter value for %c: ", psfExp[i]);
                        scanf("%d", &valTable[idx]);
                        hasVal[idx] = true;
                    }
                }
            }

            result = evalPostfix(psfExp, valTable);
            printf("Evaluation Result: %d\n", result);
            break;

        case 0:
            printf("Exiting program.\n");
            break;

        default:
            printf("Invalid choice.\n");
        }

    } while (choice != 0);

    return 0;
}
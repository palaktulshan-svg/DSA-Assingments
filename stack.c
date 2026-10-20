#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 20

char stack[MAX][MAX];
int top = -1;


int isFull()
{
    if (top == MAX - 1)
        return 1;
    else
        return 0;
}

int isEmpty()
{
    if (top == -1)
        return 1;
    else
        return 0;
}

void push(char str[])
{
    if (isFull())
        return;

    top++;
    strcpy(stack[top], str);
}

void pop(char str[])
{
    if (isEmpty())
        return;

    strcpy(str, stack[top]);
    top--;
}

int icp(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;

    if (ch == '*' || ch == '/')
        return 2;

    if (ch == '^')
        return 4;

    if (ch == '(')
        return 5;

    return 0;
}

int isp(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;

    if (ch == '*' || ch == '/')
        return 2;

    if (ch == '^')
        return 3;

    return 0;
}

void in_post(char inexp[], char postexp[])
{
    int k = 0, i = 0;
    char tkn;
    char temp[MAX];

    top = -1;

    tkn = inexp[i];

    while (tkn != '\0')
    {
        if (isspace((unsigned char)tkn))
        {
        }

        else if (isalnum((unsigned char)tkn))
        {
            postexp[k++] = tkn;
        }

        else if (tkn == '(')
        {
            temp[0] = '(';
            temp[1] = '\0';

            push(temp);
        }

        else if (tkn == ')')
        {
            while (!isEmpty() && strcmp(stack[top], "(") != 0)
            {
                pop(temp);
                postexp[k++] = temp[0];
            }

            if (!isEmpty())
                pop(temp);       
        }

        else
        {
            while (!isEmpty() &&
                   strcmp(stack[top], "(") != 0 &&
                   isp(stack[top][0]) >= icp(tkn))
            {
                pop(temp);
                postexp[k++] = temp[0];
            }

            temp[0] = tkn;
            temp[1] = '\0';

            push(temp);
        }

        i++;
        tkn = inexp[i];
    }

    while (!isEmpty())
    {
        pop(temp);
        postexp[k++] = temp[0];
    }

    postexp[k] = '\0';
}


void prefix_to_infix(char prefix[], char infix[])
{
    int i;
    char op;

    char operand1[MAX];
    char operand2[MAX];
    char temp[MAX];

    top = -1;

  
    for (i = 0; prefix[i] != '\0'; i++)
        ;

   
    i--;

    while (i >= 0)
    {
        op = prefix[i];

        
        if (isspace((unsigned char)op))
        {
            i--;
            continue;
        }

       
        if (isalnum((unsigned char)op))
        {
            temp[0] = op;
            temp[1] = '\0';

            push(temp);
        }

        /* Operator */
        else
        {
           
            pop(operand1);

        
            pop(operand2);

        

            temp[0] = '(';
            temp[1] = '\0';

            strcat(temp, operand1);

            int len = strlen(temp);

            temp[len] = op;
            temp[len + 1] = '\0';

            strcat(temp, operand2);
            strcat(temp, ")");

           
            push(temp);
        }

        i--;
    }

    pop(infix);
}

void postfix_to_prefix(char postfix[], char prefix[])
{
    int i;
    char op;

    char operand1[MAX];
    char operand2[MAX];
    char temp[MAX];

    top = -1;

    i = 0;

    while (postfix[i] != '\0')
    {
        op = postfix[i];

       
        if (isspace((unsigned char)op))
        {
            i++;
            continue;
        }

        
        if (isalnum((unsigned char)op))
        {
            temp[0] = op;
            temp[1] = '\0';

            push(temp);
        }

       
        else
        {
           

            pop(operand2);
            pop(operand1);

            
            temp[0] = op;
            temp[1] = '\0';

            strcat(temp, operand1);
            strcat(temp, operand2);
            push(temp);
        }

        i++;
    }

    pop(prefix);
}



int main()
{
    int choice;
    char ch;

    char inexp[MAX];
    char postexp[MAX];

    char prefix[MAX];
    char result[MAX];

    char temp[MAX];

    while (1)
    {
        printf("\n--- Stack Menu ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Infix To Postfix\n");
        printf("4. Prefix To Infix\n");
        printf("5. Postfix To Prefix\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:

            if (isFull())
            {
                printf("Stack is full!\n");
            }
            else
            {
                printf("Enter character to push: ");
                scanf(" %c", &ch);

                temp[0] = ch;
                temp[1] = '\0';

                push(temp);

                printf("'%c' pushed successfully! "
                       "(Current top: %d)\n",
                       ch, top);
            }

            break;

        case 2:

            if (isEmpty())
            {
                printf("Stack is empty!\n");
            }
            else
            {
                pop(temp);

                printf("Popped element: %s\n", temp);
            }

            break;

        case 3:

            printf("Enter infix expression: ");
            scanf("%s", inexp);

            in_post(inexp, postexp);

            printf("Postfix expression: %s\n", postexp);

            break;

        case 4:

            printf("Enter prefix expression: ");
            scanf("%s", prefix);

            prefix_to_infix(prefix, result);

            printf("Infix expression: %s\n", result);

            break;

        case 5:

            printf("Enter postfix expression: ");
            scanf("%s", postexp);

            postfix_to_prefix(postexp, result);

            printf("Prefix expression: %s\n", result);

            break;

        case 6:

            exit(0);

        default:

            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
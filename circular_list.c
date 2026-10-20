
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int exp;
    struct Node *next;
};

struct Node *createNode(int coeff, int exp) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = newNode;

    return newNode;
}

struct Node *insertTerm(struct Node *head, int coeff, int exp) {
    struct Node *newNode = createNode(coeff, exp);
    struct Node *temp;

    if (head == NULL)
        return newNode;

    temp = head;

    while (temp->next != head)
        temp = temp->next;

    temp->next = newNode;
    newNode->next = head;

    return head;
}

struct Node *createPolynomial(int n) {
    struct Node *head = NULL;
    int coeff, exp, i;

    for (i = 0; i < n; i++) {
        printf("Enter coefficient and exponent: ");
        scanf("%d %d", &coeff, &exp);

        head = insertTerm(head, coeff, exp);
    }

    return head;
}

void displayPolynomial(struct Node *head) {
    struct Node *temp;
    int first = 1;

    if (head == NULL) {
        printf("0");
        return;
    }

    temp = head;

    do {
        if (temp->coeff != 0) {
            if (!first && temp->coeff > 0)
                printf(" + ");
            else if (temp->coeff < 0)
                printf(" - ");

            if (first && temp->coeff < 0)
                printf("-");

            int c = abs(temp->coeff);

            if (temp->exp == 0)
                printf("%d", c);
            else if (temp->exp == 1) {
                if (c != 1)
                    printf("%d", c);
                printf("x");
            } else {
                if (c != 1)
                    printf("%d", c);
                printf("x^%d", temp->exp);
            }

            first = 0;
        }

        temp = temp->next;
    } while (temp != head);

    if (first)
        printf("0");
}

struct Node *addPolynomials(struct Node *p1, struct Node *p2) {
    struct Node *result = NULL;
    struct Node *a, *b;

    if (p1 == NULL)
        return p2;

    if (p2 == NULL)
        return p1;

    a = p1;

    do {
        int coeff = a->coeff;
        int exp = a->exp;

        b = p2;

        do {
            if (b->exp == exp) {
                coeff += b->coeff;
            }
            b = b->next;
        } while (b != p2);

        result = insertTerm(result, coeff, exp);
        a = a->next;
    } while (a != p1);

    b = p2;

    do {
        int found = 0;
        a = p1;

        do {
            if (a->exp == b->exp) {
                found = 1;
                break;
            }
            a = a->next;
        } while (a != p1);

        if (!found)
            result = insertTerm(result, b->coeff, b->exp);

        b = b->next;
    } while (b != p2);

    return result;
}

int main() {
    struct Node *p1 = NULL, *p2 = NULL, *sum = NULL;
    int n;

    printf("Enter number of terms in first polynomial: ");
    scanf("%d", &n);
    p1 = createPolynomial(n);

    printf("Enter number of terms in second polynomial: ");
    scanf("%d", &n);
    p2 = createPolynomial(n);

    printf("\nFirst polynomial: ");
    displayPolynomial(p1);

    printf("\nSecond polynomial: ");
    displayPolynomial(p2);

    sum = addPolynomials(p1, p2);

    printf("\nSum of polynomials: ");
    displayPolynomial(sum);

    printf("\n");

    return 0;
}

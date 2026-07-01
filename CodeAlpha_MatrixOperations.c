#include <stdio.h>

void addMatrix(int a[10][10], int b[10][10], int r, int c);
void multiplyMatrix(int a[10][10], int b[10][10], int r1, int c1, int c2);
void transposeMatrix(int a[10][10], int r, int c);

int main() {
    int a[10][10], b[10][10];
    int r1, c1, r2, c2, i, j, choice;

    printf("Enter rows and columns of Matrix A: ");
    scanf("%d %d", &r1, &c1);

    printf("Enter elements of Matrix A:\n");
    for(i = 0; i < r1; i++)
        for(j = 0; j < c1; j++)
            scanf("%d", &a[i][j]);

    printf("Enter rows and columns of Matrix B: ");
    scanf("%d %d", &r2, &c2);

    printf("Enter elements of Matrix B:\n");
    for(i = 0; i < r2; i++)
        for(j = 0; j < c2; j++)
            scanf("%d", &b[i][j]);

    printf("\n1. Matrix Addition");
    printf("\n2. Matrix Multiplication");
    printf("\n3. Transpose of Matrix A");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            if(r1 == r2 && c1 == c2)
                addMatrix(a, b, r1, c1);
            else
                printf("Addition not possible!\n");
            break;

        case 2:
            if(c1 == r2)
                multiplyMatrix(a, b, r1, c1, c2);
            else
                printf("Multiplication not possible!\n");
            break;

        case 3:
            transposeMatrix(a, r1, c1);
            break;

        default:
            printf("Invalid Choice!\n");
    }

    return 0;
}

void addMatrix(int a[10][10], int b[10][10], int r, int c) {
    int i, j, sum[10][10];

    printf("\nResult:\n");
    for(i = 0; i < r; i++) {
        for(j = 0; j < c; j++) {
            sum[i][j] = a[i][j] + b[i][j];
            printf("%d ", sum[i][j]);
        }
        printf("\n");
    }
}

void multiplyMatrix(int a[10][10], int b[10][10], int r1, int c1, int c2) {
    int i, j, k, mul[10][10];

    for(i = 0; i < r1; i++) {
        for(j = 0; j < c2; j++) {
            mul[i][j] = 0;
            for(k = 0; k < c1; k++)
                mul[i][j] += a[i][k] * b[k][j];
        }
    }

    printf("\nResult:\n");
    for(i = 0; i < r1; i++) {
        for(j = 0; j < c2; j++)
            printf("%d ", mul[i][j]);
        printf("\n");
    }
}

void transposeMatrix(int a[10][10], int r, int c) {
    int i, j;

    printf("\nTranspose of Matrix A:\n");
    for(i = 0; i < c; i++) {
        for(j = 0; j < r; j++)
            printf("%d ", a[j][i]);
        printf("\n");
    }
}
#include <stdio.h>
#include <stdlib.h>

void displayMatrix(int **matrix,int rows, int cols);
int **matmul(int **a,int **b,int rowsA,int colsA,int rowsB,int colsB);

int main() {
    int rows = 3;
    int cols = 3;
    int **result;
    int **arr = (int **)malloc(rows * sizeof(int *));
    for(int i=0; i <cols;i++) {
        arr[i] = (int *)malloc(cols * sizeof(int));
    }
    arr[0][0] = 1;
    arr[0][1] = 2;
    arr[0][2] = 3;   
    arr[1][0] = 4;
    arr[1][1] = 5;
    arr[1][2] = 6;
    arr[2][0] = 7;
    arr[2][1] = 8;
    arr[2][2] = 9;
    


    int **B = (int **)malloc(rows * sizeof(int *));
    for(int i=0; i <cols;i++) {
        B[i] = (int *)malloc(cols * sizeof(int));
    }
    B[0][0] = 1;
    B[0][1] = 2;
    B[0][2] = 3;   
    B[1][0] = 4;
    B[1][1] = 5;
    B[1][2] = 6;
    B[2][0] = 7;
    B[2][1] = 8;
    B[2][2] = 9;

    printf("Matrix 1 :\n");
    displayMatrix(arr,rows,cols);
    printf("Matrix 2 :\n");
    displayMatrix(B,rows,cols);
    result = matmul(arr,B,rows,cols,rows,cols);
    printf("Matrix Multiplication\n");
    displayMatrix(result,rows,cols);
    free(result);
    free(arr);
    free(B);
    return 0;
}


void displayMatrix(int **matrix,int rows, int cols) {
    for(int i = 0;i < rows; i++) {
        printf("[");
        for(int j = 0;j < cols;j++) {
            if ((j+1)==cols) {
                printf("%d",matrix[i][j]);
            } else {
                printf("%d ",matrix[i][j]);
            }
        }
        printf("]\n");
    }
}

int **matmul(int **a,int **b,int rowsA,int colsA,int rowsB,int colsB) {
    int **matres = (int**)malloc(rowsA*sizeof(int*));
    for(int x = 0; x < colsB; x++) {
        matres[x] = (int*)malloc(colsB*sizeof(int));
    }

    for(int i = 0;i < rowsA;i++) {
        for(int j = 0;j < colsB;j++) {
            int *res = malloc(sizeof(int));
            *res = 0;
            for(int k = 0;k < colsA;k++) {
                *res += a[i][k]*b[k][j];
            }
            matres[i][j] = *res;
            free(res);
        }
    }

    return matres;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct matmulArguments {
    int i, j, colsA;
    int **A, **B, **matres;
};

void displayMatrix(int **matrix,int rows, int cols);
int **multithreadMatmul(int **a,int **b,int rowsA,int colsA,int rowsB,int colsB);
void *matmulCalc(void *args);



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

    // B[0][0] = 1;
    // B[0][1] = 0;
    // B[0][2] = 0;   
    // B[1][0] = 0;
    // B[1][1] = 1;
    // B[1][2] = 0;
    // B[2][0] = 0;
    // B[2][1] = 0;
    // B[2][2] = 1;

    printf("Matrix 1 :\n");
    displayMatrix(arr,rows,cols);
    printf("Matrix 2 :\n");
    displayMatrix(B,rows,cols);
    printf("Matrix Multiplication\n");
    result = multithreadMatmul(arr,B,rows,cols,rows,cols);
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

int **multithreadMatmul(int **a,int **b,int rowsA,int colsA,int rowsB,int colsB) {
    // printf("start function matmul\n");
    int num_element_res = rowsA*colsB;

    pthread_t **threads = (pthread_t **)malloc(sizeof(pthread_t *));
    int **matres = (int**)malloc(rowsA*sizeof(int*));
    for(int x = 0; x < colsB; x++) {
        matres[x] = (int*)malloc(colsB*sizeof(int));
        threads[x] = (pthread_t *)malloc(colsB*sizeof(pthread_t));
    }
    // printf("done creating matres\n");

    for(int i = 0;i < rowsA;i++) {
        // printf("Calculating for matrix A row %d\n",i);
        for(int j = 0;j < colsB;j++) {
            // printf("Calculating for matrix B column %d\n",j);
            struct matmulArguments *args;
            args = (struct matmulArguments*)malloc(sizeof(struct matmulArguments));
            args->A = a;
            args->B = b;
            args->i = i;
            args->j = j;
            args->colsA = colsA;
            args->matres = matres;
            pthread_create(&threads[i][j],NULL,matmulCalc,args);
        }
    }
    for(int i = 0;i < rowsA; i++) {
        for(int j = 0;j < colsB; j++) {
            pthread_join(threads[i][j],NULL);
        }
    }
    return matres;
}


void *matmulCalc(void *args) {
    struct matmulArguments *arg = (struct matmulArguments*)args;
    int res = 0;
    for(int k = 0;k < arg->colsA;k++) {
        res += arg->A[arg->i][k]*arg->B[k][arg->j];
    }
    arg->matres[arg->i][arg->j] = res;
    return NULL;
}
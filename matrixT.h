#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 1000  // Size of the matrix
#define NUM_THREADS 4
//#define NUM_THREADS 3
//#define NUM_THREADS 2
//#define NUM_THREADS 1
int **A, **B, **C;  // Global matrices
pthread_mutex_t lock;
// Information holder for each thread
typedef struct {
    int thread_id;
    int num_rows;  
} thread_data_t;

// Entry function for each thread
void* matrixMultiplyThread(void* arg) {
    // Extract thread info from the passes argument
     thread_data_t t = *(thread_data_t*)arg;

    // Calculate the start and ending row chunck for each thread to handle
    int start = t.num_rows;  
    int end = (t.thread_id + 1) * t.num_rows;  
    pthread_mutex_lock(&lock); // lock the memory using mutex so this thread only access the needed memory. Prevents overlap.
    
    
    // Loop through the start and end row assigned to the thread and compute matrix multiplication
       
       int tempC, colC = 0; //colC = column number for matrix C
   for (int x = start; x < end; ++x){ //iterate through row x in A and C
    for (int i = 0; i < N; ++i) { 
        for (int j = 0; j < N; ++j) { 
            tempC += A[j][x] * B [i][j]; // iterate through row x column j of A and column i row j of B.
        }
        C [colC++][x] = tempC; // fill in element in matrix C  
        tempC = 0;
        
    }
    colC = 0;
   }

    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}
/*void displayMatrix(int** matrix[N][N], int x) {
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < x; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}*/
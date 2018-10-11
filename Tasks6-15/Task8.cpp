//
// Created by mister on 02.10.18.
//

#include <iostream>
#include <omp.h>
#include "Task8.h"

using namespace std;

long getRandomInt(long min, long max);

void multiplyMatrixByVector(long **A, long *V, long *R, long n, long m);

void fillMatrix(long **A, long n, long m);

long **createMatrix(long n, long m);

long *createVector(long m);

void showVector(long *V, long m);

void showMatrix(long **A, long n, long m);

void pMultiplyMatrixByVector(long **A, long *V, long *R, long n, long m);

void Task8() {
    long n, m;
    cout << "Укажите размерность матрицы: ";
    cin >> n >> m;
    long **A = createMatrix(n, m), *R = createVector(n), *V = createVector(n);
//    showMatrix(A, n, m);
//    cout << '\n';
//    showVector(V, n);
//    cout << '\n';
    multiplyMatrixByVector(A, V, R, n, m);
    cout << "\nРезультат вычислений: ";
    showVector(R, n);
//    showMatrix(A, n, m);
//    cout << '\n';
//    showVector(V, n);
//    cout << '\n';
    pMultiplyMatrixByVector(A, V, R, n, m);
    cout << "\nРезультат вычислений: ";
    showVector(R, n);

    delete[] R;
    delete[] V;
    for (int i = 0; i < n; i++)
        delete[] A[i];
}

long getRandomInt(long min, long max) {
    srand(static_cast<unsigned int>(rand() % static_cast<int>(time(NULL))));
    return min + (rand() % static_cast<int>(max - min + 1));
}

void fillMatrix(long **A, long n, long m) {
    for (long i = 0; i < n; i++) {
        for (long j = 0; j < m; j++)
            A[i][j] = getRandomInt(abs(n - m), n * m);
    }
}

long *createVector(long m) {
    long *V = new long[m];
    for (long i = 0; i < m; ++i)
        V[i] = getRandomInt(1, m * m);
    return V;

}

long **createMatrix(long n, long m) {
    long **A = new long *[n];
    for (long i = 0; i < n; i++)
        A[i] = new long[m];
    fillMatrix(A, n, m);
    return A;
}

void showMatrix(long **A, long n, long m) {
    for (long i = 0; i < n; i++) {
        for (long j = 0; j < m; j++)
            cout << A[i][j] << " ";
        cout << '\n';
    }
}

void showVector(long *V, long m) {
    for (long i = 0; i < m; i++)
        cout << V[i] << " ";
    cout << '\n';
}


void multiplyMatrixByVector(long **A, long *V, long *R, long n, long m) {
    auto start_time = omp_get_wtime();
    for (long i = 0; i < n; i++) {
        R[i] = 0;
        for (long j = 0; j < m; j++) {
            R[i] += V[j] * A[i][j];
        }
    }
    auto end_time = omp_get_wtime();
    auto elapsed_s = end_time - start_time;
    printf("Время умножения матрицы на вектор без распараллеливания: %f", elapsed_s);

}

// Распараллеленное умножение
void pMultiplyMatrixByVector(long **A, long *V, long *R, long n, long m) {
    long i, j;
    auto start_time = omp_get_wtime();
    auto max_threads = omp_get_max_threads();
    for (i = 0; i < n; i++) {
        R[i] = 0;
    omp_set_num_threads(max_threads);
#pragma omp parallel for reduction(+:R[i]) if(n>425 && m>425)
        for (j = 0; j < m; j++) {
            R[i] = R[i] + V[j] * A[i][j];
        }
    }
    auto end_time = omp_get_wtime();
    auto elapsed_s = end_time - start_time;
    printf("Время умножения матрицы на вектор c распараллеливанием: %f", elapsed_s);
}

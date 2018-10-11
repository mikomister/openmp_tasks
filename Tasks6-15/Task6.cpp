//
// Created by mister on 02.10.18.
//
#include <iostream>
#include <omp.h>
#include "Task6.h"

/*
* Задача №6
* Вычислить среднее арифметическое с у каждого массива и сравнить результат.
*/
void Task6() {
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int j, sumA = 0, sumB = 0, n;
    omp_set_num_threads(4);
// for ... reduction при входе в параллельную секцию создает свою локальную копию переменной
// инициализируя её 0 (в данном случае), после чего(при выходе из параллельной секции) результаты частичных сумм
// суммируются и передаются в основной поток
#pragma omp parallel for private(j) reduction(+: sumA, sumB)
    for (j = 0; j < 10; j++) {
        sumA += a[j];
        sumB += b[j];
        n = omp_get_thread_num();
        printf("Thread #%d: \t sumA=%d \t sumB=%d\n", n, sumA, sumB);
    };
    double mA = sumA / 10.0, mB = sumB / 10.0; //среднее арифм.-ое
    printf("\n RESULT REDUCTION \n");
    printf("mA=%f \t mB=%f\n mA %c mB", mA, mB, (mA > mB) ? '>' : (mA < mB) ? '<' : '=');
}

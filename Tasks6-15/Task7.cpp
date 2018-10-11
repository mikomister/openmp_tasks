//
// Created by mister on 02.10.18.
//
#include <iostream>
#include <omp.h>
#include "Task7.h"

/*
* Задача №7
 * Определить две параллельные области, каждая из которых
 * содержит итерационную конструкцию for выполняющую инициализацию элементов
 * одномерных массивов целых чисел a[12], b[12] и c[12].
 * В каждой области определить и выдать на экран количество нитей, номер
 * нити и результат выполнения цикла.
*/
void Task7() {
    int a[12], b[12], c[12];
    int j, i;
    omp_set_num_threads(3);
#pragma omp parallel for schedule(static, 4)
    for (j = 0; j < 12; j++) {
        if (j == 0)
            printf("Number of threads: %d\n", omp_get_num_threads());
        a[j] = rand() % (128 - 1 + 1) + 1;
        b[j] = rand() % a[j];
        printf("Thread #%d: \t a[%d]=%d \t b[%d]=%d\n", omp_get_thread_num(), j, a[j], j, b[j]);
    };
    omp_set_num_threads(4);
#pragma omp parallel for schedule(dynamic, 2)
    for (int i = 0; i < 12; ++i) {
        if (i == 0)
            printf("Number of threads: %d\n", omp_get_num_threads());
        c[i] = a[i] + b[i];
        printf("Thread #%d: \t c[%d]=%d \n", omp_get_thread_num(), i, i, c[i]);
    }
}

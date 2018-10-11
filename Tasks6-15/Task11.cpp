//
// Created by mister on 9.10.18.
//

#include <iostream>
#include <omp.h>
#include <time.h>
#include <cassert>
#include "Task9.h"
#include "Task11.h"

//Написать программу, в которой, объявить и заполнить случайными значениями массив целых
//чисел. Используя возможности OpenMP найти максимальное числовое значение элементов
//массива, кратное 7. Длину массива и количество потоков определить самостоятельно.
//Результат выдать на экран. Для синхронизации числовых значений максимума используется
//механизм критических секций.

using namespace std;

void showArray(int *a, int n);

void Task11() {
    int n, max_threads = omp_get_max_threads(), max = 0;
    printf("Укажите кол-во элементов в массиве:");
    cin >> n;
    int a[n];
    for (auto &i: a) {
        i = getRandomInt(1, 1022);
    }
    omp_set_num_threads(max_threads);
    auto start_time = omp_get_wtime();
#pragma omp parallel for schedule(static, max_threads/2)
    for (int i = 0; i < n; i++) {
        if (a[i] % 7 == 0 && a[i] > max) {
#pragma omp critical
            max = a[i];
        }

    }
    auto end_time = omp_get_wtime();
    auto elapsed_s = end_time - start_time;
    printf("Время выполнения: %f\n", elapsed_s);
    showArray(a, n);
    printf("Максимум кратный 7 в массиве 'a': %d", max);

}

void showArray(int *a, int n) {
    for (int j = 0; j < n; j++)
        printf(" %d ", a[j]);
    cout << endl;
}

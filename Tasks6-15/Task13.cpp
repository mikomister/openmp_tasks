//
// Created by mister on 9.10.18.
//

#include <iostream>
#include <omp.h>
#include <time.h>
#include "cmath"
#include "Task11.h"
#include "Task13.h"

using namespace std;

void Task13() {
    int max_threads = omp_get_max_threads(), result = 0, i, k;
    int a[30] = {1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1};
    omp_set_num_threads(max_threads * max_threads);
    auto start_time = omp_get_wtime();
    k = 29;
    omp_set_num_threads(omp_get_max_threads());
#pragma omp parallel for reduction(+:result) reduction( -:k)
    for (i = 0; i < 30; ++i) {
        result += (int) pow(a[i], k);
        k -= 1;
    }
    auto end_time = omp_get_wtime();
    auto elapsed_s = end_time - start_time;
    printf("Время выполнения: %f\n", elapsed_s);
    printf("Число a в двоичной системе счисления: \n");
    showArray(a, 30);
    printf("Число в десятично системе счисления: %d\n", result);

}
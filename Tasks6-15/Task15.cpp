//
// Created by mister on 9.10.18.
//

#include <iostream>
#include <omp.h>
#include <time.h>
#include <cmath>
#include "Task15.h"

using namespace std;

void Task15() {
    int i, j, m;
    printf("Укажите диапозон(2 целых положительных числа): ");
    cin >> i >> j;
    auto start_time = omp_get_wtime();
    printf("Простые числа в диапозоне от %d до %d:\n", i, j);
    omp_set_num_threads(omp_get_max_threads());
#pragma omp parallel for schedule(static, 2)
    for (m = i; m < j + 1; m++) {
        if (isPrime(m))
            printf(" %d ", m);
    }
    auto end_time = omp_get_wtime();
    auto elapsed_s = end_time - start_time;
    printf("\nВремя выполнения: %f\n", elapsed_s);

}

bool isPrime(int r) {
    bool t = true;
    if (r < 2) return !t;
    else if (r == 2) return t;
    else if (r % 2 == 0) return !t;
    for (int k = 2; k * k < r; ++k) {
        if (r % k == 0)
            return !t;
    }
    return t;
}
//
// Created by mister on 10.10.18.
//

#include <iostream>
#include <omp.h>
#include <time.h>
#include "Task10.h"

int randomInt(int min, int max);

void showArray(int ( &a )[30]);

using namespace std;

void Task10() {
    int a[30], k = 0, i = 0, j = 0;
    for (i = 0; i < 30; i++) {
        a[i] = randomInt(i + 2, (i + 3) * i * i);
    }
    auto start_time = omp_get_wtime();
    omp_set_num_threads(3);
#pragma omp parallel for schedule(static, 5) shared(k)
    for (j = 0; j < 30; j++) {
        if (a[j] % 9 == 0)
#pragma omp atomic
            k++;
    }
    auto end_time = omp_get_wtime();
    auto elapsed_s = end_time - start_time;
    showArray(a);
    printf("Время выполнения: %f\n", elapsed_s);
    printf("Чисел кратных 9 в массиве 'a': %d", k);
}

int randomInt(int min, int max) {
    srand(static_cast<unsigned int>(rand() % static_cast<int>(time(NULL))));
    return min + (rand() % static_cast<int>(max - min + 1));
}


void showArray(int ( &a )[30]) {
    for (auto &i: a)
        printf(" %d ", i);
    cout << endl;
}


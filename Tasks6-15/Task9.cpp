//
// Created by mister on 02.10.18.
//

#include "Task9.h"
#include <iostream>
#include <omp.h>
#include <time.h>

using namespace std;

void showMatrix(int ( &d )[6][8]);

void Task9() {
    int d[6][8];

    for (auto &i : d)
        for (auto &j : i)
            j = getRandomInt(1, getRandomInt(1, 6 * 8));

    showMatrix(d);
    int max = d[0][0], min = max;
    int i = 0, j = 0;
    auto start_time = omp_get_wtime();
#pragma omp parallel for num_threads(1)
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 8; j++) {
#pragma omp critical
            {
                if (max < d[i][j])
                    max = d[i][j];
                else if (min > d[i][j])
                    min = d[i][j];
            };
        }
    };
    auto end_time = omp_get_wtime();
    auto elapsed_s = end_time - start_time;
    printf("Время выполнения: %f\n", elapsed_s);
    printf("Thread: %d, min = %d, max = %d\n", omp_get_thread_num(), min, max);
}

int getRandomInt(int min, int max) {
    srand(static_cast<unsigned int>(rand() % static_cast<int>(time(NULL))));
    return min + (rand() % static_cast<int>(max - min + 1));
}

void showMatrix(int ( &d )[6][8]) {
    for (auto &i : d) {
        for (auto j : i)
            printf(" %d ", j);
        cout << endl;
    }
}
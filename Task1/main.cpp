#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    // Задача №1: Написать програму, где каждый поток
    // печатает свой ID, кол-во потоков всего
    // и строчку "Hello World"
#pragma omp parallel num_threads(8)
    {
        int thread_id = omp_get_thread_num();
        int threads_count = omp_get_num_threads();
        printf("Thread id: %d Threads count: %d\n  Hello, World!\n", thread_id, threads_count);
    };
    // Пояснения: Зачастую вывод различается, так происходит
    // потому что 8 потоков одновременно пытаются обратиться к единственному потоку вывода
    // без синхронизации, такая ситуация называется "data race" or Race condition.

    return 0;
}
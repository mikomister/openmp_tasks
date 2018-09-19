#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    /*
     * Задача №2
     *
     * Если заданное значение числа нитей больше 1, параллельная область выполняется, иначе не выполняется.
     * Число нитей перед первой областью задать равным 3, перед второй – равным 1.
     */
    omp_set_num_threads(3);
#pragma omp parallel
    if (omp_get_num_threads() > 1) {
        int thread_id = omp_get_thread_num();
        int threads_count = omp_get_num_threads();
        printf("Thread id: %d Threads count: %d\n\n", thread_id, threads_count);
    };

    omp_set_num_threads(1);
#pragma omp parallel
    if (omp_get_num_threads() > 1) {
        cout << "TEST\n";
        int thread_id = omp_get_thread_num();
        int threads_count = omp_get_num_threads();
        printf("Thread id: %d Threads count: %d\n\n", thread_id, threads_count);
    };

    return 0;
}
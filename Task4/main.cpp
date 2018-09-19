#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, -9};
    int b[10] = {0, -45, 6, 7, 8, 2, 33, 4, 5, -1};
    int min = a[0];
    int max = b[0];

    /*
     * Задача №4
     *  Основная нить должна выполнять поиск min значения элементов массива a, нить с номером 1 - поиск max значения
     *  элементов массива b. Результат выдать на экран.
     */
#pragma omp parallel num_threads(2)
    {
        if (omp_get_thread_num() == 0) {
            for (int i = 1; i < 10; i++) {
                if (omp_get_thread_num() != 0)
                    printf("1 !? %d\n", omp_get_thread_num());
                min = min > a[i] ? a[i] : min;
            }
        }
        if (omp_get_thread_num() == 1) {
            for (int i = 1; i < 10; i++) {
                if (omp_get_thread_num() != 1)
                    printf("0 !? %d\n", omp_get_thread_num());
                max = max < b[i] ? b[i] : max;
            }
        }
    }
    /*
     * Пояснение: Пробовал также через master и single => - не вышло.
     */
    printf("Min in array 'a': %d\n", min);
    printf("Max in array 'b': %d\n", max);
    return 0;
}
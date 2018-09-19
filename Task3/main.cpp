#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    /*
     * Задача №3
     *
     * Если заданное значение числа нитей больше 1, параллельная область выполняется, иначе не выполняется.
     * Число нитей перед первой областью задать равным 3, перед второй – равным 1.
     */

    long a = 7, b = 11;

    printf("Значение переменных до входа в 1-ую параллельную область:\n a: %d, b: %d\n\n", a, b);

    //parallel region #1
#pragma omp parallel num_threads(2) private(a) firstprivate(b)
    {
        int thread_id = omp_get_thread_num();
        a += thread_id;
        b += thread_id;
        printf("Значение переменных внутри 1-ой параллельной области:\n a: %d, b: %d\nthread_id:%d\n\n", a, b,
               thread_id);
    };

    printf("Значение переменных до входа в 2-ую параллельную область(после выхода из 1-ой):\n a: %d, b: %d\n\n", a, b);

    //parallel region #2
#pragma omp parallel num_threads(4) shared(a) private(b)
    {
        int thread_id = omp_get_thread_num();
        a -= thread_id;
        b -= thread_id;
        printf("Значение переменных внутри 2-ой параллельной области:\n a: %d, b: %d\nthread_id:%d\n\n", a, b,
               thread_id);
    };
    printf("Значение после выхода из 2-ой параллельной области:\n a: %d, b: %d\n\n", a, b);
    return 0;
}
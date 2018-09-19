#include <iostream>
#include <omp.h>
#include <time.h>

using namespace std;

void showM(int ( &d )[6][8]) {
    for (auto &i : d) {
        for (auto j : i)
            printf(" %d ", j);
        cout << endl;
    }
}

int main() {
    int d[6][8];
    for (auto &i : d)
        for (auto &j : i) {
            srand(static_cast<unsigned int>(rand() % static_cast<int>(512 - 3 + time(NULL))));
            j = rand() % (128 - 1 + 1) + 1;
        }

    showM(d);

#pragma omp parallel sections num_threads(3)
    {
#pragma omp section
        {
            int s = 0;
            for (auto &i : d)
                for (auto &j : i) {
                    s += j;
                }

            printf("Thread: %d, среднее арифметическое: %lf\n", omp_get_thread_num(), (double) s / (6.0 * 8.0));
        }

#pragma omp section
        {
            int max = d[0][0], min = max;
            for (auto &i : d)
                for (auto &j : i) {
                    if (max < j)
                        max = j;
                    else if (min > j)
                        min = j;
                }

            printf("Thread: %d, min = %d, max = %d\n", omp_get_thread_num(), min, max);
        }

#pragma omp section
        {
            int k = 0;
            for (auto &i : d)
                for (auto &j : i) {
                    if (j % 3 == 0)
                        k++;
                }
            printf("Thread: %d, число элементов кратное 3-м: %d\n", omp_get_thread_num(), k);
        }
    }
    return 0;

}
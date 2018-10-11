//
// Created by mister on 9.10.18.
//

#include <iostream>
#include <omp.h>
#include <time.h>
#include <cassert>
#include "Task12.h"

void Task12() {
    // Задача №11: Написать програму, где каждый поток
    // печатает свой ID, в обратном порядке 5-ю и более способами
    omp_set_num_threads(8);
#pragma omp parallel
    {
        int ID = omp_get_thread_num();

        // Computations done by each thread

#pragma omp for ordered schedule(static,1)
        for( int t=0; t<omp_get_num_threads(); ++t )
        {
            assert( t==ID );
#pragma omp ordered
            {
                printf("Thread #%d\n", ID);
            }
        }
    }
}
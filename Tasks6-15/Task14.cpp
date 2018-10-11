//
// Created by mister on 9.10.18.
//

#include <iostream>
#include <omp.h>
#include <time.h>
#include <cmath>
#include "Task15.h"
#include "Task14.h"

void Task14() {
    int result = 0, i, j, r = 210;
#pragma omp parallel for reduction(+:result)
    for (i = 1; i <= r; i++)
        result += 2 * i - 1;
    printf("%d == %d", r * r, result);
}
//
// Created by nicholas on 2021/2/25.
//

#include <stdlib.h>

int main(void) {
    int *data = (int *)malloc(100 * sizeof(int));
    data[100] = 0;
    return 0;
}


//
// Created by nicholas on 2021/2/25.
//

#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int *data = (int *)malloc(100 * sizeof(int));
    for (int i = 0; i < 100; i++) {
        data[i] = i;
    }
    printf("before free, element at index 99: %d\n", data[99]);
    free(data);
    printf("after free, element at index 99: %d\n", data[99]);
    return 0;
}


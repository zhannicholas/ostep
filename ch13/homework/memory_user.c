//
// Created by nicholas on 2021/2/24.
//

#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[]) {
    if (argc == 2) {
        printf("memory to allocate: %s MB", argv[1]);
        int size;
        sscanf(argv[1], "%d", &size);
        int *p = malloc(size * 8 * 1024 * 1024);
        printf("location of allocated memory: %p", p);
        while (1) {}

    } else {
        fprintf(stderr, "wrong arguments!");
        exit(-1);
    }
    return 0;
}

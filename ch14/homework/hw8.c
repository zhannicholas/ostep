//
// Created by nicholas on 2021/2/25.
//

#include <stdlib.h>
#include <stdio.h>

typedef struct vector {
    int *data;
    int size;
    int capacity;
} Vector;

void vector_push(Vector *v, int val) {
    // 扩容
    if (v->size == v->capacity) {
        v->capacity *= 2;
        v->data = (int *)realloc(v->data, v->capacity * sizeof(int));
    }
    (v->data)[v->size] = val;
    v->size++;
}

void vector_pop(Vector *v) {
    (v->data)[v->size] = 0;
    v->size--;
    // 压缩
    if (v->size == (int)(v->capacity / 4)) {
        v->capacity = (int)(v->capacity / 2);
        v->data = (int *)realloc(v->data, v->capacity * sizeof(int));
    }
}

void vector_free(Vector *v) {
    free(v->data);
    v->size = 0;
    v->capacity = 0;
    free(v);
}

int main(void) {
    Vector v = {
            (int *)malloc(sizeof(int)),
            1,
            1
    };
    v.data[0] = 1;
    vector_push(&v, 2);
    vector_push(&v, 3);
    vector_push(&v, 4);

    printf("data[0]: %d\n", v.data[0]);
    printf("data[1]: %d\n", v.data[1]);
    printf("data[2]: %d\n", v.data[2]);
    printf("data[3]: %d\n", v.data[3]);

    vector_pop(&v);
    printf("size: %d\n", v.size);
    printf("capacity: %d\n", v.capacity);

    return 0;
}




//
// Created by nicholas on 2021/3/6.
//

#include <assert.h>
#include <stdio.h>
#include <pthread.h>

typedef struct myarg_t {
    int a;
    int b;
} myarg_t;

void* mythread(void* arg) {
    myarg_t* m = (myarg_t*) arg;
    printf("%d %d\n", m->a, m->b);
    return NULL;
}

int main(int argc, char* argv[]) {
    pthread_t p;
    int rc;

    myarg_t args = {10, 20};

    rc = pthread_create(&p, NULL, mythread, &args);
    assert(rc == 0);
    pthread_join(p, NULL);
    printf("Done.\n");

    return 0;
}
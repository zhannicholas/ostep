//
// Created by nicholas on 2021/3/6.
//

#include <assert.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct myarg_t {
    int a;
    int b;
} myarg_t;

typedef struct myret_t {
    int x;
    int y;
} myret_t;

void* mythread(void* arg) {
    myarg_t* m = (myarg_t*) arg;
    printf("%d %d\n", m->a, m->b);
    // oops is ALLOCATED ON STACK: BAD!
    myret_t* oops = malloc(sizeof(myret_t));
    assert(oops != NULL);
    oops->x = 1;
    oops->y = 2;
    // when it returns, the variables on stack are automatically deallocated!
    return (void*)&oops;
}

int main(int argc, char* argv[]) {
    pthread_t p;
    int rc;

    myarg_t args = {10, 20};
    myret_t *m;

    rc = pthread_create(&p, NULL, mythread, &args);
    assert(rc == 0);
    pthread_join(p, (void**) &m);
    printf("%d %d\n", m->x, m->y);

    return 0;
}
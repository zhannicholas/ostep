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
    myret_t* r = malloc(sizeof(myret_t));
    assert(r != NULL);
    r->x = 1;
    r->y = 2;
    return (void*)r;
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
    free(m);
    return 0;
}
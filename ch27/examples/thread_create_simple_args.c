//
// Created by nicholas on 2021/3/6.
//

#include <assert.h>
#include <stdio.h>
#include <pthread.h>

void* mythread(void* arg) {
    int m = (int) arg;
    printf("%d\n", m);
    return (void*) (arg + 1);
}

int main(int argc, char* argv[]) {
    pthread_t p;
    int rc, m;


    rc = pthread_create(&p, NULL, mythread, (void*) 100);
    assert(rc == 0);
    pthread_join(p, (void**) &m);
    printf("%d\n", m);

    return 0;
}
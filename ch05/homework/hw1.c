/*
 * 1. Write a program that calls fork(). Before calling fork(), have the main process access a variable (e.g., x) and set
 * its value to something (e.g., 100). What value is the variable in the child process? What happens to the variable when
 * both the child and parent change the value of x?
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int x = 100;
    int rc = fork();
    if (rc < 0) {   // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {   //  child (new process)
        printf("reading x from child: %d\n", x);
        x += 50;
        printf("reading x from child: %d\n", x);
    } else {    // parent goes down this path (main)
        int wc = wait(NULL);
        printf("reading x from parent: %d\n", x);
        x++;
        printf("reading x from parent: %d\n", x);
    }
    return 0;
}


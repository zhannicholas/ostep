/*
 * 7. Write a program that creates a child process, and then in the child closes standard output (STDOUT FILENO).
 * What happens if the child calls printf() to print some output after closing the descriptor?
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {   // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {   //  child (new process)
        printf("before closing standard output\n");
        fclose(STDOUT_FILENO);
        printf("after closing standard output\n");
    } else {    // parent goes down this path (main)
        int wc = wait(NULL);
        printf("hello, I am parent of %d (pid: %d) (pid: %d)\n", rc, wc, (int) getpid());
    }
    return 0;
}
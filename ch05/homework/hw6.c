/*
 * 6. Write a slight modification of the previous program, this time using waitpid() instead of wait(). When would waitpid() be useful?
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
        printf("hello, I am child (pid:%d)\n", (int) getpid());
    } else {    // parent goes down this path (main)
        int status = waitpid(getpid(), NULL, WUNTRACED);
        printf("hello, I am parent of %d (status: %d) (pid: %d)\n", rc, status, (int) getpid());
    }
    return 0;
}
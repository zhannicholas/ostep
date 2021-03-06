/*
 * 8. Write a program that creates two children,
 * and connects the standard output of one to the standard input of the other, using the pipe() system call.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());
    int cid1 = fork();
    if (cid1 < 0) {
        fprintf(stderr, "fork failed!\n");
        exit(EXIT_FAILURE);
    } else if (cid1 == 0) { // child (new process)
        int pipefd[2];
        char buff;
        if (pipe(pipefd) < 0) {
            fprintf(stderr, "pipe failed!\n");
            exit(EXIT_FAILURE);
        } else {
            int cid2 = fork();
            if (cid2 < 0) {
                fprintf(stderr, "fork failed!\n");
                exit(EXIT_FAILURE);
            } else if (cid2 == 0) {
                close(pipefd[1]);   // close unused write end
                while (read(pipefd[0], &buff, 1) > 0) {
                    write(STDOUT_FILENO, &buff, 1);
                }
                write(STDOUT_FILENO, "\n", 1);
                close(pipefd[0]);
                _exit(EXIT_SUCCESS);
            } else {
                char *text = "hello there, child!\n";
                close(pipefd[0]);   // close unused read end
                write(pipefd[1], text, strlen(text));
                close(pipefd[1]);   // Reader will see EOF
                wait(NULL);         // Wait for child
                exit(EXIT_SUCCESS);
            }
        }
    } else {
        wait(NULL);         // Wait for child
        exit(EXIT_SUCCESS);
    }
}
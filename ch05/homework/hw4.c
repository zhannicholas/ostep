/*
 * 4. Write a program that calls fork() and then calls some form of exec() to run the program /bin/ls.
 * See if you can try all of the variants of exec(), including (on Linux) execl(), execle(), execlp(), execv(),
 * execvp(), and execvpe(). Why do you think there are so many variants of the same basic call?
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void run_execl();
void run_execle();
void run_execlp();
void run_execv();
void run_execvp();
void run_execvpe();

int main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {   // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {   //  child (new process)
        printf("running /bin/ls ...");
//        run_execl();
//        run_execle();
//        run_execlp();
//        run_execv();
//        run_execvp();
        run_execvpe();
        printf("\nthis shouldn't print out\n");
    } else {    // parent goes down this path (main)
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc: %d) (pid: %d)\n", rc, wc, (int) getpid());
    }
    return 0;
}

void run_execl() {
    execl("/bin/ls", "ls", "-a", "..", NULL);
}

void run_execle() {
    char *myargs[4];
    myargs[0] = strdup("/bin/ls");
    myargs[1] = strdup("ls");
    myargs[2] = strdup("..");
    myargs[3] = NULL;
    execle(myargs[0], myargs[1], myargs[2], myargs[3], myargs);
}

void run_execlp() {
    execlp("/bin/ls", "ls", "-a", "..", NULL);
}

void run_execv() {
    char *myargs[2];
    myargs[0] = strdup("/bin/ls");   // program: "/bin/ls"
    myargs[1] = NULL;   // marks end of array
    execv(myargs[0], myargs);  // run ls
}

void run_execvp() {
    char *myargs[2];
    myargs[0] = strdup("/bin/ls");   // program: "/bin/ls"
    myargs[1] = NULL;   // marks end of array
    execvp(myargs[0], myargs);  // run ls
}

void run_execvpe() {
    char *myargs[2];
    myargs[0] = strdup("/bin/ls");   // program: "/bin/ls"
    myargs[1] = NULL;   // marks end of array
    execvpe(myargs[0], myargs);  // run ls
}
/*
 * 2. Write a program that opens a file (with the open() system call) and then calls fork() to create a new process.
 * Can both the child and parent access the file descriptor returned by open()? What happens when they are writing to
 * the file concurrently, i.e., at the same time?
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    FILE* file = fopen("new_file.out", "a");
    if (file == NULL) {
        fprintf(stderr, "\n fopen() failed");
    } else {
        int rc = fork();
        if (rc < 0) {
            fprintf(stderr, "fork failed\n");
            fclose(file);
            exit(1);
        } else if (rc == 0) {
            for (int i=0; i<5; i++)
                fprintf(file, "writing from child, #%d\n", i);
        } else {
            for (int i=0; i<5; i++)
                fprintf(file, "writing from parent, #%d\n", i);
        }
        fclose(file);
    }
    return 0;
}


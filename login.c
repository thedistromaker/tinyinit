#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "login.h"

void spawn_tty(void) {
        while (1) {
                pid_t pid = fork();
                if (pid == 0) {
                        execl("/bin/login", "login", NULL);
                        perror("execl login");
                        exit(1);
                }

                int status;
                waitpid(pid, &status, 0);
                printf("User logged out, ending current session and spawning new login.\n");
        }
}
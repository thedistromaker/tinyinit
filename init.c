#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "mounts.h"
#include "login.h"
#include "shutdown.h"

volatile sig_atomic_t shutdown_requested = 0; // We set the shutdown request to 0 so that the system doesn't have a seizure.
volatile sig_atomic_t reboot_requested = 0;   // We set the reboot request to 0 so that the system doesn't bootloop.
                                              // And now the reboot and shutdown logic with SIGINT and SIGUSR1
void handle_shtdwn(int sig) {
       shutdown_requested = 1; // Setting it to 1 so that it signals for a shutdown.
}

void handle_reboot(int sig) {
        reboot_requested = 1; // Setting it to 1 so that it signals for a reboot.
}

int main() {
        printf("initramfs-init 1.1.0 starting..."); // Here is where we start our init system.
        signal(SIGINT, handle_shtdwn);
        signal(SIGUSR1, handle_reboot);
        if (mount_essfs() != 0) {
                fprintf(stderr, "F: Unable to mount root filesystem.\n"); // Where we set up the root filesystem, and the error logic.
        }
        spawn_tty(); // Spawn the login screen and loop.
        if (reboot_requested)
                shutdown_sys(1); // Restart and shutdown logic.
        else
                shutdown_sys(0);

        return 0;
}

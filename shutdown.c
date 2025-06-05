#include <stdio.h>
#include <unistd.h>
#include <sys/reboot.h>
#include "shutdown.h"

void shutdown_sys(int reboot_flag) {
        printf("Writing changes to disk...");
        sync();
        printf("%s system...\n", reboot_flag ? "Rebooting" : "Shutting down");
        reboot(reboot_flag ? RB_AUTOBOOT : RB_POWER_OFF);
}
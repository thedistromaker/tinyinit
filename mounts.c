#include <stdio.h>
#include <sys/mount.h>
#include <string.h>
#include "mounts.h"

static int mount_vfs(const char *source, const char *target, const char *type) {
        if (mount(source, type, target, 0, "") < 0) {
                perror(target);
                return -1;
        }
        return 0;
}

int mount_essfs() {
        int status = 0;
        status |= mount_vfs("proc", "proc", "/proc");
        status |= mount_vfs("sysfs", "sysfs", "/sys");
        status |= mount_vfs("devtmpfs", "devtmpfs", "/dev");
        return status;
}

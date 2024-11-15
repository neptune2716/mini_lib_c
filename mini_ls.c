#include "mini_lib.h"
#include <sys/types.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <unistd.h>

struct linux_dirent {
    unsigned long   d_ino;
    unsigned long   d_off;
    unsigned short  d_reclen;
    char            d_name[];
};

int main() {
    int fd;
    int nread;
    char buf[1024];
    struct linux_dirent *d;
    int bpos;

    fd = open(".", O_RDONLY | O_DIRECTORY);
    if (fd == -1) {
        mini_printf("Erreur: Impossible d'ouvrir le répertoire.\n");
        mini_exit();
    }

    for (;;) {
        nread = syscall(SYS_getdents, fd, buf, sizeof(buf));
        if (nread == -1) {
            mini_printf("Erreur: Impossible de lire le répertoire.\n");
            mini_exit();
        }

        if (nread == 0)
            break;

        for (bpos = 0; bpos < nread;) {
            d = (struct linux_dirent *) (buf + bpos);

            mini_printf(d->d_name);
            mini_printf("\n");

            bpos += d->d_reclen;
        }
    }

    syscall(SYS_close, fd);
    mini_exit();
    return 0;
}

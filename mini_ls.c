#include "mini_lib.h"
#include <sys/types.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <unistd.h>

// Définition de la structure linux_dirent
struct linux_dirent {
    unsigned long   d_ino;     // Numéro d'inœud
    unsigned long   d_off;     // Décalage vers la prochaine entrée
    unsigned short  d_reclen;  // Longueur de cette entrée
    char            d_name[];  // Nom du fichier (de longueur variable)
};

int main() {
    int fd;
    int nread;
    char buf[1024];
    struct linux_dirent *d;
    int bpos;

    // Ouvrir le répertoire courant
    fd = open(".", O_RDONLY | O_DIRECTORY);
    if (fd == -1) {
        mini_printf("Erreur: Impossible d'ouvrir le répertoire.\n");
        mini_exit();
    }

    // Lire les entrées du répertoire en utilisant getdents
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

            // Afficher le nom du fichier
            mini_printf(d->d_name);
            mini_printf("\n");

            bpos += d->d_reclen;
        }
    }

    close(fd);
    mini_exit();
    return 0;
}

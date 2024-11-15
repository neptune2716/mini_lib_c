//exo 40
#include "mini_lib.h"
#define SYS_stat 4
#define SYS_rmdir 84

struct stat {
    unsigned long st_mode;
};

#define S_IFMT  0170000
#define S_IFDIR 0040000
#define S_ISDIR(mode) (((mode) & S_IFMT) == S_IFDIR)

int main(int argc, char* argv[]) {
    if (argc != 2) {
        mini_printf("Usage: mini_rmdir <directory>\n");
        mini_exit();
    }

    char* dir_path = argv[1];
    struct stat path_stat;

    if (syscall(SYS_stat, dir_path, &path_stat) == -1) {
        mini_perror("Erreur: Impossible d'accéder au répertoire");
        mini_exit();
    }

    if (!S_ISDIR(path_stat.st_mode)) {
        mini_printf("Erreur: Le chemin spécifié n'est pas un répertoire.\n");
        mini_exit();
    }

    if (syscall(SYS_rmdir, dir_path) == -1) {
        mini_perror("Erreur: Impossible de supprimer le répertoire");
        mini_exit();
    }

    mini_printf("Répertoire supprimé avec succès: ");
    mini_printf(dir_path);
    mini_printf("\n");

    mini_exit();
    return 0;
}

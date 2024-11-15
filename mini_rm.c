//exo 40
#include "mini_lib.h"
#define SYS_stat 4
#define SYS_unlink 87

struct stat {
    unsigned long st_mode;
};

#define S_IFMT  0170000
#define S_IFREG 0100000
#define S_ISREG(mode) (((mode) & S_IFMT) == S_IFREG)

int main(int argc, char* argv[]) {
    if (argc != 2) {
        mini_printf("Usage: mini_rm <file>\n");
        mini_exit();
    }

    char* file_path = argv[1];
    struct stat file_stat;

    if (syscall(SYS_stat, file_path, &file_stat) == -1) {
        mini_perror("Erreur: Impossible d'accéder au fichier");
        mini_exit();
    }

    if (!S_ISREG(file_stat.st_mode)) {
        mini_printf("Erreur: Le fichier spécifié n'est pas un fichier régulier.\n");
        mini_exit();
    }

    if (syscall(SYS_unlink, file_path) == -1) {
        mini_perror("Erreur: Impossible de supprimer le fichier");
        mini_exit();
    }

    mini_printf("Fichier supprimé avec succès: ");
    mini_printf(file_path);
    mini_printf("\n");

    mini_exit();
    return 0;
}

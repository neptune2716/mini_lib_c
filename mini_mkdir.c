//exo 40
#include "mini_lib.h"
#define SYS_mkdir 83

int main(int argc, char* argv[]) {
    if (argc != 2) {
        mini_printf("Usage: mini_mkdir <directory_name>\n");
        mini_exit();
    }

    char* dir_name = argv[1];

    if (syscall(SYS_mkdir, dir_name, 0755) == -1) {
        mini_perror("Erreur: Impossible de créer le répertoire");
        mini_exit();
    }

    mini_printf("Répertoire créé avec succès: ");
    mini_printf(dir_name);
    mini_printf("\n");

    mini_exit();
    return 0;
}

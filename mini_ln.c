//exo 40
#include "mini_lib.h"
#define SYS_symlink 88

int main(int argc, char* argv[]) {
    if (argc != 3) {
        mini_printf("Usage: mini_ln <source> <destination>\n");
        mini_exit();
    }

    char* source = argv[1];
    char* destination = argv[2];

    if (syscall(SYS_symlink, source, destination) == -1) {
        mini_perror("Erreur: Impossible de créer le lien symbolique");
        mini_exit();
    }

    mini_printf("Lien symbolique créé de ");
    mini_printf(source);
    mini_printf(" vers ");
    mini_printf(destination);
    mini_printf(".\n");

    mini_exit();
    return 0;
}

#include "mini_lib.h"
#include <sys/stat.h> // For mkdir
#include <sys/types.h>

/**
 * @brief Creates a new directory with the specified name.
 *
 * @param argc Argument count.
 * @param argv Argument values.
 * @return int Exit status.
 */
int main(int argc, char* argv[]) {
    if (argc != 2) {
        mini_printf("Usage: mini_mkdir <directory_name>\n");
        mini_exit();
    }

    char* dir_name = argv[1];

    // Attempt to create the directory with default permissions
    if (mkdir(dir_name, 0755) == -1) {
        mini_perror("Erreur: Impossible de créer le répertoire");
        mini_exit();
    }

    mini_printf("Répertoire créé avec succès: ");
    mini_printf(dir_name);
    mini_printf("\n");

    mini_exit();
    return 0;
}
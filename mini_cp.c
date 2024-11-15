#include "mini_lib.h"
#include <errno.h>

//exo 40
int main(int argc, char* argv[]) {
    if (argc != 3) {
        mini_printf("Usage: mini_cp <source> <destination>\n");
        mini_exit();
    }

    char* src = argv[1];
    char* dest = argv[2];

    MYFILE* srcFile = mini_fopen(src, 'r');
    if (srcFile == NULL) {
        mini_printf("Erreur: Impossible d'ouvrir le fichier source.\n");
        mini_exit();
    }

    MYFILE* destFile = mini_fopen(dest, 'w');
    if (destFile == NULL) {
        mini_printf("Erreur: Impossible d'ouvrir le fichier de destination.\n");
        mini_fclose(srcFile);
        mini_exit();
    }

    char buffer[BUF_SIZE];
    int items_read;

    while ((items_read = mini_fread(buffer, sizeof(char), BUF_SIZE, srcFile)) > 0) {
        if (mini_fwrite(buffer, sizeof(char), items_read, destFile) != items_read) {
            mini_printf("Erreur: Écriture dans le fichier de destination échouée.\n");
            mini_fclose(srcFile);
            mini_fclose(destFile);
            mini_exit();
        }
    }

    if (items_read == -1) {
        mini_printf("Erreur: Lecture du fichier source échouée.\n");
    }

    mini_fclose(srcFile);
    mini_fclose(destFile);

    mini_printf("Copie réussie.\n");
    mini_exit();
    return 0;
}
#include "mini_lib.h"

// Exercice 40 : mini_clean
int main(int argc, char* argv[]) {
    if (argc != 2) {
        mini_printf("Usage: mini_clean <fichier>\n");
        mini_exit();
    }

    MYFILE* file = mini_fopen(argv[1], 'w');
    if (file == NULL) {
        mini_printf("Erreur: Impossible de créer ou d'ouvrir le fichier.\n");
        mini_exit();
    }

    mini_fclose(file);

    mini_printf("Fichier ");
    mini_printf(argv[1]);
    mini_printf(" nettoyé.\n");

    mini_exit();
    return 0;
}

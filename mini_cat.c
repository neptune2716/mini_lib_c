
#include "mini_lib.h"

//exo 40
int main(int argc, char* argv[]) {
    if (argc != 2) {
        mini_printf("Usage: mini_cat <fichier>\n");
        mini_exit();
    }

    MYFILE* file = mini_fopen(argv[1], 'r');
    if (file == NULL) {
        mini_printf("Erreur: Impossible d'ouvrir le fichier.\n");
        mini_exit();
    }

    int ch;
    while ((ch = mini_fgetc(file)) != -1) {
        mini_fputc(mini_stdout, (char)ch);
    }
    mini_fflush(mini_stdout);
    mini_fclose(file);

    mini_exit();
    return 0;
}
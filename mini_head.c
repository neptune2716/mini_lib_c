//exo 40
#include "mini_lib.h"

int main(int argc, char* argv[]) {
    if (argc != 4 || mini_strcmp(argv[1], "-n") != 0) {
        mini_printf("Usage: mini_head -n <N> <fichier>\n");
        mini_exit();
    }

    int N = mini_atoi(argv[2]);
    if (N <= 0) {
        mini_printf("Erreur: N doit être un entier positif.\n");
        mini_exit();
    }

    MYFILE* file = mini_fopen(argv[3], 'r');
    if (file == NULL) {
        mini_printf("Erreur: Impossible d'ouvrir le fichier.\n");
        mini_exit();
    }

    char line[256];
    int line_count = 0;

    while (line_count < N && mini_fread(line, sizeof(char), 255, file) > 0) {
        mini_printf(line);
        mini_printf("\n");
        line_count++;
    }

    mini_fclose(file);
    mini_exit();
    return 0;
}
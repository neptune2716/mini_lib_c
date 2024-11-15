//exo 40
#include "mini_lib.h"
#include <stdio.h>

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
    int char_read;
    int index = 0;

    while (line_count < N && (char_read = mini_fgetc(file)) != EOF) {
        if (char_read == '\n') {
            line[index] = '\0';
            mini_printf(line);
            mini_printf("\n");
            line_count++;
            index = 0;
        } else {
            if (index < 255) {
                line[index++] = (char)char_read;
            }
        }
    }

    mini_fclose(file);
    mini_exit();
    return 0;
}
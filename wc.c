//exo 40
#include "mini_lib.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        mini_printf("Usage: wc <fichier>\n");
        mini_exit();
    }

    MYFILE* file = mini_fopen(argv[1], 'r');
    if (file == NULL) {
        mini_printf("Erreur: Impossible d'ouvrir le fichier.\n");
        mini_exit();
    }

    char ch;
    int word_count = 0;
    int in_word = 0;

    while ((ch = (char)mini_fgetc(file)) != -1) {
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            if (in_word) {
                word_count++;
                in_word = 0;
            }
        } else {
            in_word = 1;
        }
    }

    if (in_word) {
        word_count++;
    }

    mini_printf("Nombre de mots: ");
    char num_str[12];
    mini_itoa(word_count, num_str);
    mini_printf(num_str);
    mini_printf("\n");

    mini_fclose(file);
    mini_exit();
    return 0;
}
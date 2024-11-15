#include "mini_lib.h"

//exo 40
int mini_strstr(char* haystack, char* needle) {
    if (!haystack || !needle) return 0;
    int len_haystack = mini_strlen(haystack);
    int len_needle = mini_strlen(needle);
    for (int i = 0; i <= len_haystack - len_needle; i++) {
        int j = 0;
        while (j < len_needle && haystack[i + j] == needle[j]) {
            j++;
        }
        if (j == len_needle) {
            return 1;
        }
    }
    return 0; 
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        mini_printf("Usage: mini_grep <mot> <fichier>\n");
        mini_exit();
    }

    char* mot = argv[1];
    char* filename = argv[2];

    MYFILE* file = mini_fopen(filename, 'r');
    if (file == NULL) {
        mini_printf("Erreur: Impossible d'ouvrir le fichier.\n");
        mini_exit();
    }

    char line[256];
    int ch;
    int i = 0;

    while ((ch = mini_fgetc(file)) != -1) {
        if (ch != '\n' && i < 255) {
            line[i++] = (char)ch;
        } else {
            line[i] = '\0';
            if (mini_strstr(line, mot)) {
                mini_printf(line);
                mini_printf("\n");
            }
            i = 0;
        }
    }
    if (i > 0) {
        line[i] = '\0';
        if (mini_strstr(line, mot)) {
            mini_printf(line);
            mini_printf("\n");
        }
    }

    mini_fclose(file);

    mini_exit();
    return 0;
}
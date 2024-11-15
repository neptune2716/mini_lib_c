
#include "mini_lib.h"

//exo 40
int main(int argc, char* argv[]) {
    if (argc != 4 || mini_strcmp(argv[1], "-n") != 0) {
        mini_printf("Usage: mini_tail -n <N> <fichier>\n");
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

    char *lines[N];
    int line_lengths[N];
    int current_line = 0;

    for (int i = 0; i < N; i++) {
        lines[i] = mini_calloc(1, 1024);
        if (lines[i] == NULL) {
            mini_printf("Erreur: Mémoire insuffisante.\n");
            mini_exit();
        }
        line_lengths[i] = 0;
    }

    int ch;
    while ((ch = mini_fgetc(file)) != -1) {
        if (line_lengths[current_line] < 1023) {
            lines[current_line][line_lengths[current_line]++] = (char)ch;
        }

        if (ch == '\n') {
            lines[current_line][line_lengths[current_line]] = '\0';
            current_line = (current_line + 1) % N;
            line_lengths[current_line] = 0;
        }
    }

    int start = current_line;
    for (int i = 0; i < N; i++) {
        int idx = (start + i) % N;
        if (line_lengths[idx] > 0) {
            mini_printf(lines[idx]);
        }
    }

    for (int i = 0; i < N; i++) {
        mini_free(lines[i]);
    }

    mini_fclose(file);

    mini_exit();
    return 0;
}
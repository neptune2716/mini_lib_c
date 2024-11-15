#include "mini_lib.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        mini_printf("Usage: mini_quickdiff <source> <destination>\n");
        mini_exit();
    }

    MYFILE* srcFile = mini_fopen(argv[1], 'r');
    if (srcFile == NULL) {
        mini_printf("Erreur: Impossible d'ouvrir le fichier source.\n");
        mini_exit();
    }

    MYFILE* destFile = mini_fopen(argv[2], 'r');
    if (destFile == NULL) {
        mini_printf("Erreur: Impossible d'ouvrir le fichier de destination.\n");
        mini_fclose(srcFile);
        mini_exit();
    }

    char src_line[BUF_SIZE];
    char dest_line[BUF_SIZE];
    int line_num = 1;
    int src_eof = 0, dest_eof = 0;

    while (1) {
        // Read a line from the source file using mini_fgetc
        int src_index = 0;
        int ch;
        while ((ch = mini_fgetc(srcFile)) != -1 && ch != '\n' && src_index < BUF_SIZE - 1) {
            src_line[src_index++] = (char)ch;
        }
        if (ch == -1) {
            src_eof = 1;
        }
        src_line[src_index] = '\0';

        // Read a line from the destination file using mini_fgetc
        int dest_index = 0;
        while ((ch = mini_fgetc(destFile)) != -1 && ch != '\n' && dest_index < BUF_SIZE - 1) {
            dest_line[dest_index++] = (char)ch;
        }
        if (ch == -1) {
            dest_eof = 1;
        }
        dest_line[dest_index] = '\0';

        if (src_eof && dest_eof) {
            break;
        }

        if (src_eof || dest_eof || mini_strcmp(src_line, dest_line) != 0) {
            mini_printf("Diff at line ");
            char line_str[12];
            mini_itoa(line_num, line_str);
            mini_printf(line_str);
            mini_printf(":\n");
            if (!src_eof) {
                mini_printf("Source: ");
                mini_printf(src_line);
                mini_printf("\n");
            } else {
                mini_printf("Source: <EOF>\n");
            }
            if (!dest_eof) {
                mini_printf("Destination: ");
                mini_printf(dest_line);
                mini_printf("\n");
            } else {
                mini_printf("Destination: <EOF>\n");
            }
        }

        line_num++;
    }

    mini_fclose(srcFile);
    mini_fclose(destFile);
    mini_exit();
    return 0;
}
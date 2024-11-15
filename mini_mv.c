//exo 40
#include "mini_lib.h"
#define SYS_unlink 87

int main(int argc, char* argv[]) {
    if (argc != 3) {
        mini_printf("Usage: mini_mv <source> <destination>\n");
        mini_exit();
    }

    char* source = argv[1];
    char* destination = argv[2];

    MYFILE* srcFile = mini_fopen(source, 'r');
    if (srcFile == NULL) {
        mini_perror("Erreur à l'ouverture du fichier source");
        mini_exit();
    }

    MYFILE* destFile = mini_fopen(destination, 'w');
    if (destFile == NULL) {
        mini_perror("Erreur à l'ouverture du fichier de destination");
        mini_fclose(srcFile);
        mini_exit();
    }

    char buffer[BUF_SIZE];
    int bytes_read;
    while ((bytes_read = mini_fread(buffer, sizeof(char), BUF_SIZE, srcFile)) > 0) {
        if (mini_fwrite(buffer, sizeof(char), bytes_read, destFile) != bytes_read) {
            mini_perror("Erreur lors de l'écriture dans le fichier de destination");
            mini_fclose(srcFile);
            mini_fclose(destFile);
            mini_exit();
        }
    }

    mini_fclose(srcFile);
    mini_fclose(destFile);

    if (syscall(SYS_unlink, source) == -1) {
        mini_perror("Erreur lors de la suppression du fichier source");
        mini_exit();
    }

    mini_printf("Fichier déplacé de ");
    mini_printf(source);
    mini_printf(" vers ");
    mini_printf(destination);
    mini_printf(".\n");

    mini_exit();
    return 0;
}

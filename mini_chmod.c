
#include "mini_lib.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        mini_printf("Usage: mini_chmod <permissions> <filename>\n");
        mini_exit();
    }

    char* perm_str = argv[1];
    char* filename = argv[2];

    // Convert permission string to integer
    int permissions = 0;
    for (int i = 0; i < mini_strlen(perm_str); i++) {
        if (perm_str[i] < '0' || perm_str[i] > '7') {
            mini_printf("Erreur: Permissions invalides. Utilisez des valeurs octales (e.g., 755).\n");
            mini_exit();
        }
        permissions = permissions * 8 + (perm_str[i] - '0');
    }

    // Change file permissions
    if (chmod(filename, permissions) == -1) {
        mini_printf("Erreur: Impossible de changer les permissions.\n");
        mini_exit();
    }

    mini_printf("Permissions changées avec succès.\n");
    mini_exit();
    return 0;
}
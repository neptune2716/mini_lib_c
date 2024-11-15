#include "mini_lib.h"

//exo 40
int main(int argc, char* argv[]) {
    if (argc < 2) {
        mini_printf("Usage: mini_echo <message>\n");
        mini_exit();
    }

    for (int i = 1; i < argc; i++) {
        mini_printf(argv[i]);
        if (i < argc - 1) {
            mini_printf(" ");
        }
    }
    mini_printf("\n");

    mini_exit();
    return 0;
}

#include "mini_lib.h"
#include <unistd.h>  // For rename and unlink
#include <errno.h>

/**
 * @brief Moves a file from source to destination.
 *
 * @param argc Argument count.
 * @param argv Argument values.
 * @return int Exit status.
 */
int main(int argc, char* argv[]) {
    if (argc != 3) {
        mini_printf("Usage: mini_mv <source> <destination>\n");
        mini_exit();
    }

    char* source = argv[1];
    char* destination = argv[2];

    // Attempt to rename the file (move it)
    if (rename(source, destination) == -1) {
        // If rename fails, attempt to copy and delete
        MYFILE* srcFile = mini_fopen(source, 'r');
        if (srcFile == NULL) {
            mini_perror("Error opening source file");
            mini_exit();
        }

        MYFILE* destFile = mini_fopen(destination, 'w');
        if (destFile == NULL) {
            mini_perror("Error opening destination file");
            mini_fclose(srcFile);
            mini_exit();
        }

        char buffer[BUF_SIZE];
        int bytes_read;
        while ((bytes_read = mini_fread(buffer, sizeof(char), BUF_SIZE, srcFile)) > 0) {
            if (mini_fwrite(buffer, sizeof(char), bytes_read, destFile) != bytes_read) {
                mini_perror("Error writing to destination file");
                mini_fclose(srcFile);
                mini_fclose(destFile);
                mini_exit();
            }
        }

        mini_fclose(srcFile);
        mini_fclose(destFile);

        // Remove the source file
        if (unlink(source) == -1) {
            mini_perror("Error deleting source file");
            mini_exit();
        }
    }

    mini_printf("File moved from ");
    mini_printf(source);
    mini_printf(" to ");
    mini_printf(destination);
    mini_printf(".\n");

    mini_exit();
    return 0;
}
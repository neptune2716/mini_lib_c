// mini_io.c
#include "mini_lib.h"
#include <unistd.h>
#include <fcntl.h> 
#include <errno.h>
#include <stddef.h>

// Exercice 26
#define IOBUFFER_SIZE 2048

// Exercice 34
MYFILE* open_files_list = NULL;

MYFILE* mini_stdout = NULL;

void initialize_mini_io() {
    if (mini_stdout == NULL) {
        mini_stdout = (MYFILE*)mini_calloc(1, sizeof(MYFILE));
        if (mini_stdout == NULL) {
            return;
        }
        mini_stdout->fd = 1; 
        mini_stdout->ind_write = 0;
        mini_stdout->buffer_write = NULL;
        mini_stdout->next = open_files_list;
        open_files_list = mini_stdout;
    }
}

// Exercice 28 : mini_fopen
MYFILE* mini_fopen(char* file, char mode) {
    int fd;
    MYFILE* myfile = (MYFILE*)mini_calloc(1, sizeof(MYFILE));
    if (!myfile) return NULL;

    switch (mode) {
        case 'r':
            fd = open(file, O_RDONLY);
            break;
        case 'w':
            fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            break;
        case 'b':
            fd = open(file, O_RDWR | O_CREAT, 0644);
            break;
        case 'a':
            fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            break;
        default:
            mini_free(myfile);
            return NULL;
    }

    if (fd == -1) {
        mini_free(myfile);
        return NULL;
    }

    myfile->fd = fd;
    myfile->ind_read = -1;
    myfile->ind_write = -1;
    myfile->buffer_read = NULL;
    myfile->buffer_write = NULL;
    myfile->next = open_files_list; 
    open_files_list = myfile;

    return myfile;
}

// Exercice 29 : mini_fread
int mini_fread(void* buffer, int size_element, int number_element, MYFILE* file) {
    if (buffer == NULL || file == NULL || size_element <= 0 || number_element <= 0) {
        return -1;
    }

    if (file->buffer_read == NULL) {
        file->buffer_read = mini_calloc(1, IOBUFFER_SIZE);
        if (file->buffer_read == NULL) {
            return -1;
        }
        file->ind_read = 0;
        file->buffer_read_size = 0;
    }

    int total_size = size_element * number_element;
    int bytes_read = 0;
    char* buf = (char*)buffer;

    while (bytes_read < total_size) {
        if (file->ind_read >= file->buffer_read_size) {
            int result = read(file->fd, file->buffer_read, IOBUFFER_SIZE);
            if (result <= 0) {
                return (result == 0 && bytes_read > 0) ? bytes_read / size_element : -1;
            }
            file->ind_read = 0;
            file->buffer_read_size = result;
        }

        int bytes_to_copy = total_size - bytes_read;
        int buffer_remaining = file->buffer_read_size - file->ind_read;
        int copy_size = (bytes_to_copy < buffer_remaining) ? bytes_to_copy : buffer_remaining;

        mini_memcpy(buf + bytes_read, (char*)file->buffer_read + file->ind_read, copy_size);
        file->ind_read += copy_size;
        bytes_read += copy_size;
    }

    return bytes_read / size_element;
}

// Exercice 31 : mini_fwrite
int mini_fwrite(void* buffer, int size_element, int number_element, MYFILE* file) {
    if (buffer == NULL || file == NULL || size_element <= 0 || number_element <= 0) {
        return -1;
    }

    if (file->buffer_write == NULL) {
        file->buffer_write = mini_calloc(1, IOBUFFER_SIZE);
        if (file->buffer_write == NULL) {
            return -1;
        }
        file->ind_write = 0;
    }

    int total_size = size_element * number_element;
    int bytes_written = 0;
    char* buf = (char*)buffer;

    while (bytes_written < total_size) {
        int buffer_space = IOBUFFER_SIZE - file->ind_write;
        int bytes_to_copy = total_size - bytes_written;
        int copy_size = (bytes_to_copy < buffer_space) ? bytes_to_copy : buffer_space;

        mini_memcpy((char*)file->buffer_write + file->ind_write, buf + bytes_written, copy_size);
        file->ind_write += copy_size;
        bytes_written += copy_size;

        if (file->ind_write >= IOBUFFER_SIZE) {
            int result = write(file->fd, file->buffer_write, IOBUFFER_SIZE);
            if (result <= 0) {
                return -1;
            }
            file->ind_write = 0;
        }
    }

    return bytes_written / size_element;
}

// Exercice 33 : mini_fflush
int mini_fflush(MYFILE* file) {
    if (file == NULL || file->buffer_write == NULL || file->ind_write <= 0) {
        return -1;
    }

    int result = write(file->fd, file->buffer_write, file->ind_write);
    if (result < 0) {
        return -1;
    }

    file->ind_write = 0;
    return result;
}

// Exercice 35 : mini_fclose
int mini_fclose(MYFILE* file) {
    if (file == NULL) {
        return -1;
    }

    // Vider le tampon d'écriture
    if (file->buffer_write != NULL && file->ind_write > 0) {
        if (mini_fflush(file) == -1) {
            return -1;
        }
    }

    // Retirer le fichier de la liste des fichiers ouverts
    if (open_files_list == file) {
        open_files_list = file->next;
    } else {
        MYFILE* prev = open_files_list;
        while (prev != NULL && prev->next != file) {
            prev = prev->next;
        }
        if (prev != NULL) {
            prev->next = file->next;
        }
    }

    // Fermer le descripteur de fichier
    if (close(file->fd) == -1) {
        return -1;
    }

    // Libérer les tampons et la structure MYFILE
    if (file->buffer_read != NULL) {
        mini_free(file->buffer_read);
    }
    if (file->buffer_write != NULL) {
        mini_free(file->buffer_write);
    }
    mini_free(file);

    return 0;
}

// Exercice 36 : mini_fgetc
int mini_fgetc(MYFILE* file) {
    if (file == NULL) {
        return -1;
    }

    if (file->buffer_read == NULL) {
        file->buffer_read = mini_calloc(1, IOBUFFER_SIZE);
        if (file->buffer_read == NULL) {
            return -1;
        }
        file->ind_read = 0;
        file->buffer_read_size = 0;
    }

    if (file->ind_read >= file->buffer_read_size) {
        int bytes_read = read(file->fd, file->buffer_read, IOBUFFER_SIZE);
        if (bytes_read <= 0) {
            return -1; // Fin du fichier ou erreur
        }
        file->ind_read = 0;
        file->buffer_read_size = bytes_read;
    }

    return ((unsigned char*)file->buffer_read)[file->ind_read++];
}

// Exercice 37 : mini_fputc corrigée
int mini_fputc(MYFILE* file, char c) {
    if (file == NULL) {
        return -1;
    }

    if (file->buffer_write == NULL) {
        file->buffer_write = mini_calloc(1, IOBUFFER_SIZE);
        if (file->buffer_write == NULL) {
            return -1;
        }
        file->ind_write = 0;
    }

    ((char*)file->buffer_write)[file->ind_write++] = c;

    if (file->ind_write >= IOBUFFER_SIZE) {
        int result = write(file->fd, file->buffer_write, IOBUFFER_SIZE);
        if (result <= 0) {
            return -1;
        }
        file->ind_write = 0;
    }

    return (unsigned char)c;
}

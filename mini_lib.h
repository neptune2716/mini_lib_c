#ifndef MINI_LIB_H
#define MINI_LIB_H

#include <unistd.h>
#include <stddef.h>

//exo 7
typedef struct MYFILE {
    int fd;
    void *buffer_read;
    void *buffer_write;
    int ind_read;
    int ind_write;
    int buffer_read_size;
    struct MYFILE* next;
} MYFILE;

//exo 7
typedef struct malloc_element {
    void* ptr;
    size_t size;
    int status;
    struct malloc_element* next_malloc;
} malloc_element;

// Exercice 14 : Prototypes des fonctions

// Exercice 4,5,9,11 : mini_calloc
void* mini_calloc(size_t size_element, size_t number_element);

// Exercice 10 : mini_free
void mini_free(void* ptr);

// Exercice 13 : mini_exit
void mini_exit();

// Exercice 16 : mini_printf corrigée
void mini_printf(char* str);

// Exercice 19 : mini_scanf
int mini_scanf(char* buffer, int size_buffer);

// Exercice 24 : Fonctions de chaînes
int mini_strlen(char* s);
int mini_strcpy(char* s, char* d, size_t d_size);
int mini_strcmp(char* s1, char* s2);
int mini_strstr(char* haystack, char* needle);
void mini_perror(char* message);

//exo 42
int mini_strcat(char* dest, const char* src, int dest_size);

// Fonctions utilitaires
void mini_memset(void* s, int c, size_t n);
void mini_memcpy(void* dest, const void* src, size_t n);
ssize_t mini_write(int fd, const void* buf, size_t count);

// Opérations sur les fichiers
MYFILE* mini_fopen(char* file, char mode);

// Exercice 29 : mini_fread
int mini_fread(void* buffer, int size_element, int number_element, MYFILE* file);

// Exercice 31 : mini_fwrite
int mini_fwrite(void* buffer, int size_element, int number_element, MYFILE* file);

// Exercice 33 : mini_fflush
int mini_fflush(MYFILE* file);

// Exercice 35 : mini_fclose
int mini_fclose(MYFILE* file);

// Exercice 36 : mini_fgetc
int mini_fgetc(MYFILE* file);

// Exercice 37 : mini_fputc 
int mini_fputc(MYFILE* file, char c);

// Fonction d'initialisation
void initialize_mini_io();

// Exercice 34 : Variables globales
extern MYFILE* open_files_list;
extern MYFILE* mini_stdout;

// Exercice 15 
#define BUF_SIZE 1024

int mini_touch(char* file);

//exo 40
void mini_itoa(int num, char* str);
int mini_atoi(char* str);
char* mini_fgets(char* buffer, int size, MYFILE* file);

#define EOF -1
//exo 41
void execute_command(char* line);
void load_config();

#endif // MINI_LIB_H


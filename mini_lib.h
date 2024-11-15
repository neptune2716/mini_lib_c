// mini_lib.h
#ifndef MINI_LIB_H
#define MINI_LIB_H

#include <unistd.h>
#include <stddef.h>

// Définition de la structure MYFILE
/**
 * @struct MYFILE
 * @brief Represents a file structure for buffered I/O operations.
 *
 * The MYFILE structure maintains separate read and write buffers along with their indices,
 * and keeps track of the file descriptor. It also includes a pointer to the next MYFILE
 * structure, allowing the creation of a linked list of file structures.
 *
 * @var int MYFILE::fd
 * File descriptor associated with the file.
 *
 * @var void* MYFILE::buffer_read
 * Pointer to the read buffer.
 *
 * @var void* MYFILE::buffer_write
 * Pointer to the write buffer.
 *
 * @var int MYFILE::ind_read
 * Current index in the read buffer.
 *
 * @var int MYFILE::ind_write
 * Current index in the write buffer.
 *
 * @var int MYFILE::buffer_read_size
 * Size of the read buffer.
 *
 * @var struct MYFILE* MYFILE::next
 * Pointer to the next MYFILE structure in a linked list.
 */
typedef struct MYFILE {
    int fd;
    void *buffer_read;
    void *buffer_write;
    int ind_read;
    int ind_write;
    int buffer_read_size;
    struct MYFILE* next;
} MYFILE;

// Exercice 7 : Structure malloc_element
typedef struct malloc_element {
    void* ptr;
    size_t size;
    int status;
    struct malloc_element* next_malloc;
} malloc_element;

// Exercice 14 : Prototypes des fonctions

// Exercice 4,5,9,11 : mini_calloc
/**
 * @brief Allocates memory for an array of elements and initializes them to zero.
 *
 * @param size_element Size of each element.
 * @param number_element Number of elements.
 * @return Pointer to the allocated memory.
 */
void* mini_calloc(size_t size_element, size_t number_element);

// Exercice 10 : mini_free
/**
 * @brief Frees the allocated memory.
 *
 * @param ptr Pointer to the memory to be freed.
 */
void mini_free(void* ptr);

// Exercice 13 : mini_exit
/**
 * @brief Exits the program after performing cleanup.
 */
void mini_exit();

// Exercice 16 : mini_printf corrigée
/**
 * @brief Prints a formatted string to the standard output.
 *
 * @param str The string to be printed.
 */
void mini_printf(char* str);

// Exercice 19 : mini_scanf
/**
 * @brief Reads formatted input from the standard input.
 *
 * @param buffer Buffer to store the input.
 * @param size_buffer Size of the buffer.
 * @return Number of items successfully read.
 */
int mini_scanf(char* buffer, int size_buffer);

// Exercice 24 : Fonctions de chaînes
/**
 * @brief Calculates the length of a string.
 *
 * @param s The string.
 * @return Length of the string.
 */
int mini_strlen(char* s);

/**
 * @brief Copies a string to a destination buffer.
 *
 * @param s Source string.
 * @param d Destination buffer.
 * @param d_size Size of the destination buffer.
 * @return Number of characters copied.
 */
int mini_strcpy(char* s, char* d, size_t d_size);

/**
 * @brief Compares two strings.
 *
 * @param s1 First string.
 * @param s2 Second string.
 * @return An integer less than, equal to, or greater than zero if s1 is found,
 *         respectively, to be less than, to match, or be greater than s2.
 */
int mini_strcmp(char* s1, char* s2);

/**
 * @brief Finds the first occurrence of the substring needle in the string haystack.
 *
 * @param haystack The string to be searched.
 * @param needle The substring to search for.
 * @return A pointer to the beginning of the located substring, or NULL if the substring is not found.
 */
int mini_strstr(char* haystack, char* needle);

/**
 * @brief Prints an error message to the standard error.
 *
 * @param message The error message.
 */
void mini_perror(char* message);

// Fonctions utilitaires
/**
 * @brief Sets a block of memory to a specific value.
 *
 * @param s Pointer to the memory block.
 * @param c The value to set.
 * @param n Number of bytes to set.
 */
void mini_memset(void* s, int c, size_t n);

/**
 * @brief Copies a block of memory from source to destination.
 *
 * @param dest Destination buffer.
 * @param src Source buffer.
 * @param n Number of bytes to copy.
 */
void mini_memcpy(void* dest, const void* src, size_t n);

/**
 * @brief Writes data to a file descriptor.
 *
 * @param fd File descriptor.
 * @param buf Buffer containing the data to write.
 * @param count Number of bytes to write.
 * @return Number of bytes written.
 */
ssize_t mini_write(int fd, const void* buf, size_t count);

// Opérations sur les fichiers
/**
 * @brief Opens a file with the specified mode.
 *
 * @param file The name of the file.
 * @param mode The mode to open the file ('r', 'w', etc.).
 * @return Pointer to the MYFILE structure.
 */
MYFILE* mini_fopen(char* file, char mode);

// Exercice 29 : mini_fread
/**
 * @brief Reads data from a file into a buffer.
 *
 * @param buffer Buffer to store the read data.
 * @param size_element Size of each element.
 * @param number_element Number of elements to read.
 * @param file Pointer to the MYFILE structure.
 * @return Number of elements successfully read.
 */
int mini_fread(void* buffer, int size_element, int number_element, MYFILE* file);

// Exercice 31 : mini_fwrite
/**
 * @brief Writes data from a buffer to a file.
 *
 * @param buffer Buffer containing the data to write.
 * @param size_element Size of each element.
 * @param number_element Number of elements to write.
 * @param file Pointer to the MYFILE structure.
 * @return Number of elements successfully written.
 */
int mini_fwrite(void* buffer, int size_element, int number_element, MYFILE* file);

// Exercice 33 : mini_fflush
/**
 * @brief Flushes the output buffer of a file.
 *
 * @param file Pointer to the MYFILE structure.
 * @return Zero on success, EOF on error.
 */
int mini_fflush(MYFILE* file);

// Exercice 35 : mini_fclose
/**
 * @brief Closes a file and releases associated resources.
 *
 * @param file Pointer to the MYFILE structure.
 * @return Zero on success, EOF on error.
 */
int mini_fclose(MYFILE* file);

// Exercice 36 : mini_fgetc
/**
 * @brief Retrieves the next character from a file.
 *
 * @param file Pointer to the MYFILE structure.
 * @return The next character as an integer, or EOF on end of file or error.
 */
int mini_fgetc(MYFILE* file);

// Exercice 37 : mini_fputc corrigée
/**
 * @brief Writes a character to a file.
 *
 * @param file Pointer to the MYFILE structure.
 * @param c The character to write.
 * @return The character written as an unsigned char cast to an int or EOF on error.
 */
int mini_fputc(MYFILE* file, char c);

// Fonction d'initialisation
/**
 * @brief Initializes the mini I/O system.
 */
void initialize_mini_io();

// Exercice 34 : Variables globales
extern MYFILE* open_files_list;
extern MYFILE* mini_stdout;

// Exercice 15 : Taille du tampon pour mini_printf
#define BUF_SIZE 1024

/**
 * @brief Creates an empty file if it does not exist.
 *
 * @param file The name of the file to create.
 * @return 0 on success, -1 if the file already exists or on error.
 */
int mini_touch(char* file);

//exo 40
void mini_itoa(int num, char* str);

/**
 * @brief Converts a string to an integer.
 *
 * @param str The string to convert.
 * @return The resulting integer.
 */
int mini_atoi(char* str);

#endif // MINI_LIB_H

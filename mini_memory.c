//exo 40
#include "mini_lib.h"
#include <unistd.h>
#include <stddef.h>
#include <stdint.h>
#include <errno.h>

// Exercice 8 
malloc_element* malloc_list = NULL;

void mini_memset(void* s, int c, size_t n) {
    unsigned char* p = s;
    for (size_t i = 0; i < n; i++) {
        p[i] = (unsigned char)c;
    }
}

void mini_memcpy(void* dest, const void* src, size_t n) {
    unsigned char* d = dest;
    const unsigned char* s = src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

// Exercice 5,9,11,14,15 
void* mini_calloc(size_t size_element, size_t number_element) {
    if (size_element == 0 || number_element == 0) {
        errno = EINVAL;
        return NULL;
    }

    if (size_element > SIZE_MAX / number_element) {
        errno = ENOMEM;
        return NULL;
    }

    size_t total_size = size_element * number_element;
    malloc_element* current = malloc_list;

    while (current != NULL) {
        if (current->status == 0 && current->size >= total_size) {
            current->status = 1;
            mini_memset(current->ptr, 0, current->size);
            return current->ptr;
        }
        current = current->next_malloc;
    }

    void* ptr = sbrk(total_size);
    if (ptr == (void*)-1) {
        errno = ENOMEM;
        return NULL;
    }

    mini_memset(ptr, 0, total_size);

    malloc_element* new_element = sbrk(sizeof(malloc_element));
    if (new_element == (void*)-1) {
        errno = ENOMEM;
        return NULL;
    }

    new_element->ptr = ptr;
    new_element->size = total_size;
    new_element->status = 1;
    new_element->next_malloc = NULL;

    if (malloc_list == NULL) {
        malloc_list = new_element;
    } else {
        current = malloc_list;
        while (current->next_malloc != NULL) {
            current = current->next_malloc;
        }
        current->next_malloc = new_element;
    }

    return ptr;
}

// Exercice 10 
void mini_free(void* ptr) {
    if (ptr == NULL) {
        return;
    }

    malloc_element* current = malloc_list;
    while (current != NULL) {
        if (current->ptr == ptr) {
            current->status = 0;
            return;
        }
        current = current->next_malloc;
    }
}

// Exercice 13,18 
void flush_buffer() {
    extern char* buffer;
    extern int ind;
    if (buffer != NULL && ind > 0) {
        write(1, buffer, ind);
        ind = 0;
    }
}

void mini_exit() {
    // Exercice 34 
    MYFILE* courant = open_files_list;
    while (courant != NULL) {
        if (courant->buffer_write != NULL && courant->ind_write > 0) {
            mini_fflush(courant);
        }
        courant = courant->next;
    }
    flush_buffer(); 
    _exit(0);
}

#include "mini_lib.h"
#include <unistd.h>
#include <stddef.h>
#include <errno.h>

//exo 15
char* buffer = NULL;
int ind = -1;

ssize_t mini_write(int fd, const void* buf, size_t count) {
    return write(fd, buf, count);
}

//exo 16
void mini_printf(char* str) {
    if (str == NULL) {
        return;
    }

    if (buffer == NULL) {
        buffer = mini_calloc(BUF_SIZE, sizeof(char));
        if (buffer == NULL) {
            return;
        }
        ind = 0;
    }

    int i = 0;
    while (str[i] != '\0') {
        buffer[ind++] = str[i];
        if (ind == BUF_SIZE || str[i] == '\n') {
            mini_write(1, buffer, ind);
            ind = 0;
        }
        i++;
    }
}

//exo 19,20
int mini_scanf(char* buf, int size_buffer) {
    if (buf == NULL || size_buffer <= 0) {
        return -1;
    }

    int bytes_read = read(0, buf, size_buffer - 1);
    if (bytes_read < 0) {
        return -1; 
    }

    if (bytes_read < size_buffer - 1) {
        buf[bytes_read] = '\0';
    } else {
        buf[size_buffer - 1] = '\0';
        char last_char = buf[size_buffer - 2];
        if (last_char != '\n') {
            char discard;
            while (read(0, &discard, 1) == 1 && discard != '\n');
        }
    }

    return bytes_read;
}
//exo 21,22
int mini_strlen(char* s) {
    if (s == NULL) {
        return 0;
    }
    int length = 0;
    while (s[length] != '\0') {
        length++;
    }
    return length;
}

int mini_strcpy(char* s, char* d, size_t d_size) {
    if (s == NULL || d == NULL) {
        return -1;
    }
    size_t count = 0;
    while (s[count] != '\0') {
        if (count >= d_size - 1) {
            d[count] = '\0';
            return (int)count;
        }
        d[count] = s[count];
        count++;
    }
    d[count] = '\0';
    return (int)count;
}

int mini_strcmp(char* s1, char* s2) {
    if (s1 == NULL && s2 == NULL) {
        return 0;
    }
    if (s1 == NULL) {
        return -1;
    }
    if (s2 == NULL) {
        return 1;
    }
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return (unsigned char)s1[i] - (unsigned char)s2[i];
        }
        i++;
    }
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}

//exo 23
void mini_perror(char* message) {
    if (message != NULL) {
        mini_write(2, message, mini_strlen(message));
        mini_write(2, ": ", 2);
    }
    char* error_message = NULL;
    switch(errno) {
        case EACCES:
            error_message = "Permission denied";
            break;
        case EEXIST:
            error_message = "File exists";
            break;
        case EINVAL:
            error_message = "Invalid argument";
            break;
        case ENOENT:
            error_message = "No such file or directory";
            break;
        case ENOMEM:
            error_message = "Out of memory";
            break;
        case EBADF:
            error_message = "Bad file descriptor";
            break;
        case EAGAIN:
            error_message = "Try again";
            break;
        case EINTR:
            error_message = "Interrupted system call";
            break;
        case EIO:
            error_message = "I/O error";
            break;
        default:
            error_message = "Unknown error";
            break;
    }
    mini_write(2, error_message, mini_strlen(error_message));
    mini_write(2, "\n", 1);
}

//exo 40
void mini_itoa(int num, char* str) {
    int i = 0, is_negative = 0;
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    while (num != 0) {
        int rem = num % 10;
        str[i++] = rem + '0';
        num /= 10;
    }
    if (is_negative) {
        str[i++] = '-';
    }
    str[i] = '\0';

    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

int mini_atoi(char* str) {
    int result = 0;
    int sign = 1;
    int i = 0;
    while (str[i] == ' ') {
        i++;
    }
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return sign * result;
}

//exo 42
int mini_strcat(char* dest, const char* src, int dest_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return -1;
    }

    int dest_len = mini_strlen(dest);
    int src_len = mini_strlen((char*)src);

    if (dest_len + src_len >= dest_size) {
        // Pas assez d'espace dans le buffer de destination
        return -1;
    }

    for (int i = 0; i < src_len; i++) {
        dest[dest_len + i] = src[i];
    }
    dest[dest_len + src_len] = '\0';

    return src_len;
}

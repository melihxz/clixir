#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// Safe memory allocation
void* safe_malloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

// Safe memory deallocation
void safe_free(void* ptr) {
    if (ptr) {
        free(ptr);
    }
}

// Trim leading and trailing whitespace from a string
char* trim_whitespace(const char* str) {
    while (isspace((unsigned char)*str)) str++;
    if (*str == '\0') return strdup("");

    const char* end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    size_t length = end - str + 1;
    char* trimmed_str = (char*)safe_malloc(length + 1);
    strncpy(trimmed_str, str, length);
    trimmed_str[length] = '\0';
    return trimmed_str;
}

// Concatenate two strings
char* concat_strings(const char* str1, const char* str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char* result = (char*)safe_malloc(len1 + len2 + 1);
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

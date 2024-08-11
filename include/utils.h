#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

// Memory management functions
void* safe_malloc(size_t size);
void safe_free(void* ptr);

// String manipulation functions
char* trim_whitespace(const char* str);
char* concat_strings(const char* str1, const char* str2);

#endif // UTILS_H

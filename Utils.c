#include "scinstdlib.h"
#include <stdio.h>
#include <stdlib.h>

char* readFile(const char* path) {
    FILE* f = fopen(path, "r");
    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if (buffer == NULL) return NULL;

    size_t status = fread(buffer, 1, length, f);
    if (ferror(f)) return NULL;
    fclose(f);

    buffer[length] = 0;

    return buffer;
}

int isAlpha(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
}

int isNumber(char ch) {
    return (ch >= '0' && ch <= '9');
}

int isAlphaNumerical(char ch) {
    return isAlpha(ch) | isNumber(ch);
}

char* stringify_char_array(struct Array* arr) {
    char* ret = (char*)malloc(arr->length + 1);
    for (int i = 0; i < arr->length; i++) ret[i] = GET_ELEMENT_FROM_ARRAY(arr, char, i);
    ret[arr->length] = 0;
    return ret;
}

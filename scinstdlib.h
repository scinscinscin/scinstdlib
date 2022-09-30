#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct Array {
    size_t length;
    size_t capacity;
    // the items array contains pointers to the actual elements
    void** items;
};

struct Array* CreateArray();
void AddElementToArray(struct Array* arr, void* newElement);
void* GetElementFromArray(struct Array* arr, size_t index);
void* PopElementFromArray(struct Array* arr);
void FreeArray(struct Array* arr);

#define ADD_ELEMENT_TO_ARRAY(arr, type, number) \
    { \
        type* temp = (type*) calloc(1, sizeof(type)); \
        *temp = number; \
        AddElementToArray(arr, temp); \
    }
#define POP_ELEMENT_FROM_ARRAY(arr, type)\
    *(type *) PopElementFromArray(arr)
#define GET_ELEMENT_FROM_ARRAY(arr, type, n) \
    *(type *) GetElementFromArray(arr, n)

struct Entry {
    uint32_t hash;
    const char* key;
    void* val;
};

struct Hashmap {
    int length;
    int capacity;
    struct Entry** entries;
};

struct Hashmap* CreateHashmap();
void addItemToHashmap(struct Hashmap* map, const char* key, void* val);
void* getItemFromHashmap(struct Hashmap* map, const char* key);
int isKeyInHashmap(struct Hashmap* map, const char* key);

#define ADD_ELEMENT_TO_HASHMAP(map, key, type, item) \
    { \
        type *temp = (type*) malloc(sizeof(type)); \
        *temp = item; \
        addItemToHashmap(map, key, temp); \
    }

#define GET_ELEMENT_FROM_HASHMAP(map, key, type) \
    *(type *) getItemFromHashmap(map, key)

char* readFile(const char* path);
int isAlpha(char ch);
int isNumber(char ch);
int isAlphaNumerical(char ch);

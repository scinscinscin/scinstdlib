#pragma once
#include<stdio.h>
#include <stdlib.h>

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

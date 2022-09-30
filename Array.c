#include "Array.h"
#define GROW_CAPACITY(cap) \
    cap < 8 ? 8 : cap * 2

struct Array* CreateArray() {
    struct Array* ret = (struct Array*)malloc(sizeof(struct Array));
    if (ret != NULL) {
        ret->length = 0;
        ret->capacity = 0;
        ret->items = NULL;
    }

    return ret;
}

void AddElementToArray(struct Array* arr, void* newElement) {
    if (arr->length >= arr->capacity) {
        // the number of items in the array matches the number it can take so it has to be grown
        size_t newCapacity = GROW_CAPACITY(arr->capacity);
        arr->capacity = newCapacity;
        if (arr->items == NULL)
            arr->items = (void**)malloc(arr->capacity * sizeof(void*));
        else
            arr->items = (void**)realloc(arr->items, arr->capacity * sizeof(void*));
    }

    (arr->items)[arr->length++] = newElement;
}

void* GetElementFromArray(struct Array* arr, size_t index) {
    if (index >= arr->length) return NULL;
    return (arr->items)[index];
}

void* PopElementFromArray(struct Array* arr){
    if (arr->length == 0) return NULL;
    void* item = GetElementFromArray(arr, arr->length - 1);
    arr->length--;
    return item;
}

void FreeArray(struct Array* arr) {
    // free every item inside of arr->items
    for (int i = 0; i < arr->length; i++) free(arr->items[i]);
    free(arr->items);

    arr->capacity = 0;
    arr->length = 0;
}

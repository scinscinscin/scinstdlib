#pragma once
#include <stdint.h>

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

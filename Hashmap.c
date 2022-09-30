#include "scinstdlib.h"
#include <stdlib.h>
#include <string.h>

#define HASHMAP_LOAD_FACTOR 0.90
#define HASHMAP_STARTING_CAPACITY 16

static uint32_t hashString(const char* key) {
    uint32_t hash = 2166136261u;
    for (int i = 0; i < strlen(key); i++) {
        hash ^= (uint8_t)key[i];
        hash *= 16777619;
    }

    return hash;
}

struct Hashmap* CreateHashmap() {
    struct Hashmap* ret = (struct Hashmap*)malloc(sizeof(struct Hashmap));
    ret->capacity = HASHMAP_STARTING_CAPACITY;
    ret->length = 0;
    ret->entries = (struct Entry**)calloc(HASHMAP_STARTING_CAPACITY, sizeof(struct Entry*));
    return ret;
}

// finds where an entry can be placed in an array of entries
int findIndex(struct Entry** entries, struct Entry* entry, int capacity) {
    int rawIndex = entry->hash % capacity;

    while (entries[rawIndex] != NULL) {
        rawIndex = (rawIndex + 1) % capacity;
    }

    return rawIndex;
}

void addItemToHashmap(struct Hashmap* map, const char* key, void* val) {
    if (map->entries == NULL || map->capacity == 0) return;

    if ((map->length + 1) / (double)map->capacity > HASHMAP_LOAD_FACTOR) {
        // create a new entry list
        int newCapacity = map->capacity * 2;
        struct Entry** entries = (struct Entry**)calloc(newCapacity, sizeof(struct Entry*));

        // fill the new entries
        for (int i = 0; i < map->capacity; i++) {
            struct Entry* entry = map->entries[i];
            if (entry == NULL) continue;

            // calculate the new index of where to put the entry
            int index = findIndex(entries, entry, newCapacity);
            entries[index] = entry;
        }

        map->capacity = newCapacity;
        map->entries = entries;
    }

    struct Entry* newEntry = (struct Entry*)malloc(sizeof(struct Entry));
    *newEntry = (struct Entry) { .hash = hashString(key), .key = key, .val = val };
    
    int index = findIndex(map->entries, newEntry, map->capacity);
    map->entries[index] = newEntry;
    map->length++;
}

void* getItemFromHashmap(struct Hashmap* map, const char* key) {
    uint32_t index = hashString(key);

    for (uint32_t i = index; i < index + (uint32_t)map->capacity; i++) {
        struct Entry* entry = map->entries[i % map->capacity];
        if (entry == NULL) break;
        if (!strcmp(entry->key, key)) return entry->val;
        else continue;
    }
    return NULL;
}

// checks if a key is in a hashmap, returns 1 if true, 0 if false
int isKeyInHashmap(struct Hashmap* map, const char* key) {
    uint32_t index = hashString(key);

    for (uint32_t i = index; i < index + (uint32_t)map->capacity; i++) {
        struct Entry* entry = map->entries[i % map->capacity];
        if (entry == NULL) break;
        if (!strcmp(entry->key, key)) return 1;
        else continue;
    }

    return 0;
}

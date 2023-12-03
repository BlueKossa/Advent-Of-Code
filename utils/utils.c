#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_file(char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* buffer = malloc(length + 1);
    if (buffer) {
        fread(buffer, 1, length, file);
    }
    fclose(file);
    return buffer;
}

typedef struct Vector {
    size_t element_size;
    size_t length;
    size_t capacity;
    void* data;
} Vec;

Vec* vec_new(size_t element_size) {
    Vec* vec = malloc(sizeof(Vec));
    vec->element_size = element_size;
    vec->length = 0;
    vec->capacity = 0;
    vec->data = NULL;
    return vec;
}

void vec_push(Vec* vec, void* element) {
    if (vec->length == vec->capacity) {
        vec->capacity = vec->capacity == 0 ? 1 : vec->capacity * 2;
        vec->data = realloc(vec->data, vec->capacity * vec->element_size);
    }
    memcpy(vec->data + vec->length * vec->element_size, element, vec->element_size);
    vec->length++;
}

void vec_get(Vec* vec, size_t index, void* element) {
    memcpy(element, vec->data + index * vec->element_size, vec->element_size);
}

void vec_free(Vec* vec) {
    free(vec->data);
    free(vec);
}

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_CAPACITY 10

typedef struct {
  int size, capacity;
  int* storage;
} IntVector;

void* new_int_vector() {
  IntVector* res = malloc(sizeof(IntVector));

  res->size = 0;
  res->capacity = DEFAULT_CAPACITY;

  // initialise storage
  int* storage = malloc(sizeof(int) * DEFAULT_CAPACITY);
  res->storage = storage;
  
  return res;
}

int size(IntVector* vector) {
  return vector->size;
}

void resize(IntVector* vector, int new_size) {
  int* old_storage = vector->storage;
  int* new_storage = malloc(sizeof(int) * new_size);
  
  for (int i = 0; i < vector->size; i++) {
    printf("old num: %d\n", old_storage[i]);
    new_storage[i] = old_storage[i];
  }

  // prevent memory leak
  free(old_storage);

  vector->capacity = new_size;
  vector->storage = new_storage;
}

void insert(IntVector* vector, int value) {
  int size = vector->size;
  int capacity = vector->capacity;

  // if the size is more than capacity then just resize array
  if (size > capacity || size+1 > capacity) {
    printf("%s", "capacity exceeded, resizing vector\n");
    resize(vector, capacity * 2);
  }

  int* storage = vector->storage;
  storage[size] = value;
  
  vector->size += 1;
}

int get(IntVector* vector, int index) {
  if (index > vector->capacity) return -1;

  int* storage = vector->storage;
  return storage[index];
}

int main() {
  IntVector* vector = new_int_vector();

  int limit = 15;

  for (int i = 0; i < limit; ++i) {
    insert(vector, i);
  }

  for (int i = 0; i < limit; ++i) {
    printf("num: %d\n", get(vector, i));
  }

  free(vector);
  return 1;
}

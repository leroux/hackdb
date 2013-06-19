#include "alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void *create_pool(size_t item, unsigned int blocksize) {
  void *pool = malloc(item * blocksize);

  if (!pool)
    perror(NULL);

  init_pool(

  return pool;
}

void *alloc_from_pool(unsigned int itemsize, unsigned int blocksize) {
  void *head;
  unsigned int i = 0;

  head = malloc(BLOCK_SIZE * sizeof(hdb_record));

  if (!head) {
    error("Failed to allocate memory for block.");
    return NULL;
  }

  // Initialize head: previous set to NULL and next to next node.
  head->previous = NULL;
  head->next = head + 1;

  // Initialize tail - last of list.
  for (i = 1; i < size - 1; i++) {
    (head + i)->previous = head - i;
    (head + i)->next = head + i;
  }

  // Initialize last: next set to NULL.
  (head + i + 1)->previous = (head + i);
  (head + i + 1)->next = NULL;

  return head;
}

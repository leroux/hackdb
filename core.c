#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

hdb_t *hdb_create(void) {
  hdb_t *db = malloc(sizeof(hdb_t));
  db->head = db->last = hdb_alloc_and_init(BLOCK_SIZE);

  if (!db)
    error("Could not allocate memory for database");

  return db;
}

hdb_record *hdb_alloc_and_init(unsigned int size) {
  hdb_record *head;
  unsigned int i = 0;

  head = malloc(BLOCK_SIZE * sizeof(hdb_record));

  if (!head) {
    error("Failed to allocate memory for block.");
    return NULL;
  }

  head->previous = NULL;
  head->next = head + 1;

  for (i = 1; i < size - 1; i++) {
    (head + i)->previous = head - i;
    (head + i)->next = head + i;
  }

  (head + i + 1)->previous = (head + i);
  (head + i + 1)->next = NULL;

  return head;
}

int hdb_insert_after(hdb_record *insert_after, const char *key, const char *value) {

}

int error(const char *msg) {
  if (errno) {
    perror(msg);
  } else {
    printf("Error: %s\n", msg);
  }

  return -1;
}

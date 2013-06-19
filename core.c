#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

hdb_t *hdb_create(void) {
  hdb_t *db = malloc(sizeof(hdb_t));

  if (!db)
    error("Could not allocate memory for database");

  db->head = db->last = hdb_alloc_and_init(BLOCKSIZE);

  return db;
}

hdb_record *hdb_alloc_and_init(unsigned int blocksize) {
  hdb_record *head; 
  hdb_record *current = NULL;
  int i = 0;

  head = malloc(sizeof(hdb_record) * blocksize);

  if(!head)
    error("Could not allocate memory for list block");

  head->previous = NULL;
  head->next = current = (head + 1);

  for (i = 1; i < BLOCKSIZE - 1; i++) {
    (current + i)->previous = current - 1;
    (current + i)->next = current + 1;
  }

  (current + i + 1)->previous = current - 1;
  (current + i + 1)->next = NULL;
  
  return head;
}

int hdb_set(hdb_t *db, const char *key, const char *value) {
  hdb_record *previous = NULL;
  hdb_record *current = db->head;
  hdb_record *existing_record = NULL;
  hdb_record *new = NULL;

  // If at the end of currently allocated list, grow the list.
  if (!db->last->next)
    db->last->next = hdb_alloc_and_init(BLOCKSIZE); 

  // If list is empty, set head and move last.
  // db->last is a reference to the next allocated node to use.
  // Therefore db->last must be incremented whenever it is used.
  if (db->head == db->last) {
    db->head->key = strdup(key);
    db->head->value = strdup(value); 
    db->last++; // must increment to next free spot.

    return 0;
  }

  // If record exists, update existing record with new value.
  if ((existing_record = hdb_get(db, key))) {
    return hdb_update(existing_record, value);
  }

  // Traverse until current is greater than the new record's key.
  while (current != db->last && strcmp(current->key, key) <= 0) {
    previous = current;
    current = current->next;
  }

  // new record; db->last is incremented to next free position.
  new = db->last++;

  if (!previous) { // prepend: new record will become the head.
    new = db->last++; // must increment last to next free spot.
    new->key = strdup(key);
    new->value = strdup(value);

    // provision new to become head (head->previous must == NULL).
    new->previous = NULL;
    new->next = db->head;

    // prepend new to list.
    db->head->previous = new;
    db->head = new;
  } else { // insert new after previous.
    new->previous = previous;
    new->next = previous->next;
    previous->next = new;
    new->next->previous = new;
  }

  return 0;
}

hdb_record *hdb_get(hdb_t *db, const char *key) {
  hdb_record *current = db->head;

  while (current != db->last) {
    if (strcmp(current->key, key) == 0)
      return current;

    current = current->next;
  }

  return NULL; // Traversed the entire list and didn't find a matching key.
}

int hdb_update(hdb_record *record, const char *value) {
  if (!record)
    return error("Referenced record does not exist.");

  record->value = strdup(value);

  return 0;
}

int hdb_del(hdb_t *db, hdb_record *record) {
  if (!db)
    return error("Referenced database does not exist.");
  else if (!db->head)
    return error("Empty database.");
  else if (!record)
    return error("Referenced record does not exist.");

  if (record == db->head) {
    db->head = db->head->next;
    if (db->head)
      db->head->previous = NULL;
    free(record); // record is the old db->head.
  } else {
    record->previous->next = record->next;
    free(record);
  }

  return 0;
}

int hdb_destroy(hdb_t *db) {
  hdb_record *current = db->head;

  if (!db)
    return error("Referenced database does not exist.");

  while (!current) {
    free(current->previous);
    current = current->next;
  }

  free(db);

  return 0;
}

void hdb_list_contents(hdb_t *db) {
  hdb_record *current = db->head;

  while (current != db->last) {
    printf("%s => \"%s\"\n", current->key, current->value);
    current = current->next;
  }
}

unsigned int hdb_count(hdb_t *db) {
  int count = 0;
  hdb_record *current = db->head;

  if (!current)
    return 0;

  while (current) {
    count++;
    current = current->next;
  }

  return count;
}

int error(const char *msg) {
  if (errno)
    perror(msg);
  else
    printf("Error: %s\n", msg);

  return -1;
}

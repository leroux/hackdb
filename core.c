#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

hdb_t *hdb_create(void) {
  hdb_t *db = malloc(sizeof(hdb_t));
  db->head = NULL;
  return db;
}

hdb_record *hdb_record_create(char *key, char *value, hdb_record *next) {
  hdb_record *record = malloc(sizeof(hdb_record));
  record->key = strdup(key);
  record->value = strdup(value);
  record->next = next;

  return record;
}

int hdb_add(hdb_t *db, char *key, char *value) {
  hdb_record *previous = NULL;
  hdb_record *current = db->head;

  if (db->head == NULL) {
    db->head = hdb_record_create(key, value, NULL);
    return 0;
  }

  // Traverse until current is greater than the new record's key.
  while (current != NULL && strcmp(current->key, key) <= 0) {
    previous = current;
    current = current->next;
  }

  // Insert new record after previous.
  previous->next = hdb_record_create(key, value, previous->next);

  return 0;
}

int hdb_del(hdb_t *db, char *key) {
  hdb_record *previous2 = NULL;
  hdb_record *previous = NULL;
  hdb_record *current = db->head;

  if(hdb_count(db) == 0) return -1;

  // If head is a matching key, shift db->head to its next.
  // else shift references to the next block.
  if (strcmp(db->head->key, key) == 0) {
    previous = db->head;
    current = current->next;
    db->head = current;
    free(previous);
    return 0;
  } else {
    previous2 = previous;
    previous = current;
    current = current->next;
  }

  while (current != NULL) {
    previous2 = previous;
    previous = current;
    current = current->next;

    if (strcmp(previous->key, key) == 0) {
      previous2->next = current; 
      return 0;
    }
  }

  return -1; // matching key not found.
}

char *hdb_get(hdb_t *db, char *key) {
  hdb_record *previous = NULL;
  hdb_record *current = db->head;

  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      return current->value;
    }

    previous = current;
    current = current->next;
  }

  return NULL; // Traversed the entire list and didn't find a matching key.
}

void hdb_destroy(hdb_t *db) {
  hdb_record *previous = NULL;
  hdb_record *current = db->head;

  while (current != NULL) {
    previous = current;
    current = current->next;
    free(previous);
  }

  free(db);
}

void hdb_list_contents(hdb_t *db) {
  hdb_record *current = db->head;

  printf("----------------------\n");
  printf("| Key\t| Value      |\n");
  printf("----------------------\n");

  while (current != NULL) {
    printf("  %s:\t  %s\n", current->key, current->value);
    current = current->next;
  }
}

unsigned int hdb_count(hdb_t *db) {
  int count = 0;
  hdb_record *current = db->head;

  if (current == NULL) {
    return 0;
  }

  while (current != NULL) {
    count++;
    current = current->next;
  }

  return count;
}

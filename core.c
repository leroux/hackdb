#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

hdb_t *hdb_create(void) {
  hdb_t *db = malloc(sizeof(hdb_t));

  if (!db) {
    perror("Could not allocate memory for database");
  }

  db->head = NULL;
  return db;
}

hdb_record *hdb_record_create(const char *key, const char *value, hdb_record *previous, hdb_record *next) {
  hdb_record *record = malloc(sizeof(hdb_record));
  record->key = strdup(key);
  record->value = strdup(value);
  record->previous = previous;
  record->next = next;

  return record;
}

int hdb_set(hdb_t *db, const char *key, const char *value) {
  hdb_record *previous = NULL;
  hdb_record *current = db->head;
  hdb_record *existing_record = NULL;

  if (hdb_count(db) == 0) {
    db->head = hdb_record_create(key, value, NULL, NULL);
    return 0;
  }

  existing_record = hdb_get(db, key);

  if (existing_record)
    return hdb_update(existing_record, value);

  // Traverse until current is greater than the new record's key.
  while (current != NULL && strcmp(current->key, key) <= 0) {
    previous = current;
    current = current->next;
  }

  if (previous == NULL) {
    db->head = hdb_record_create(key, value, NULL, current); 
  } else {
    previous->next = hdb_record_create(key, value, previous, current);
  }

  return 0;
}

int hdb_update(hdb_record *record, const char *value) {
  if (!record) {
    return error("Referenced record does not exist.");
  }

  record->value = strdup(value);

  return 0;
}

int hdb_del(hdb_t *db, hdb_record *record) {
  if (!db) {
    return error("Referenced database does not exist.");
  } else if (!db->head) {
    return error("Empty database.");
  } else if (!record) {
    return error("Referenced record does not exist.");
  }

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

hdb_record *hdb_get(hdb_t *db, const char *key) {
  hdb_record *current = db->head;

  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      return current;
    }

    current = current->next;
  }

  return NULL; // Traversed the entire list and didn't find a matching key.
}

int hdb_destroy(hdb_t *db) {
  hdb_record *current = db->head;

  if (!db) {
    
  }

  while (current != NULL) {
    free(current->previous);
    current = current->next;
  }

  free(db);

  return 0;
}

void hdb_list_contents(hdb_t *db) {
  hdb_record *current = db->head;

  while (current != NULL) {
    printf("%s => \"%s\"\n", current->key, current->value);
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

int error(const char *msg) {
  if (errno) {
    perror(msg);
  } else {
    printf("Error: %s\n", msg);
  }

  return -1;
}

#include "hackdb.h"

hdb_t *hdb_create(void) {
  hdb_t *db = malloc(sizeof(hdb_t));
  db->head = NULL;
  return db;
}

hdb_record *hdb_record_create(char *key, char *value) {
  hdb_record *record = malloc(sizeof(hdb_record));
  record->key = strdup(key);
  record->value = strdup(value);
  record->next = NULL;

  return record;
}

int hdb_add(hdb_t *db, char *key, char *value) {
  hdb_record *previous = NULL;
  hdb_record *current = db->head;

  // if db is empty construct the head.
  if (db->head == NULL) {
    db->head = hdb_record_create(key, value);
    return 0;
  }

  // Traverse until previous is the last node.
  while (current != NULL) {
    previous = current;
    current = current->next;
  }

  // Append to the last node.
  previous->next = hdb_record_create(key, value);

  return 0;
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

int main(int argc, char *argv[]) {
  char cmd[256];
  char key[256];
  char value[256];

  hdb_t *db = hdb_create();
  printf("\n\nWelcome to HackDB.\nYou don't care about your data and neither do we!\n\n");
  while (1) {
    printf("hdb> ");
    scanf("%s %s %s", cmd, key, value);

    if (!strcmp(cmd, "add"))
      hdb_add(db, key, value);
    else if (!strcmp(cmd, "get"))
      printf("%s\n", hdb_get(db, key));
    else if (!strcmp(cmd, "count"))
      printf("%u\n", hdb_count(db));
    else
      printf("Invalid command.\n");
  }

  printf("%s %s %s\n", cmd, key, value);
}

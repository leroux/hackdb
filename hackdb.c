#include "hackdb.h"

hdb_t *hdb_create(void) {
  hdb_t *db = malloc(sizeof(hdb_t));
  db->first = NULL;
  return db;
}

int hdb_add(hdb_t *db, char *key, char *value) {
  hdb_record *current = db->first;
  hdb_record *new = malloc(sizeof(hdb_record));

  new->key = strdup(key);
  new->value = strdup(value);
  new->next = NULL;

  if (current == NULL) {
    db->first = new;
    return 0;
  }

  while (current->next != NULL) {
    current = current->next;
  }

  current->next = new;

  return 0;
}

char *hdb_get(hdb_t *db, char *key) {
  hdb_record *current = db->first;

  if (current == NULL) {
    return NULL;
  }

  if (strcmp(current->key, key) == 0) {
    return current->value;
  }

  while (current->next != NULL) {
    current = current->next;

    if (strcmp(current->key, key) == 0) {
      return current->value;
    }
  }

  return NULL; // Traversed the entire list and didn't find the key.
}

unsigned int hdb_count(hdb_t *db) {
  int count = 1;
  hdb_record *current = db->first;

  if (current == NULL) {
    return 0;
  }

  while (current->next != NULL) {
    ++count;
    current = current->next;
  }

  return count;
}

void hdb_destroy(hdb_t *db) {
  hdb_record *current = db->first;
  hdb_record *next;

  while (current->next != NULL) {
    next = current->next;
    free(current);
    current = next;
  }

  free(current);
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
    else if (!strcmp(cmd, "count"))
      printf("%u\n", hdb_count(db));
    else
      printf("Invalid command.\n");
  }

  printf("%s %s %s\n", cmd, key, value);
}

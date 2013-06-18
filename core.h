#ifndef __CORE_H
#define __CORE_H

#define BLOCK_SIZE 1024

typedef struct hdb_record {
  char *key;
  char *value;
  struct hdb_record *previous;
  struct hdb_record *next;
} hdb_record;

typedef struct {
  hdb_record *head;
  hdb_record *last;
} hdb_t;

// Core
hdb_t *hdb_create(void);
hdb_record *hdb_alloc_and_init(unsigned int size);
int hdb_insert_after(hdb_record *record, const char *key, const char *value);
int hdb_insert_before(hdb_record *record, const char *key, const char *value);
int hdb_set(hdb_t *db, const char *key, const char *value);
hdb_record *hdb_get(hdb_t *db, const char *key);
int hdb_update_record(hdb_record *record, const char *value);
int hdb_del(hdb_t *db, hdb_record *record);
int hdb_destroy(hdb_t *db);

char *hdb_list(hdb_t *db);
unsigned int hdb_count(hdb_t *db);

int error(const char *msg);

#endif

#ifndef __CORE_H
#define __CORE_H

// A hdb_record consists of a key, value, and next record (singly-linked list).
typedef struct hdb_record {
  char *key;
  char *value;
  struct hdb_record *next;
} hdb_record; 

// A hdb_t (database type) is the head of a singly-linked list of hdb_record's.
typedef struct {
  hdb_record *head;
} hdb_t;

// Core
hdb_t *hdb_create(void);
hdb_record *hdb_record_create(char *key, char *value, hdb_record *next);
int hdb_add(hdb_t *db, char *key, char *value);
int hdb_del(hdb_t *db, char *key);
char *hdb_get(hdb_t *db, char *key);
int hdb_del(hdb_t *db, char *key);
void hdb_destroy(hdb_t *db);

// Core (recursive implementations)
int hdb_add_r(hdb_t *db, char *key, char *value);
int hdb_del_r(hdb_t *db, char *key);
char *hdb_get_r(hdb_t *db, char *key);
int hdb_del_r(hdb_t *db, char *key);
void hdb_destroy_r(hdb_t *db);

// Miscellaneous
void hdb_list_contents(hdb_t *db);
unsigned int hdb_count(hdb_t *db);

#endif

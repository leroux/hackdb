#ifndef __CORE_H_
#define __CORE_H_

#define BLOCKSIZE 4

typedef struct hdb_record {
  char *key;
  char *value;
  struct hdb_record *previous;
  struct hdb_record *next;
} hdb_record; 

typedef struct {
  hdb_record *head; // head of list.
  hdb_record *last; // the next free node of list.
} hdb_t;

// Core
hdb_t *hdb_create(void);
int hdb_set(hdb_t *db, const char *key, const char *value);
hdb_record *hdb_get(hdb_t *db, const char *key);
int hdb_update(hdb_record *record, const char *value);
int hdb_del(hdb_t *db, hdb_record *record);
int hdb_destroy(hdb_t *db);

// Allocation (Slab)
hdb_record *hdb_alloc_and_init(unsigned int blocksize, hdb_record *lastblocks_last);
hdb_record *hdb_get_next_free(hdb_t *db);

// Miscellaneous
void hdb_list_contents(hdb_t *db);
unsigned int hdb_count(hdb_t *db);

int error(const char *msg);

#endif

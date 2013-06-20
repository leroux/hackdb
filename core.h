#ifndef __CORE_H
#define __CORE_H

typedef struct hdb_record {
  char *key;
  char *value;
  struct hdb_record *previous;
  struct hdb_record *next;
} hdb_record; 

typedef struct {
  hdb_record *head;
} hdb_t;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Core
hdb_t *hdb_create(void);
hdb_record *hdb_record_create(const char *key, const char *value, hdb_record *previous, hdb_record *next);
int hdb_set(hdb_t *db, const char *key, const char *value);
hdb_record *hdb_get_record(hdb_t *db, const char *key);
char *hdb_get(hdb_t *db, const char *key);
int hdb_update(hdb_record *record, const char *value);
int hdb_del(hdb_t *db, char *key);
int hdb_destroy(hdb_t *db);

// Miscellaneous
void hdb_list_contents(hdb_t *db);
unsigned int hdb_count(hdb_t *db);

int error(const char *msg);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif

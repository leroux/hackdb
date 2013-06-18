#ifndef __HACKDB_H
#define __HACKDB_H

typedef struct hdb_record {
  char *key;
  char *value;
  struct hdb_record *next;
} hdb_record; 

typedef struct {
  hdb_record *head;
} hdb_t;

hdb_t *hdb_create(void);
hdb_record *hdb_record_create(char *key, char *value);
int hdb_add(hdb_t *db, char *key, char *value);
char *hdb_get(hdb_t *db, char *key);
int hdb_del(hdb_t *db, char *key);
unsigned int hdb_count(hdb_t *db);
void hdb_destroy(hdb_t *db);

#endif

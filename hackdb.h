#ifndef __HACKDB_H
#define __HACKDB_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct hdb_t {
  struct hdb_record *first;
} hdb_t;

typedef struct hdb_record {
  char *key;
  char *value;
  struct hdb_record *next;
} hdb_record; 

hdb_t *hdb_create(void);
int hdb_add(hdb_t *db, char *key, char *value);
char *hdb_get(hdb_t *db, char *key);
int hdb_del(hdb_t *db, char *key);
unsigned int hdb_count(hdb_t *db);
void hdb_destroy(hdb_t *db);

#endif

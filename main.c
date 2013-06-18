#include "main.h"
#include "hackdb.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  hdb_t *db = hdb_create();

  //char cmd[MAXCMD];
  //char *args[MAXARGS]
  
  char cmd[MAXCMD];
  char key[MAXCMD];
  char value[MAXCMD];

  // SCRAP ENTIRE PROMPT
  // Use fgets and parse the line.

  printf("\nHackDB :: You don't care about your data -> neither do we!\n");
  while (1) {
    printf("hdb> ");

    scanf("%s %s %s", cmd, key, value);

    if (!strcmp(cmd, "add"))
      hdb_add(db, key, value);
    else if (!strcmp(cmd, "get"))
      printf("%s\n", hdb_get(db, key));
    else if (!strcmp(cmd, "count"))
      printf("%u\n", hdb_count(db));
    else if (!strcmp(cmd, "exit"))
      break;
    else
      printf("Invalid command.\n");
  }

  hdb_destroy(db);

  return 0;
}

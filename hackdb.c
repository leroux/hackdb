#include "hackdb.h"
#include "core.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  hdb_t *db = hdb_create();
  char buffer[MAX_INPUT];
  char *token;
  char cmds[MAX_ARGS][MAX_INPUT];
  int i = 0, args_count = 0;

  printf("\nHackDB :: You don't care about your data -> neither do we!\n");

  while (1) {
    printf("hdb> ");
    fgets(buffer, MAX_INPUT, stdin);

    for (i = 0, token = strtok(buffer, SEPARATOR); i < MAX_ARGS && token != NULL; i++) {
      strncpy(cmds[i], token, MAX_INPUT);
      token = strtok(NULL, SEPARATOR);
    }

    args_count = i;

    if (!strcmp(cmds[0], "set")) {
      hdb_set(db, cmds[1], cmds[2]);
    } else if (!strcmp(cmds[0], "del")) {
      hdb_del(db, hdb_get(db, cmds[1]));
    } else if (!strcmp(cmds[0], "count")) {
      printf("%u\n", hdb_count(db));
    } else if (!strcmp(cmds[0], "list")) {
      hdb_list_contents(db);
    } else if (!strcmp(cmds[0], "get")) {
      printf("%s\n", hdb_get(db, cmds[1])->value);
    } else if (!strcmp(cmds[0], "exit")) {
      break;
    } else {
      printf("Invalid command.\n");
    }
  }

  hdb_destroy(db);

  return 0;
}

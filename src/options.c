#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "options.h"
#include "utils.h"

#define NEW_TASK 1
#define READ_TASK 2
#define EXIT 3

typedef struct {
  int idx;
  char name[50];
} Task;

char* parse_field(char* line, int field_index) {
  char* tok;
  for (tok = strtok(line, ";");
        tok && *tok;
        tok = strtok(NULL, ";\n")) {
    if (!--field_index) {
      return tok;
    }
  }

  return NULL;
}

Task get_last_task() {
  Task last_task;

  char line[256];
  FILE *fpt;
  fpt = fopen("tasks.csv", "r");

  if (fpt) {
    while (fgets(line, sizeof(line), fpt)) { continue; }

    char* idx_tmp = strdup(line);
    char* name_tmp = strdup(line);

    char *index_field = parse_field(idx_tmp, 1);
    char *index_field_ptr;

    long index = strtol(index_field, &index_field_ptr, sizeof(index_field));
    last_task.idx = index;

    strncpy(last_task.name, parse_field(name_tmp, 2), 50);

    free(idx_tmp);
    free(name_tmp);
    fclose(fpt);
  }
  
  return last_task;
}

int new_idx() {
  Task last_task = get_last_task();

  int new_index = last_task.idx + 1;

  return new_index;
}

void new_task(void) {
  cls();

  printf("Enter task name\n");
  printf("---> ");

  Task task;
  fgets(task.name, sizeof(task.name), stdin);

  FILE *fpt;
  fpt = fopen("tasks.csv", "a");
  fprintf(fpt, "%d;%s", new_idx(), task.name);
  fclose(fpt);
}

void read_task(void) {
  cls();

  printf("Current tasks\n\n");

  int c;
  FILE *fpt;
  fpt = fopen("tasks.csv", "r");

  if (fpt) {
    while ((c = getc(fpt)) != EOF) {
      putchar(c);
    }
    fclose(fpt);
  }

  printf("\nPress any key to continue...");
  getchar();
}

void process_input(int option) {
  switch (option) {
    case NEW_TASK:
      new_task();
    break;

    case READ_TASK:
      read_task();
    break;

    case EXIT:
      exit(0);
    break;

    default:
      cls();
      printf("Insert a valid option\n");
    break;
  }
}


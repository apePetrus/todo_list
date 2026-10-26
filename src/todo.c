#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "todo.h"
#include "utils.h"

typedef enum {
  NEW_TASK,
  READ_TASK,
  EXIT
} Option;

typedef enum {
  TODO,
  DONE
} Status;

typedef struct {
  int idx;
  char name[50];
  Status status;
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

char* parse_status(int status) {
  if (status == 0) {
    return "To-do";
  }
  return "Done";
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

    // returns -1 if no tasks exist
    if (!index_field) {
      last_task.idx = -1;
      return last_task;
    }

    long index = strtol(index_field, &index_field_ptr, sizeof(index_field));

    last_task.idx = index;

    if (index > 0) {
      strncpy(last_task.name, parse_field(name_tmp, 3), 50);
    }

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

  FILE *fpt;
  fpt = fopen("tasks.csv", "a");

  if (new_idx() == 0) {
    fprintf(fpt, "idx;status;name\n");
  }

  Task task;
  fgets(task.name, sizeof(task.name), stdin);

  task.status = TODO;

  fprintf(fpt, "%d;%d;%s", new_idx(), task.status, task.name);
  fclose(fpt);
}

void read_task(void) {
  cls();

  printf("Current tasks\n\n");

  char line[256];
  FILE *fpt;
  fpt = fopen("tasks.csv", "r");

  if (fpt) {

    // just skips first line (header) lol
    fgets(line, sizeof(line), fpt);

    while (fgets(line, sizeof(line), fpt)) {
      char* name_tmp = strdup(line);
      char* status_tmp = strdup(line);

      char *status_field = parse_field(status_tmp, 2);
      char *status_field_ptr;

      long status = strtol(
          status_field,
          &status_field_ptr,
          sizeof(status_field)
          );

      printf("%s - %s\n", parse_status(status), parse_field(name_tmp, 3));
      free(name_tmp);
      free(status_tmp);
    }

    fclose(fpt);
  }

  printf("\nPress any key to continue...");
  getchar();
}

void process_input(int option) {
  switch (option - 1) {
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


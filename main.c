#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[10];
char task_name[50];
char list[3][10] = {'\0'};
char *inputptr;
int option;

void cls(void) {
  printf("\e[H\e[2J\e[3J");
}

void new_task(void) {
  cls();

  printf("Enter task name\n");
  printf("---> ");
  fgets(task_name, sizeof(task_name), stdin);

  FILE *fpt;
  fpt = fopen("tasks.csv", "a");
  fprintf(fpt, "%s", task_name);
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
  if (option == 1) {
    new_task();
  } else if (option == 2) {
    read_task();
  } else if (option == 3) {
    exit(0);
  } else {
    cls();

    printf("Insert a valid option\n");
  }
}

int main(void) {
  while (true) {
    cls();
    printf("LISTA DE TAREFAS\n\n");

    printf("1 - New task\n");
    printf("2 - Read tasks\n");
    printf("3 - Exit\n\n");

    printf("Enter option\n");
    printf("---> ");

    fgets(input, sizeof(input), stdin);
    option = strtol(input, &inputptr, sizeof(input));
    process_input(option);
  }

  return 0;
}

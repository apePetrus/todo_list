#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "options.h"

int main(void) {
  while (1) {
    cls();
    printf("LISTA DE TAREFAS\n\n");

    printf("1 - New task\n");
    printf("2 - Read tasks\n");
    printf("3 - Exit\n\n");

    printf("Enter option\n");
    printf("---> ");

    char input[10];
    char *inputptr;
    int option;

    fgets(input, sizeof(input), stdin);
    option = strtol(input, &inputptr, sizeof(input));
    process_input(option);
  }

  return 0;
}

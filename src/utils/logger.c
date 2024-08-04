#include "logger.h"
#include <stdio.h>
void logger(char log[]) {
  if (IS_LOG != 1) {
    return;
  }
  printf("\n=> %s <=\n", log);
}

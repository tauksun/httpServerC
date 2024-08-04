#include "config/constants.h"
#include "server.h"
#include "utils/logger.h"
#include <stdlib.h>
#include <unistd.h>

int main() {
  logger("main");

  struct I_CONSTANTS *constants = getConstants();
  server();

  logger("Free heap memory for constants...");
  free(constants);
  return 0;
}

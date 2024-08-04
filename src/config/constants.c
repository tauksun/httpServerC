#include "constants.h"
#include "../utils/logger.h"
#include <stdlib.h>
#include <string.h>

int allocated = 0;
struct I_CONSTANTS *_constants;

struct I_CONSTANTS *getConstants() {

  // On subsequent calls
  // return pointer to already allocated memory
  if (allocated) {
    logger("Returning already allocated heap memory pointer for contants...");
    return _constants;
  }

  logger("Allocating heap memory for constants...");
  // Allocate memory on heap
  // return the pointer
  _constants = (struct I_CONSTANTS *)malloc(sizeof(struct I_CONSTANTS));
  strcpy(_constants->APPLICATION_NAME, "SERVER");
  _constants->PORT = 5454;
  _constants->MAX_THREAD_COUNT = CONNECTION_THREAD_SIZE;

  allocated = 1;
  return _constants;
}

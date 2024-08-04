#ifndef CONSTANTS
#define CONSTANTS

#define CONNECTION_THREAD_SIZE 1000
#define IS_LOGGER 1

struct I_CONSTANTS {
  char APPLICATION_NAME[10];
  int PORT;
  int MAX_THREAD_COUNT;
};

/**
 * Gives a map of constants
 */
struct I_CONSTANTS *getConstants();

#endif

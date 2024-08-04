#ifndef CLIENT_HANDLER
#define CLIENT_HANDLER

#include "utils/queue.h"
struct I_CLIENT_HANDLER_PARAMS {
  int socket;
  unsigned long *thread;
  struct I_QUEUE *queue;
};

struct I_REQUEST_DATA {
  char buffer[1024];
  char method[10];
  char route[96];
};

void *clientHandler(void *);

#endif

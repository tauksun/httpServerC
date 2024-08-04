#ifndef QUEUE
#define QUEUE

#include "../config/constants.h"
#define SIZE CONNECTION_THREAD_SIZE + 1

struct I_QUEUE {
  int head;
  int tail;
  int size;
  unsigned long *values[SIZE];
};

void initializeQueue(struct I_QUEUE *queue);

int addToQueue(struct I_QUEUE *queue, unsigned long *val);

unsigned long *fetchFromQueue(struct I_QUEUE *queue);

int canFetchFromQueue(struct I_QUEUE *queue);

#endif

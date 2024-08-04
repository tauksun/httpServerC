#include "queue.h"
#include "logger.h"
#include <stdlib.h>

void initializeQueue(struct I_QUEUE *queue) {
  logger("Initializing Queue...");
  queue->head = 0;
  queue->tail = 0;
  queue->size = SIZE;
}

int addToQueue(struct I_QUEUE *queue, unsigned long *val) {
  if (queue->tail + 1 == queue->head) {
    logger("Queue is full ! Can't add anymore.");
    return 1;
  }

  logger("Adding to Queue.");

  queue->values[queue->tail] = val;
  queue->tail = ((queue->tail + 1) % queue->size);
  return 0;
}

unsigned long *fetchFromQueue(struct I_QUEUE *queue) {
  if (queue->head == queue->tail) {
    logger("Queue is empty !");
    return NULL;
  }

  logger("Fetching from Queue.");
  unsigned long *value = queue->values[queue->head];

  queue->head = ((queue->head + 1) % queue->size);

  return value;
}

int canFetchFromQueue(struct I_QUEUE *queue) {
  if (queue->head == queue->tail) {
    return 1;
  }

  logger("Can be fetch from Queue !!!");
  return 0;
}

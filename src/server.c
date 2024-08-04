#include "clientHandler.h"
#include "config/constants.h"
#include "utils/logger.h"
#include "utils/queue.h"
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int server() {
  logger("Starting server...");

  struct I_CONSTANTS *constants = getConstants();

  // Initialize socket
  logger("Initializing socket");
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  // Bind
  struct sockaddr_in serverSocketAddress;
  serverSocketAddress.sin_family = AF_INET;
  serverSocketAddress.sin_addr.s_addr = INADDR_ANY;
  serverSocketAddress.sin_port = htons(constants->PORT);

  logger("Binding to socket");
  int bindReturn = bind(serverSocket, (struct sockaddr *)&serverSocketAddress,
                        sizeof(serverSocketAddress));
  if (bindReturn == -1) {
    logger("Unable to bind to socket.");
    exit(1);
  }

  // Listen
  logger("Listening on socket");
  listen(serverSocket, constants->MAX_THREAD_COUNT);

  // Accept incoming connection

  pthread_t threads[constants->MAX_THREAD_COUNT];

  // On getting new connection request
  // Check & Handle request in available
  // thread, otherwise let it wait in queue

  struct I_QUEUE queue;
  initializeQueue(&queue);
  for (int i = 0; i < constants->MAX_THREAD_COUNT; i++) {
    addToQueue(&queue, &threads[i]);
  }

  while (1) {
    // Check thread pool availability
    // if not available :
    // => don't accept connections : continue;

    if (canFetchFromQueue(&queue) != 0) {
      // Event based
      sleep(1);
      continue;
    }

    int clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == -1) {
      logger("Error occured while accepting client connection.");
      continue;
    }

    logger("Connection accepted.");

    // Handle each connection on a seprate thread
    struct I_CLIENT_HANDLER_PARAMS *paramsHeap =
        (struct I_CLIENT_HANDLER_PARAMS *)malloc(
            sizeof(struct I_CLIENT_HANDLER_PARAMS));

    paramsHeap->socket = clientSocket;
    logger("Fetching thread from queue...");
    unsigned long *thread = fetchFromQueue(&queue);
    paramsHeap->queue = &queue;
    paramsHeap->thread = thread;

    pthread_create(thread, NULL, clientHandler, paramsHeap);
    pthread_detach(*thread);
  }

  return 0;
}

#include "clientHandler.h"
#include "handlers/health/health.h"
#include "handlers/home/home.h"
#include "handlers/unknown/unknown.h"
#include "utils/logger.h"
#include "utils/parser.h"
#include "utils/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void *clientHandler(void *params) {
  struct I_CLIENT_HANDLER_PARAMS *handlerParams = params;
  int clientSocket = handlerParams->socket;

  struct I_REQUEST_DATA requestData;
  memset(requestData.buffer, 0, sizeof(requestData.buffer));
  memset(requestData.method, 0, sizeof(requestData.method));
  memset(requestData.route, 0, sizeof(requestData.route));

  // Read
  recv(clientSocket, requestData.buffer, sizeof(requestData.buffer) - 1, 0);
  logger("client sent : ");
  logger(requestData.buffer);

  // Parse : fetch method & route //
  parser(&requestData);
  logger("METHOD : ");
  logger(requestData.method);
  logger("ROUTE : ");
  logger(requestData.route);

  // Pass to handler //
  if (strcmp(requestData.route, "/") == 0) {
    // Serve Home
    home(clientSocket);
  } else if (strcmp(requestData.route, "/health") == 0) {
    // Health Check
    health(clientSocket);
  } else {
    // Hit on unknown route
    unknown(clientSocket);
  }

  logger("Closing client connection.");
  close(clientSocket);

  logger("Adding thread back to Queue...");
  addToQueue(handlerParams->queue, handlerParams->thread);
  logger("Free allocated heap memory for pointer...");
  free(params);

  return NULL;
}

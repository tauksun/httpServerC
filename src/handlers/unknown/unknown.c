#include "../../utils/logger.h"
#include <string.h>
#include <unistd.h>

int unknown(int socket) {
  logger("Hit on unknown route");
  char *htmlResponse = "HTTP/1.1 400 BAD REQUEST\r\n"
                       "Connection: close\r\n"
                       "\r\n";

  write(socket, htmlResponse, strlen(htmlResponse));
  return 0;
}

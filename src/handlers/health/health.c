#include "../../utils/logger.h"
#include <string.h>
#include <unistd.h>

int health(int socket) {
  logger("Hit on health");
  char *htmlResponse = "HTTP/1.1 200 OK\r\n"
                       "Content-Type: application/json\r\n"
                       "Connection: close\r\n"
                       "\r\n"
                       "{health:OK}";

  write(socket, htmlResponse, strlen(htmlResponse));
  return 0;
}

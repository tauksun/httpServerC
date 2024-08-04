#include "../../utils/logger.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int home(int socket) {
  logger("Hit on home");
  char *response = "HTTP/1.1 200 OK\r\n"
                   "Content-Type: text/html\r\n"
                   "\r\n";

  // Response with 200 & then stream the file contents
  write(socket, response, strlen(response));

  logger("Reading from file...");
  FILE *index_file;
  index_file = fopen("./data/index.html", "r");

  char htmlData[1024];
  while (fgets(htmlData, 1024, index_file) != NULL) {
    // Stream to client
    write(socket, htmlData, strlen(htmlData));
    memset(htmlData, 0, 1024);
  }

  // Close
  logger("Closing file...");
  fclose(index_file);
  return 0;
}

#include "../clientHandler.h"
#include <string.h>
int parser(struct I_REQUEST_DATA *requestData) {

  int m = 0;
  int r = 0;

  char *requestBuffer = requestData->buffer;

  int count = 0;

  for (int i = 0; i < strlen(requestBuffer); i++) {
    if (requestBuffer[i] == ' ') {
      if (m == 0) {
        m = 1;
        count = 0;
      } else {
        r = 1;
        count = 0;
      }
    } else {
      if (m == 0) {
        requestData->method[count] = requestBuffer[i];
        count++;
      } else if (r == 0) {
        requestData->route[count] = requestBuffer[i];
        count++;
      }
    }
  }
  return 0;
}

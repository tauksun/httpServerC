#include "../../utils/directoryStructure.h"
#include "../../utils/logger.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int isValidFilePath(char *path) {
  logger("Checking validity for path : ");
  logger(path);
  struct I_NODE *currentDir = getDirStructure();
  currentDir = currentDir->dirs[0];
  char tempName[1024] = "";
  int tempCount = 0;

  for (int i = 1; i < strlen(path); i++) {
    if (path[i] == '/') {
      // search dir
      int found = 0;
      for (int d = 0; d < currentDir->dirCount; d++) {
        if (strcmp(currentDir->dirs[d]->val, tempName) == 0) {
          currentDir = currentDir->dirs[d];
          found = 1;
          break;
        }
      }

      if (found == 0) {
        // No such path exists
        logger("No such path exists");
        return 1;
      }

      memset(tempName, 0, strlen(tempName));
      tempCount = 0;
    } else {
      if (i == strlen(path) - 1) {
        tempName[tempCount] = path[i];
        tempCount++;

        int found = 0;
        for (int f = 0; f < currentDir->fileCount; f++) {
          if (strcmp(currentDir->files[f], tempName) == 0) {
            found = 1;
            break;
          }
        }
        if (found == 0) {
          // No such file exists
          logger("No such file exists");
          return 1;
        } else {
          return 0;
        }
      } else {
        tempName[tempCount] = path[i];
        tempCount++;
      }
    }
  }

  return 0;
}

int serverFile(int socket, char *path) {
  logger("Hit on serverFile");

  char pathToFile[1024];
  char currentDirectory[1024];
  getcwd(currentDirectory, sizeof(currentDirectory));

  strcpy(pathToFile, currentDirectory);
  strcat(pathToFile, "/");
  strcat(pathToFile, DATA_DIRECTORY);
  strcat(pathToFile, path);

  logger("serving file : ");
  logger(pathToFile);

  char *response = "HTTP/1.1 200 OK\r\n"
                   "\r\n";

  // Response with 200 & then stream the file contents
  write(socket, response, strlen(response));

  logger("Reading from file...");
  FILE *index_file;
  index_file = fopen(pathToFile, "r");

  char htmlData[1024];

  int nb = fread(htmlData, 1, sizeof(htmlData), index_file);
  write(socket, htmlData, nb);
  memset(htmlData, 0, sizeof(htmlData));

  while (!feof(index_file)) {
    nb = fread(htmlData, 1, sizeof(htmlData), index_file);
    write(socket, htmlData, nb);
    memset(htmlData, 0, sizeof(htmlData));
  }

  // Close
  logger("Closing file...");
  fclose(index_file);
  return 0;
}

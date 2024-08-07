#ifndef FILE_SERVER
#define FILE_SERVER
#include "../../utils/directoryStructure.h"

int isValidFilePath(char *path);
int serverFile(int socket, char *path);
#endif

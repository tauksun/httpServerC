#include "directoryStructure.h"
#include "../config/constants.h"
#include "logger.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int structureCreated = 0;

// Directory entry point
struct I_NODE *root;

int traverse(char *node, struct I_NODE *parent) {
  struct dirent *dirEntry;
  DIR *dir = opendir(node);

  if (dir == NULL) {
    // Add to parent files
    char *temp = strrchr(node, '/');
    int nameLength = strlen(node) - (temp - node);
    char fileName[nameLength];
    strcpy(fileName, temp + 1);

    char *name = (char *)malloc(strlen(fileName));
    strcpy(name, fileName);
    parent->files[parent->fileCount] = name;
    parent->fileCount++;
    if (parent->fileCount > MAX_DEPTH) {
      logger("MAX_DEPTH reached for number of files !!! ");
      logger("Increase MAX_DEPTH in constants.h for serving more files.");
      exit(1);
    }

    return 1;
  }

  struct I_NODE *directory = (struct I_NODE *)malloc(sizeof(struct I_NODE *));

  char *temp = strrchr(node, '/');
  int nameLength = strlen(node) - (temp - node);
  char dirName[nameLength];
  strcpy(dirName, temp + 1);

  directory->val = (char *)malloc(strlen(dirName) + 1);
  char *directoryName = (char *)malloc(strlen(dirName) + 1);
  strcpy(directoryName, dirName);
  directory->val = directoryName;

  directory->fileCount = 0;
  directory->files = (char **)malloc(MAX_DEPTH * (sizeof(char *)));
  directory->dirCount = 0;
  directory->dirs =
      (struct I_NODE **)malloc(MAX_DEPTH * (sizeof(struct I_NODE *)));

  // Add to parent dir
  parent->dirs[parent->dirCount] = directory;
  parent->dirCount++;
  if (parent->dirCount > MAX_DEPTH) {
    logger("MAX_DEPTH for directory nesting reached !!!");
    logger("Increase MAX_DEPTH in constants.h for increased nesting.");
    exit(1);
  }

  while ((dirEntry = readdir(dir)) != NULL) {
    if ((strcmp(dirEntry->d_name, ".") != 0) &&
        (strcmp(dirEntry->d_name, "..") != 0)) {

      char dirPath[256];
      strcpy(dirPath, node);
      strcat(dirPath, "/");
      strcat(dirPath, dirEntry->d_name);
      traverse(dirPath, directory);
    }
  }

  return 0;
}

struct I_NODE *getDirStructure() {

  if (structureCreated == 1) {
    return root;
  }

  root = (struct I_NODE *)malloc(sizeof(struct I_NODE *));

  // No need to free heap memory allocated for storing nodes
  // while creating structure, because it is needed throught the
  // lifetime of process & will be cleaned on termination
  logger("Creating Structure...");
  char *name = (char *)malloc(strlen("root") + 1);
  strcpy(name, "root");
  root->val = name;
  root->fileCount = 0;
  root->files = (char **)malloc(MAX_DEPTH * (sizeof(char *)));
  root->dirCount = 0;
  root->dirs = (struct I_NODE **)malloc(MAX_DEPTH * (sizeof(struct I_NODE *)));

  char currentDirectory[1024];
  getcwd(currentDirectory, sizeof(currentDirectory));
  strcat(currentDirectory, "/");
  strcat(currentDirectory, DATA_DIRECTORY);
  logger("Traversing : ");
  logger(currentDirectory);
  traverse(currentDirectory, root);
  logger("Structure Created.");

  structureCreated = 1;

  return root;
}

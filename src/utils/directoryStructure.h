#ifndef DIRECTORY_STRUCTURE
#define DIRECTORY_STRUCTURE

#define MAX_DEPTH 256

struct I_NODE {
  char *val;
  int fileCount;
  char **files;
  int dirCount;
  struct I_NODE **dirs;
};

struct I_NODE *getDirStructure();
#endif

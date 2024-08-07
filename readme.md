# Make Executable

gcc -o executable main.c server.c utils/logger.c utils/parser.c utils/queue.c handlers/health/health.c handlers/home/home.c handlers/unknown/unknown.c config/constants.c clientHandler.c handlers/file/file.c utils/directoryStructure.c

# Run

./executable

# Details

Running port & number of threads are defined in constants

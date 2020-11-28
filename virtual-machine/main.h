// Include standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define CRST "\x1B[0m"  // Reset to default
#define CBLK "\x1B[30m" // Black
#define CRED "\x1B[31m" // Red
#define CGRN "\x1B[32m" // Green
#define CYEL "\x1B[33m" // Yellow
#define CBLU "\x1B[34m" // Blue
#define CMAG "\x1B[35m" // Magenta
#define CCYN "\x1B[36m" // Cyan
#define CWHT "\x1B[37m" // White

#define SPT  "\x1B[0m\u250A" // Seperator of default color

void getBinaryRepresentation(int reg, char *dest);
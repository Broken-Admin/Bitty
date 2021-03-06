// Include standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define CRST "\x1B[0m"  // Reset to default
#define CBLK "\x1B[30m" // Black
#define CWHT "\x1B[37m" // White

#define SPT  "\x1B[0m\u250A" // Seperator of default color

void getBinaryRepresentation(int reg, char *dest);
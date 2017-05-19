#ifndef TP4_FILE_H
#define TP4_FILE_H

#include <stdlib.h>
#include <stdio.h>
#include "table.h"

int file_load(const char *, Table_t);
int stream_load(FILE *, Table_t);
#endif

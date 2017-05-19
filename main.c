#include <stdlib.h>
#include "table.h"
#include "file.h"

int main() {

    Table_t table = {NULL};

    file_load("list.dat", table);

    return EXIT_SUCCESS;
}
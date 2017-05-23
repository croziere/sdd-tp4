#include <stdlib.h>
#include "table.h"
#include "file.h"

int main() {

    Table_t table = {NULL};

    file_load("list.dat", table);

    table_afficher(table);

    printf("Traduction de %s en %s", "uncle", table_value(table, "uncle"));

    table_liberer(table);

    return EXIT_SUCCESS;
}

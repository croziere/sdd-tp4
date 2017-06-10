#include <stdlib.h>
#include "controller.h"
#include "file.h"

int main(int argc, char **argv) {

    /* controller_main(argc, argv); */

    puts("== TESTS ==");
    Table_t table = {NULL};

    puts("-- Affichage table vide --");
    table_afficher(table);

    puts("-- Charger une clé/valeur --");
    file_load("test1.dat", table);
    table_afficher(table);

    puts("-- Ecrasement d'une valeur --");
    file_load("test2.dat", table);
    table_afficher(table);

    puts("-- Insertion pour une clé NULL --");
    table_insertion(table, NULL, NULL);
    table_afficher(table);

    puts("-- Insertion d'une deuxième clé/valeur --");
    file_load("test3.dat", table);
    table_afficher(table);

    table_liberer(table);

    puts("-- Chargement depuis un fichier --");
    file_load("list.dat", table);
    table_afficher(table);

    puts("-- Traduction --");
    controller_translate(table);

    table_liberer(table);

    return EXIT_SUCCESS;
}

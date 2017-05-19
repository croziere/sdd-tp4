#ifndef TP4_TABLE_H
#define TP4_TABLE_H

#include "hash.h"
#include "helpers.h"

typedef char* TableContent_t;
typedef char* TableKey_t;

typedef struct cell
{
    TableKey_t key;
    TableContent_t content;
    struct cell *next;
}Cellule_t, *Table_t[HASH_MAX];

Cellule_t* table_creer_cell();
Cellule_t* table_init_cell(TableKey_t, TableContent_t);
Cellule_t** table_recherchePrec(Cellule_t **, unsigned int, bool *);
void table_insertion_liste(Cellule_t*, Cellule_t**);
void table_insertion(Table_t, TableKey_t, TableContent_t);
void table_parser(char *);



#endif

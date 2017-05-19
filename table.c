#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "table.h"

Cellule_t *table_creer_cell()
{
    Cellule_t *cell = NULL;
    cell = (Cellule_t*)malloc(sizeof(Cellule_t));

    cell->content = NULL;
    cell->key = NULL;
    cell->next = NULL;

    return cell;
}

Cellule_t *table_init_cell(TableKey_t key, TableContent_t content)
{
    Cellule_t *cell = table_creer_cell();

    cell->content = content;
    cell->key = key;

    return cell;
}

Cellule_t **table_recherchePrec(Cellule_t **list, unsigned int key, bool *found)
{
    Cellule_t** prec = list;
    Cellule_t* cur = *list;
    *found = false;

    while (cur && key < hash_string(cur->key))
    {
        prec = &(cur->next);
        cur = cur->next;
    }

    if (cur && hash_string(cur->key) == key)
    {
        *found = true;
    }

    return prec;
}

void table_insertion_liste(Cellule_t * cell, Cellule_t **list)
{
    bool found;
    Cellule_t* tmp = NULL;
    Cellule_t** prec = table_recherchePrec(list, hash_string(cell->key), &found);

    tmp = *prec;
    cell->next = *prec;
    *prec = cell;

    if (found)
    {
        free(tmp);
    }
}

void table_insertion(Table_t table, TableKey_t key, TableContent_t content)
{
    Cellule_t* cell = table_init_cell(key, content);
    int i=0;

    while (table[i] && hash_string(cell->key) < hash_string(table[i]->key))
    {
        i++;
    }

    table_insertion_liste(cell, &(table[i]));
}
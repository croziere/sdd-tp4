#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

Cellule_t **table_recherchePrec(Cellule_t **list, TableKey_t key, bool *found)
{
    Cellule_t** prec = list;
    Cellule_t* cur = *list;
    *found = false;

    while (cur && strcmp(key, cur->key) < 0)
    {
        prec = &(cur->next);
        cur = cur->next;
    }

    if (cur && strcmp(cur->key, key) == 0)
    {
        *found = true;
    }

    return prec;
}

void table_insertion_liste(Cellule_t * cell, Cellule_t **list)
{
    bool found = false;
    Cellule_t* tmp = NULL;
    Cellule_t** prec = table_recherchePrec(list, cell->key, &found);

    if (found)
    {
        (*prec)->content = cell->content;
        free(cell);
    }
    else
    {
        tmp = *prec;
        cell->next = *prec;
        *prec = cell;
    }
}

void table_insertion(Table_t table, TableKey_t key, TableContent_t content)
{
    Cellule_t* cell = table_init_cell(key, content);

    table_insertion_liste(cell, &(table[hash_string(cell->key)]));
}

void table_afficher(Table_t table) {

    int i;
    Cellule_t *cur = NULL;

    puts("table = {");

    for (i=0;i<HASH_MAX;i++)
    {
        if (table[i])
        {
            cur = table[i];
            while (cur)
            {
                printf("\t%s => %s,\n", cur->key, cur->content);
                cur = cur->next;
            }
        }
    }

    puts("}");
}

TableContent_t table_value(Table_t table, TableKey_t key)
{

    Cellule_t **prec = NULL;
    bool found = false;
    TableContent_t content;

    prec = table_recherchePrec(&(table[hash_string(key)]), key, &found);

    if (found)
    {
        content = (*prec)->content;
    }
    else
    {
        content = NULL;
    }

    return content;
}

void table_liberer(Table_t table)
{
    int i=0;

    for(i=0;i<HASH_MAX;i++)
    {
        table_liste_liberer(table[i]);
        table[i] = NULL;
    }
}

void table_liste_liberer(Cellule_t * liste)
{
    Cellule_t *tmp;

    while (liste)
    {
        tmp = liste;
        liste = liste->next;
        free(tmp);
    }
}

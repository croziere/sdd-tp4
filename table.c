#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "table.h"

/**
 * Alloue et retourne une cellule vide
 * @return Pointeur sur la cellule
 */
Cellule_t *table_creer_cell()
{
    Cellule_t *cell = NULL;
    cell = (Cellule_t*)malloc(sizeof(Cellule_t));

    cell->content = NULL;
    cell->key = NULL;
    cell->next = NULL;

    return cell;
}

/**
 * Créé une cellule et insere sa clé / valeur
 * @param key La clé
 * @param content La valeur
 * @return Un pointeur sur la cellule
 */
Cellule_t *table_init_cell(TableKey_t key, TableContent_t content)
{
    Cellule_t *cell = table_creer_cell();

    cell->content = content;
    cell->key = key;

    return cell;
}

/**
 * Recherche dans la liste chainée de la table
 * @param list La liste dans laquelle on veut rechercher
 * @param key La clé recherchée
 * @param found Vrai si l'élément existe
 * @return Pointeur sur le pointeur de l'élément
 */
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

/**
 * Insere une cellule dans la liste chainée de la zone de donnée
 * Si la cellule avec la clé existe déjà, sa valeur est remplacée
 * @param cell La cellule à inserer
 * @param list La liste de cellules
 */
void table_insertion_liste(Cellule_t * cell, Cellule_t **list)
{
    bool found = false;
    Cellule_t** prec = table_recherchePrec(list, cell->key, &found);

    if (found)
    {
        (*prec)->content = cell->content;
        free(cell);
    }
    else
    {
        cell->next = *prec;
        *prec = cell;
    }
}

/**
 * Fonction de haut niveau qui insère une clé / valeur dans la table
 * @param table
 * @param key
 * @param content
 */
void table_insertion(Table_t table, TableKey_t key, TableContent_t content)
{
    Cellule_t* cell = NULL;

    if (key && content)
    {
        cell = table_init_cell(key, content);

        table_insertion_liste(cell, &(table[hash_string(cell->key)]));
    }
}

/**
 * Affiche le contenu de la table
 * @param table
 */
void table_afficher(Table_t table)
{

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

/**
 * Retourne la valeur pour une clé donnée
 * On fait une recherche dans la liste chainée à l'adresse correspondant au hash de la clé dans la table
 * Retourne NULL si non trouvé
 * @param table
 * @param key
 * @return
 */
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

/**
 * Libère la table
 * @param table
 */
void table_liberer(Table_t table)
{
    int i=0;

    for(i=0;i<HASH_MAX;i++)
    {
        table_liste_liberer(table[i]);
        table[i] = NULL;
    }
}

/**
 * Libère la liste chainée
 * @param liste
 */
void table_liste_liberer(Cellule_t * liste)
{
    Cellule_t *tmp;

    while (liste)
    {
        tmp = liste;
        liste = liste->next;
        free(tmp->key);
        free(tmp->content);
        free(tmp);
    }
}

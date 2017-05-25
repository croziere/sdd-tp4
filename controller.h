#ifndef TP4_CONTROLLER_H
#define TP4_CONTROLLER_H

#include <stdio.h>
#include "table.h"

typedef struct state {
    Table_t *table;
    int choix;
}State_t;

void controller_show_menu();

int controller_prompt();

void controller_main(int, char **);

void controller_do(Table_t, int);

void controller_add_translation(Table_t);

void controller_usage();

#endif

#include <stdlib.h>
#include <memory.h>
#include "controller.h"
#include "file.h"

void controller_show_menu()
{
    puts("==== Menu Principal ===");
    puts("");
    puts("\t1) Afficher la table");
    puts("\t2) Ajouter une traduction");
    puts("\t3) Traduire une phrase");
    puts("\t0) Quitter");
    puts("");
}

int controller_prompt()
{
    int choix;

    printf("Choix : ");
    fflush(stdout);
    scanf("%d%*c", &choix);

    return choix;
}

void controller_main(int argc, char **argv)
{
    int choix;
    int statusCode;
    Table_t table = {NULL};

    if (argc < 1)
    {
        statusCode = file_load(argv[1], table);
    }

    do
    {
        controller_show_menu();
        choix = controller_prompt();
        controller_do(table, choix);
    } while (choix);

    table_liberer(table);
}

void controller_do(Table_t table, int choix)
{
    switch (choix)
    {
        case 0:
            break;
        case 1:
            table_afficher(table);
            break;
        case 2:
            controller_add_translation(table);
            break;
        case 3:
            controller_translate(table);
            break;
        default:
            puts("Commande inconnue");
    }
}

void controller_add_translation(Table_t table)
{
    char buff[26];
    char *key, *value;

    printf("Mot à traduire : ");
    fflush(stdout);
    scanf("%s", buff);

    key = (char*)malloc(sizeof(char)*strlen(buff));
    strcpy(key, buff);

    printf("Traduction : ");
    fflush(stdout);
    scanf("%s", buff);

    value = (char*)malloc(sizeof(char)*strlen(buff));
    strcpy(value, buff);

    table_insertion(table, key, value);
}

void controller_translate(Table_t table) {
    char buf[100];
    char *cur = buf;

    printf("Phrase à traduire : ");
    fflush(stdout);
    fgets(buf, 100, stdin);

    if (buf[strlen(buf) - 1] == '\n') {
        buf[strlen(buf) - 1] = '\0';
    }

    printf("%s => ", buf);

    cur = strtok(buf, " ");

    do
    {
        printf("%s ", table_value(table, cur));
    } while ((cur = strtok(NULL, " ")));

    printf("\n");
}

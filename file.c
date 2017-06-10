#include <memory.h>
#include <stdlib.h>
#include "file.h"

/**
 * Charge un fichier depuis son path
 * Délègue le chargement des données à stream_load
 * @param path Le path du fichier à charger
 * @param table La table
 * @return Un code d'erreur
 */
int file_load(const char *path, Table_t table)
{
    FILE *stream = NULL;
    int statusCode = 0;

    stream = fopen(path, "r");

    if (stream)
    {
        statusCode = stream_load(stream, table);

        if(fclose(stream) != 0)
        {
            statusCode = 1;
        }
    }
    else
    {
        statusCode = 1;
    }

    return statusCode;
}

/**
 * Charge les données d'un flux du type clé;valeur dans la table
 * Lit chaque ligne du fichier
 * Pour chaque ligne
 *      On découpe la ligne en fonction de ;
 *      On alloue la clé et la valeur que l'on insere dans la table
 * @param stream Le flux ouvert
 * @param table La table
 * @return Un code d'erreur
 */
int stream_load(FILE *stream, Table_t table)
{
    char buf[100];
    char *tmp;
    char* key = NULL;
    char* value = NULL;

    while (fgets(buf, 100, stream))
    {
        if (buf[strlen(buf) - 1] == '\n')
        {
            buf[strlen(buf) - 1] = '\0';
        }

        tmp = strtok(buf, ";");
        key = (char *)malloc(sizeof(char)*strlen(tmp)+1);
        strcpy(key, tmp);


        tmp = strtok(NULL, ";");
        value = (char *)malloc(sizeof(char)*strlen(tmp)+1);
        strcpy(value, tmp);

        table_insertion(table, key, value);
    }

    return ferror(stream);
}

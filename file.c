#include <memory.h>
#include <stdlib.h>
#include "file.h"

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
        key = (char *)malloc(sizeof(char)*strlen(tmp));
        strcpy(key, tmp);


        tmp = strtok(NULL, ";");
        value = (char *)malloc(sizeof(char)*strlen(tmp));
        strcpy(value, tmp);

        table_insertion(table, key, value);
    }

    return ferror(stream);
}

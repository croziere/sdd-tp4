#include <ctype.h>
#include "hash.h"

/**
 * Fonction de hachage d'une chaine de caractère
 * @param str La chaine à hacher
 * @return Le hash
 */
unsigned int hash_string(const char *str)
{
    unsigned int hash = 5381;
    const char *s;

    for (s=str; *s; s++)
    {
        hash = ((hash << 5) + hash) + tolower(*s);
    }

    return (hash & 0x7FFFFFFF)%HASH_MAX;
}

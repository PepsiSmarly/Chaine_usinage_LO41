/**
 * Auteur: Thomas Gredin
 *
 * Liste chainée qui associe des clés avec leur valeur
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ARRAY_FIELD_MAX_SIZE 256

typedef struct
{
    struct Array* next;
    struct Array* prev;

    char* key;
    char* value;
}
Array;

/**
 * Créer le premier maillon d'un tableau
 * @return Le premier maillon
 */
Array*      array_Create();

/**
 * Créer le premier maillon d'un tableau en remplissant ces champs
 * @param  _key   clé du premier maillon
 * @param  _value valeur du premier maillon
 * @return        le premier maillon nouvellement crée
 */
Array*      array_CreateWithValues(const char* _key, const char* _value);

/**
 * Détruire tous les maillons du tableau
 * @param  _array premier maillon
 */
void        array_Destroy(Array* _array);

/**
 * Ajouter un maillon à la fin du tableau
 * @param  _array premier maillon
 * @param  _key   clé du nouveau maillon
 * @param  _value valeur du nouveau maillon
 */
void        array_Add(Array* _array, const char* _key, const char* _value);

/**
 * Ajouter un maillon déjà crée à la fin du tableau
 * @param  _array premier maillon du tableau
 * @param  _new   maillon à ajouter à la fin
 */
void        array_AddArray(Array* _array, Array* _new);

/**
 * Récupérer le maillon à l'index donnée dans la liste
 * @param  _array premier maillon de la liste
 * @param  _index index ou chercher
 * @return        Le maillon à l'index donnée
 */
Array*      array_GetAt(Array* _array, int _index);

/**
 * Récupérer un maillon suivant la clé qu'il contient
 * Attention cependant si plusieurs maillons de la liste possèdent la même
 * clé c'est tout simplement le premier à apparaitre qui sera retourné
 * @param  _array premier maillon de la liste
 * @param  _key   la clé à trouver
 * @return        le maillon trouvé qui possède cette clé
 */
Array*      array_GetKey(Array* _array, const char* _key);

/**
 * Récupérer la valeur à l'index donné
 * @param  _array premier maillon de la liste
 * @param  _index l'index ou chercher
 * @return        la valeur du maillon à l'index donné
 */
char*       array_GetValueAt(Array* _array, int _index);

/**
 * Récupérer la valeur du maillon qui possède la clé donnée
 * @param  _array premier maillon de la liste
 * @param  _key   clé à chercher
 * @return        la valeur du maillon qui porte la clé donnée
 */
char*       array_GetValueKey(Array* _array, const char* _key);

/**
 * Supprimer un maillon à l'index donné
 * @param  _array premier maillon de la liste
 * @param  _index index du maillon à supprimer
 */
void        array_DeleteAt(Array* _array, int _index);

/**
 * Récupérer le dernier maillon de la liste
 * @param  _array premier maillon de la liste
 * @return        le dernier maillon
 */
Array*      array_GetLast(Array* _array);

/**
 * Récupérer le nombre d'éléments présents dans le tableau
 * @param  _array premier maillon du tableau
 * @return        le nombre d'éléments
 */
int         array_GetLenght(Array* _array);

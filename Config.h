/**
 * Auteur: Thomas Gredin
 *
 * Pour la lecture de fichier de configuration
 */

#include "Array.h"

#define CONFIG_MAX_LENGHT 256

typedef struct
{
    FILE* file;
    Array* content;
}
Config;

/**
 * Créer une instance de Config en ouvrant le fichier si ce dernier existe et en
 * stockant le contenu dans le champ content de la structure
 * @param  _file chemin vers le fichier
 * @return       instance
 */
Config*     config_Create(const char* _file);

/**
 * Détruit l'instance de Config donnée
 * @param  _config l'instance à détruire
 */
void        config_Destroy(Config* _config);

/**
 * Récupérer la valeur du champ donnée dans la configuration donnée
 * @param  _config  l'instance dans laquelle chercher
 * @param  _field   le champ à chercher
 * @return          la valeur associé au champ
 */
char*       config_GetField(Config* _config, const char* _field);

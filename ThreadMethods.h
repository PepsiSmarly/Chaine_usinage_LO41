/**
 * Auteur: Thomas Gredin
 *
 * Ce fichier contient les prototypes des méthodes qui seront utilisées pour les
 * différents threads du programme
 */

#ifndef THREAD_METHODS_H
#define THREAD_METHODS_H

#include <pthread.h>

#include "Supervisor.h"
#include "Convoyer.h"
#include "Network.h"

/**
 * Structure à utiliser en argument lors de l'utilisation de pthread_create avec
 * la méthode des tables d'usinage (FactoryTable)
 *
 *
 */
typedef struct
{
    FactoryTable*       factoryTable;
    Network*            network;
}
FactoryTable_Args;

/**
 * Thread des tables d'usinage
 * @param args arguments
 */
void* factoryTable_Thread(void* args);

/**
 * Thread du Superviseur
 * @param args arguments
 */
void* supervisor_Thread(void* args);

/**
 * Thread du robot de chargement
 * @param args arguments
 */
void* robot_loader_Thread(void* args);

/**
 * Thread du robot de retrait
 * @param args arguements
 */
void* robot_unloader_Thread(void* args);

/**
 * Thread du convoyeur
 * @param args argument
 */
void* convoyer_Thread(void* args);

/**
 * Permet d'initialiser tous les éléments
 * @param  _factoryTable la table concernée
 * @param  _supervisor   le superviseur du système
 * @param  _convoyer     le convoyeur du système
 * @return               l'argument complété
 */
FactoryTable_Args* factoryTable_Args_Create(
    FactoryTable*   _factoryTable,
    Network*        _network
);

/**
 * Détruire les arguments
 * @param _ft_Args les arguments à détruire
 */
void factoryTable_Args_Destroy(FactoryTable_Args* _ft_Args);

#endif

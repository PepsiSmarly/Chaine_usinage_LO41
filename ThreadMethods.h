/**
 * Auteur: Thomas Gredin
 *
 * Ce fichier contient les prototypes des méthodes qui seront utilisées pour les
 * différents threads du programme
 */

#ifndef THREAD_METHODS_H
#define THREAD_METHODS_H

#include <pthread.h>
#include <stdlib.h>

#include "Network.h"
#include "Robot.h"

/**
 * Structure à utiliser en argument lors de l'utilisation de pthread_create avec
 * la méthode des tables d'usinage (FactoryTable)
 */
typedef struct
{
    FactoryTable*       factoryTable;
    Network*            network;
}
FactoryTable_Args;

/**
 * Structure à utiliser en argument lors de l'utilisation de pthread_create avec
 * la méthode des robot (FactoryTable)
 */
typedef struct
{
    Robot*      robot;
    Network*    network;
}
Robot_Args;

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
 * @param  _network le réseau (totalité du système)
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

/**
 * Permet d'initialiser tous les éléments
 * @param  _robot   le robot concerné
 * @param  _network le réseau (totalité du système)
 * @return          le Robot_Args nouvellement créé et complété
 */
Robot_Args* robot_Args_Create(
    Robot*      _robot,
    Network*    _network
);

/**
 * Détruire les arguments
 * @param _robot_Args les arguments à détruire
 */
void robot_Args_Destroy(Robot_Args* _robot_Args);

#endif

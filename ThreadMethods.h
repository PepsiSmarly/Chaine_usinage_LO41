/**
 * Auteur: Thomas Gredin
 *
 * Ce fichier contient les prototypes des méthodes qui seront utilisées pour les
 * différents threads du programme
 */

#ifndef THREAD_METHODS_H
#define THREAD_METHODS_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "Network.h"
#include "Robot.h"
#include "Convoyer.h"
#include "FactoryTable.h"

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
 * la méthode des robot (Robot)
 */
typedef struct
{
    Robot*      robot;
    Network*    network;
}
Robot_Args;

/**
 * Structure à utiliser en argument lors de l'utilisation de pthread_create avec
 * la méthode des supervisor (Supervisor)
 */
typedef struct
{
    Supervisor* supervisor;
    Network*    network;
}
Supervisor_Args;

typedef struct
{
    Convoyer*   convoyer;
    Network*    network;
}
Convoyer_Args;

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

/**
 * Permet d'initialiser tous les éléments
 * @param  _supervisor   le supervisueur concerné
 * @param  _network      le réseau (totalité du système)
 * @return               le Supervisor_Args nouvellement créé et complété
 */
Supervisor_Args* supervisor_Args_Create(
    Supervisor* _supervisor,
    Network*    _network
);

/**
 * Détruire les arguments
 * @param _robot_Args les arguments à détruire
 */
void supervisor_Args_Destroy(Supervisor_Args* _supervisor_Args);

/**
 * Permet d'initialiser tous les éléments
 * @param  _convoyer le convoyer concerné
 * @param  _network  le réseau (totalité du système)
 * @return           [description]
 */
Convoyer_Args* convoyer_Args_Create(
    Convoyer* _convoyer,
    Network*  _network
);

/**
 * Détruire les arguments
 * @param _convoyer_Args les arguments à détruire
 */
void convoyer_Args_Destroy(Convoyer_Args* _convoyer_Args);

#endif

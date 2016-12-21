/**
 * Auteur: Thomas Gredin
 *
 * Ce fichier contient les prototypes des méthodes qui seront utilisées pour les
 * différents threads du programme
 */

#ifndef THREAD_METHODS_H
#define THREAD_METHODS_H

#include "Supervisor.h"
#include "Convoyer.h"
#include <pthread.h>

/**
 * Structure à utiliser en argument lors de l'utilisation de pthread_create avec
 * la méthode des tables d'usinage (FactoryTable)
 */
typedef struct
{
    FactoryTable*       factoryTable;
    Convoyer*           convoyer;
    Supervisor*         supervisor;

    pthread_cond_t      is_piece_append;
    pthread_mutex_t     padlock;
}
FactoryTable_Args;

/**
 * Thread des tables d'usinage
 * @param args arguments
 */
void* factoryTable_Thread(void* args);
void* supervisor_Thread(void* args);
void* robot_loader_Thread(void* args);
void* robot_unloader_Thread(void* args);
void* convoyer_Thread(void* args);

#endif

/**
 * Auteur: Thomas Gredin
 *
 * Ce fichier contient les prototypes des méthodes qui seront utilisées pour les
 * différents threads du programme
 */

#ifndef THREAD_METHODS_H
#define THREAD_METHODS_H

#include "Supervisor.h"
#include <pthread.h>

typedef struct
{
    FactoryTable* factoryTable;

    pthread_cond_t is_piece_append;
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

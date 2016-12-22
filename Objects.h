/**
 * Auteur: Thomas Gredin
 *
 * Contient toutes les structures
 */

#ifndef OBJECTS_H
#define OBJECTS_H

#include <semaphore.h>

/**
 * Les différents états possibles du système
 */
typedef enum { OK, ERROR } SystemState;

/**
 * Structure qui représente une table d'usinage
 *
 * process_code     : code qui détermine la nature du traitement de la machine
 * is_in_process    : la valeur varie si la machine est en train de traiter une
 *                    pièce ou non
 * is_brocken       : la valeur varie si la machine est en panne ou non
 * position         : position ou doit se trouver la pièce sur le tapis pour que
 *                    la table d'usinage puisse la récupérer et la traiter, c'est
 *                    également l'endroit ou elle sera déposé à la fin du
 *                    traitement
 */
typedef struct
{
    int process_code;
    int is_in_process;
    int is_brocken;
    int is_ready;

    int position;

    pthread_cond_t*     is_piece_append;
    pthread_mutex_t*    padlock;
}
FactoryTable;

typedef struct
{
    int id;
    int process_code;
}
Piece;

typedef struct
{
    Piece* piece;
}
Robot;

/**
 * Structure qui représente le convoyer
 *
 * position     : position actuelle de la pièce se trouvant sur le convoyer si
 *                si pièce il y à
 * loaded_piece : pièce actuellement chargé sur le convoyeur si elle existe
 *                sinon la valeur est sur NULL
 */
typedef struct
{
    int position;
    Piece* loaded_piece;

    sem_t padlock;
}
Convoyer;

typedef struct
{
    SystemState sys_state;
    int convoyer_state;

    FactoryTable* last_target;
}
Supervisor;

typedef struct
{
    Supervisor* supervisor;
    Convoyer* convoyer;

    FactoryTable* table_process_1;
    FactoryTable* table_process_2;
    FactoryTable* table_process_3;

    Robot* robot_loader;
    Robot* robot_unloader;
}
Network;

#endif

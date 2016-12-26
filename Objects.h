/**
 * Auteur: Thomas Gredin
 *
 * Contient toutes les structures
 */

#ifndef OBJECTS_H
#define OBJECTS_H

/**
 * Pour signaler si le système tourne ou non
 */
#define SYSTEM_RUNNING      1
#define SYSTEM_NOT_RUNNING  0

#include <semaphore.h>
#include <sys/time.h>

/**
 * Les différents états possibles du système
 */
typedef enum { OK, ERROR } SystemState;

/**
* Structure qui représente une pièce usinable par le système
*
* id           : identifiant unique de la pièce
* process_code : code qui détermine l'opération d'usinage à effectuer sur
*                sur la pièce et donc la table d'usinage qui devra traiter
*                cette pièce
*/
typedef struct
{
    int id;
    int process_code;
    int is_processed;
}
Piece;

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

    Piece* piece;

    pthread_cond_t     is_piece_append;
    pthread_mutex_t    padlock;

    suseconds_t waited_time;
}
FactoryTable;

/**
 * Structure représentant les robot d'alimentation et de retrait du convoyeur
 *
 * piece : la pièce qui est actuellement tenu par le bras
 */
typedef struct
{
    Piece* piece;

    pthread_cond_t  work_available;
    pthread_mutex_t padlock;
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

/**
 * Structure qui représente le Superviseur du système
 *
 * sys_state        : exprime l'état général du système, on peut donc savoir si
 *                    si ce dernier est OK ou bien en erreur
 * convoyer_state   : exprime l'état connu du convoyeur par le Superviseur
 * last_target      : la dernière table ou l'on doit, ou l'on à envoyé une pièce
 *                    pour qu'elle soit usiné
 */
typedef struct
{
    SystemState sys_state;
    int convoyer_state;
    int is_system_running;

    FactoryTable* last_target;
}
Supervisor;

/**
 * Structure représentant le réseau qu'est le système, il regroupe tout simplement
 * tout les éléments présent sur le réseau.
 */
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

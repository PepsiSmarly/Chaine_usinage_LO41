/**
 * Auteur Thomas Gredin
 *
 * Structure qui va représenter et contenir tous les éléments du système pour
 * faciliter et permettre la communication entre les différents modules du
 * système. Cette structure va en fait représenter le réseau qui existe sur la
 * topologie du sujet
 */

#ifndef NETWORK_H
#define NETWORK_H

#include "Supervisor.h"
#include "Convoyer.h"
#include "FactoryTable.h"
#include "Robot.h"

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

/**
 * Constructeur de Network
 * @return le Network nouvellement crée
 */
Network* network_Create();

/**
 * Destructeur de Network
 * @param _network le Network à détruire
 */
void network_Destroy(Network* _network);

#endif

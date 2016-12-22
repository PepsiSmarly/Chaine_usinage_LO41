/**
 * Auteur: Thomas Gredin
 *
 * Projet LO41 - Modélisation d'une ligne d'usinage
 */

#define SYSTEME_RUN_TRUE    1
#define SYSTEME_RUN_FALSE   0

#include "Config.h"
#include "Supervisor.h"
#include "Convoyer.h"
#include "Robot.h"
#include "Network.h"

void clean_up();

Network* network;

Supervisor* supervisor;
Convoyer* convoyer;

FactoryTable* table_1;
FactoryTable* table_2;
FactoryTable* table_3;

Robot* robot_loader;
Robot* robot_unloader;

int main(int argc, char const *argv[])
{
    network = network_Create();
    printf("network create\n");

    supervisor = supervisor_Create();
    printf("supervisor create\n");
    convoyer = convoyer_Create();
    printf("convoyer create\n");

    table_1 = factoryTable_Create(FACTORY_PROCESS_CODE_1, FACTORYTABLE_POS_1);
    printf("table 1 create\n");
    table_2 = factoryTable_Create(FACTORY_PROCESS_CODE_2, FACTORYTABLE_POS_2);
    printf("table 2 create\n");
    table_3 = factoryTable_Create(FACTORY_PROCESS_CODE_3, FACTORYTABLE_POS_3);
    printf("table 3 create\n");

    robot_loader = robot_Create();
    printf("robot loader create\n");
    robot_unloader = robot_Create();
    printf("robot unloader create\n");

    network->supervisor = supervisor;
    network->convoyer = convoyer;
    network->table_process_1 = table_1;
    network->table_process_2 = table_2;
    network->table_process_3 = table_3;
    network->robot_loader = robot_loader;
    network->robot_unloader = robot_unloader;
    printf("attribution processed\n");

    clean_up();
    return 0;
}

void clean_up()
{
    network_Destroy(network);
    convoyer_Destroy(convoyer);

    factoryTable_Destroy(table_1);
    factoryTable_Destroy(table_2);
    factoryTable_Destroy(table_3);

    robot_Destroy(robot_loader);
    robot_Destroy(robot_unloader);
}
/**
 * TODO: Créer le Supervisor
 */

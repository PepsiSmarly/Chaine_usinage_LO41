/**
 * Auteur: Thomas Gredin
 *
 * Projet LO41 - Modélisation d'une ligne d'usinage
 */

#define SYSTEME_RUN_TRUE    1
#define SYSTEME_RUN_FALSE   0

#include <pthread.h>

#include "Config.h"
#include "Supervisor.h"
#include "Convoyer.h"
#include "Robot.h"
#include "Network.h"

void clean_up();

/**
 * Ce qui permet de lire le fichier de config
 */
Config* config;

/**
 * Tous les éléments du système
 */
Network* network;
Supervisor* supervisor;
Convoyer* convoyer;
FactoryTable* table_1;
FactoryTable* table_2;
FactoryTable* table_3;
Robot* robot_loader;
Robot* robot_unloader;

/**
 * Pour les threads des différents éléments du système
 */
pthread_t thread_supervisor;
pthread_t thread_convoyer;

pthread_t thread_tables_1;
pthread_t thread_tables_2;
pthread_t thread_tables_3;

pthread_t thread_robot_loader;
pthread_t thread_robot_unloader;

int main(int argc, char const *argv[])
{
    /**
     * Initialisation de tous les éléments
     */
    config = config_Create("config.txt");

    network = network_Create();
    printf("network create\n");

    supervisor = supervisor_Create();
    printf("supervisor create\n");
    convoyer = convoyer_Create();
    printf("convoyer create\n");

    table_1 = factoryTable_Create(FACTORY_PROCESS_CODE_1,
        atoi(config_GetField(config, "pos_table_1")));
    printf("table 1 create\n");
    table_2 = factoryTable_Create(FACTORY_PROCESS_CODE_2,
        atoi(config_GetField(config, "pos_table_2")));
    printf("table 2 create\n");
    table_3 = factoryTable_Create(FACTORY_PROCESS_CODE_3,
        atoi(config_GetField(config, "pos_table_3")));
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

    /**
     * Mise en place des threads !
     */
    

    clean_up();
    return 0;
}

void clean_up()
{
    config_Destroy(config);
    printf("free config\n");

    network_Destroy(network);
    printf("free network\n");
    supervisor_Destroy(supervisor);
    printf("free supervisor\n");
    convoyer_Destroy(convoyer);
    printf("free convoyer\n");

    factoryTable_Destroy(table_1);
    printf("free table\n");
    factoryTable_Destroy(table_2);
    printf("free table\n");
    factoryTable_Destroy(table_3);
    printf("free table\n");

    robot_Destroy(robot_loader);
    printf("free robot loader\n");
    robot_Destroy(robot_unloader);
    printf("free robot unloader\n");
}
/**
 * TODO: Créer le Supervisor
 */

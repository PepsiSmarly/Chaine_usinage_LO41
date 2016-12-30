/**
 * Auteur: Thomas Gredin
 *
 * Projet LO41 - Modélisation d'une ligne d'usinage
 */

#define SYSTEME_RUN_TRUE    1
#define SYSTEME_RUN_FALSE   0

#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#include "Config.h"
#include "Supervisor.h"
#include "Convoyer.h"
#include "Robot.h"
#include "Network.h"
#include "ThreadMethods.h"

void clean_up();
void exit_func(int sig);

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

Piece* p;

/**
 * Arguments pour les différents threads
 */
Supervisor_Args* supervisor_args;
Convoyer_Args* convoyer_args;
FactoryTable_Args* factoryTable_1_args;
FactoryTable_Args* factoryTable_2_args;
FactoryTable_Args* factoryTable_3_args;
Robot_Args* robot_loader_args;
Robot_Args* robot_unloader_args;

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
     * Mise en place des signaux !
     */
     signal(SIGINT, exit_func);
     signal(SIGSTOP, exit_func);
     signal(SIGQUIT, exit_func);
     signal(SIGTSTP, exit_func);

    /**
     * Initialisation de tous les éléments
     */
    printf("---------- Création des Objets ----------\n");

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

    printf("---------- Fin création des Objets ----------\n\n");

    /**
     * Construction de tous les arguments pour les threads
     */
    printf("---------- Création des Arguments ----------\n");

    supervisor_args = supervisor_Args_Create(supervisor, network);
    printf("robot supervisor_args create\n");
    convoyer_args = convoyer_Args_Create(convoyer, network);
    printf("robot convoyer_args create\n");

    factoryTable_1_args = factoryTable_Args_Create(table_1, network);
    printf("robot factoryTable_1_args create\n");
    factoryTable_2_args = factoryTable_Args_Create(table_2, network);
    printf("robot factoryTable_2_args create\n");
    factoryTable_3_args = factoryTable_Args_Create(table_3, network);
    printf("robot factoryTable_3_args create\n");

    robot_loader_args = robot_Args_Create(robot_loader, network);
    printf("robot robot_loader_args create\n");
    robot_unloader_args = robot_Args_Create(robot_unloader, network);
    printf("robot robot_unloader_args create\n");

    printf("---------- Fin création des Arguments ----------\n\n");

    printf("Supervisor => running : %d\n\n", supervisor->is_system_running);

    /**
     * Lancement des threads
     */
    printf("---------- Lancement des Threads ----------\n\n");

    pthread_create(&thread_supervisor, NULL, supervisor_Thread, supervisor_args);
    printf("lancement thread Supervisor\n");
    pthread_create(&thread_convoyer, NULL, convoyer_Thread, convoyer_args);
    printf("lancement thread Convoyer\n");

    pthread_create(&thread_tables_1, NULL, factoryTable_Thread, factoryTable_1_args);
    printf("lancement thread FactoryTable 1\n");
    pthread_create(&thread_tables_2, NULL, factoryTable_Thread, factoryTable_2_args);
    printf("lancement thread FactoryTable 2\n");
    pthread_create(&thread_tables_3, NULL, factoryTable_Thread, factoryTable_3_args);
    printf("lancement thread FactoryTable 3\n");

    pthread_create(&thread_robot_loader, NULL, robot_loader_Thread, robot_loader_args);
    printf("lancement thread Robot Loader\n");
    pthread_create(&thread_robot_unloader, NULL, robot_unloader_Thread, robot_unloader_args);
    printf("lancement thread Robot Unloader\n");

    printf("---------- Fin lancement des Threads ----------\n\n");

    // Provisoir
    p = piece_Create(10, FACTORY_PROCESS_CODE_2);
    supervisor->entering_piece = p;
    printf("Supervisor => running : %d\n", supervisor->is_system_running);
    // sleep(10);
    // printf("STOP SYSTEM\n\n");
    // supervisor->is_system_running = SYSTEM_NOT_RUNNING;

    clean_up();

    pthread_exit(0);
}

void clean_up()
{
    /**
     * Attente de la fin de tous les threads avant nettoyage
     * de la mémoire (Destruction de tous les objets)
     */
    pthread_join(thread_supervisor, NULL);
    printf("fin thread Supervisor\n");
    pthread_join(thread_convoyer, NULL);
    printf("fin thread Convoyer\n");

    pthread_join(thread_tables_1, NULL);
    printf("fin thread FactoryTable 1\n");
    pthread_join(thread_tables_2, NULL);
    printf("fin thread FactoryTable 2\n");
    pthread_join(thread_tables_3, NULL);
    printf("fin thread FactoryTable 3\n");

    pthread_join(thread_robot_loader, NULL);
    printf("fin thread Robot Loader\n");
    pthread_join(thread_robot_unloader, NULL);
    printf("fin thread Robot Unloader\n");

    printf("---------- Tous les threads sont terminés ----------\n\n");

    /**
     * Destruction de tous les arguments pour les threads
     */
    printf("---------- Suppression des Arguments ----------\n");

    supervisor_Args_Destroy(supervisor_args);
    printf("free supervisor_args\n");
    convoyer_Args_Destroy(convoyer_args);
    printf("free convoyer_args\n");

    factoryTable_Args_Destroy(factoryTable_1_args);
    printf("free factoryTable_1_args\n");
    factoryTable_Args_Destroy(factoryTable_2_args);
    printf("free factoryTable_2_args\n");
    factoryTable_Args_Destroy(factoryTable_3_args);
    printf("free factoryTable_3_args\n");

    robot_Args_Destroy(robot_loader_args);
    printf("free robot_loader_args\n");
    robot_Args_Destroy(robot_unloader_args);
    printf("free robot_unloader_args\n");

    printf("---------- Fin suppression des Arguments ----------\n\n");

    /**
     * Destruction de tous les objets
     */
    printf("---------- Suppression des Objets ----------\n");

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

    printf("---------- Fin suppression des Objets ----------\n\n");

    piece_Destroy(p);
}

void exit_func(int sig)
{
    convoyer->loaded_piece = NULL;
    supervisor->is_system_running = SYSTEM_NOT_RUNNING;

    pthread_kill(thread_supervisor, SIGKILL);
    pthread_kill(thread_convoyer, SIGKILL);

    pthread_kill(thread_tables_1, SIGKILL);
    pthread_kill(thread_tables_2, SIGKILL);
    pthread_kill(thread_tables_3, SIGKILL);

    pthread_kill(thread_robot_loader, SIGKILL);
    pthread_kill(thread_robot_unloader, SIGKILL);
    signal(SIGINT, exit_func);
}

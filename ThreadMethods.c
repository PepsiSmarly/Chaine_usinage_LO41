#include "ThreadMethods.h"

FactoryTable_Args* factoryTable_Args_Create(
    FactoryTable*   _factoryTable,
    Network*        _network
)
{
    FactoryTable_Args* ft_args = malloc(sizeof(FactoryTable_Args));

    ft_args->factoryTable = _factoryTable;
    ft_args->network = _network;

    return ft_args;
}

void factoryTable_Args_Destroy(FactoryTable_Args* _ft_Args)
{
    if(_ft_Args == NULL)
        return;

    free(_ft_Args);
}

Robot_Args* robot_Args_Create(Robot* _robot, Network* _network)
{
    Robot_Args* ra = malloc(sizeof(Robot_Args));

    ra->robot = _robot;
    ra->network = _network;

    return ra;
}

void robot_Args_Destroy(Robot_Args* _robot_Args)
{
    if(_robot_Args == NULL)
        return;

    free(_robot_Args);
}

Supervisor_Args* supervisor_Args_Create( Supervisor* _supervisor, Network* _network)
{
    Supervisor_Args* args = malloc(sizeof(Supervisor_Args));

    args->supervisor = _supervisor;
    args->network = _network;

    return args;
}

void supervisor_Args_Destroy(Supervisor_Args* _supervisor_Args)
{
    if(_supervisor_Args == NULL)
        return;

    free(_supervisor_Args);
}

Convoyer_Args* convoyer_Args_Create(Convoyer* _convoyer, Network*  _network)
{
    Convoyer_Args* args = malloc(sizeof(Convoyer_Args));

    args->convoyer =  _convoyer;
    args->network = _network;

    return args;
}

void convoyer_Args_Destroy(Convoyer_Args* _convoyer_Args)
{
    if(_convoyer_Args == NULL)
        return;

    free(_convoyer_Args);
}

void* factoryTable_Thread(void* args)
{
    FactoryTable_Args* arg = (FactoryTable_Args*)args;

    while (arg->network->supervisor->is_system_running == SYSTEM_RUNNING)
    {
        int result = factoryTable_EnteringSleep(arg->factoryTable);
        printf("FactoryTable %d : Réveil, code => %d\n", arg->factoryTable->process_code, result);
        if(result == FACTORYTABLE_FALSE)
        {
            supervisor_FactoryTableReport(arg->network->supervisor,
                arg->network->convoyer, FACTORYTABLE_FALSE);
            continue;
        }

        result = factoryTable_WaitPiece(arg->factoryTable,
            arg->network->convoyer);
        if(result == FACTORYTABLE_FALSE)
        {
            supervisor_FactoryTableReport(arg->network->supervisor,
                arg->network->convoyer, FACTORYTABLE_FALSE);
            continue;
        }

        int time_to_process = rand() % FACTORYTABLE_MAX_PROCESS_TIME;
        printf("FactoryTable %d : temps d'usinage => %d secondes\n", arg->factoryTable->process_code, time_to_process);
        sleep(time_to_process);

        result = supervisor_FactoryTableReport(arg->network->supervisor,
            arg->network->convoyer, FACTORYTABLE_TRUE);
        if(result == SUPERVISOR_FAIL)
        {
            continue;
        }

        result = convoyer_Use(arg->network->convoyer, FACTORYTABLE_LOADING_TIME);
        if(result == CONVOYER_FAIL)
        {
            supervisor_FactoryTableReport(arg->network->supervisor,
                arg->network->convoyer, FACTORYTABLE_FALSE);
            continue;
        }

        supervisor_FactoryTableReport(arg->network->supervisor,
            arg->network->convoyer, FACTORYTABLE_TRUE);

        arg->factoryTable->piece->is_processed = PIECE_PROCESSED;

        arg->network->convoyer->loaded_piece = arg->factoryTable->piece;
        arg->factoryTable->piece = NULL;
        convoyer_Free(arg->network->convoyer);

        robot_WakeUp(arg->network->robot_unloader, ROBOT_SUCCESS);
    }

    pthread_exit(0);
}

void* robot_loader_Thread(void* args)
{
    Robot_Args* arg = (Robot_Args*)args;
    double waited_time = 0;
    int results = 0;

    while(arg->network->supervisor->is_system_running == SYSTEM_RUNNING)
    {
        robot_WaitWork(arg->robot);
        printf("Robot Loader : Réveil\n");
        fflush(stdout);

        if(arg->robot->work_to_perform == ROBOT_SUCCESS)
        {
            printf("Robot Loader : Travail disponible\n");
            fflush(stdout);

            while(arg->network->convoyer->loaded_piece != NULL
                && waited_time < ROBOT_LOAD_TIMEOUT)
            {
                waited_time += (clock() / CLOCKS_PER_SEC);
            }

            if(waited_time >= ROBOT_LOAD_TIMEOUT)
            {
                // signaler échec au superviseur
                supervisor_RobotReport(arg->network->supervisor, ROBOT_FAIL);

                continue;
            }
            results = convoyer_Use(arg->network->convoyer,
                ROBOT_LOAD_TIMEOUT - (int)waited_time);
            if(results == CONVOYER_FAIL)
            {
                // Signaler au superviseur l'échec
                supervisor_RobotReport(arg->network->supervisor, ROBOT_FAIL);
                continue;
            }

            arg->network->convoyer->loaded_piece = arg->robot->piece;
            arg->network->convoyer->position = ROBOT_LOADER_POS;
            convoyer_Free(arg->network->convoyer);
            arg->robot->piece = NULL;

            // Signaler succès au superviseur
            supervisor_RobotReport(arg->network->supervisor, ROBOT_SUCCESS);
            waited_time = 0;
        }
    }

    pthread_exit(0);
}

void* robot_unloader_Thread(void* args)
{
    Robot_Args* arg = (Robot_Args*)args;
    double waited_time_start = 0;
    double waited_time_end = 0;
    double waited_time_total = 0;

    while(arg->network->supervisor->is_system_running == SYSTEM_RUNNING)
    {
        robot_WaitWork(arg->robot);
        printf("Robot Unloader : Réveil\n");

        if(arg->robot->work_to_perform == ROBOT_SUCCESS)
        {
            printf("Robot Unloader : Travail disponible\n");

            while(arg->network->convoyer->position != ROBOT_UNLOADER_POS
                && waited_time_total < ROBOT_UNLOAD_TIMEOUT)
            {
                waited_time_start = clock();
                waited_time_end = clock();
                waited_time_total += ((waited_time_end - waited_time_start) / CLOCKS_PER_SEC);
            }

            if(waited_time_total >= ROBOT_UNLOAD_TIMEOUT)
            {
                supervisor_RobotReport(arg->network->supervisor, ROBOT_FAIL);
                continue;
            }

            int result = convoyer_Use(arg->network->convoyer,
                ROBOT_UNLOAD_TIMEOUT - waited_time_total);
            if(result == CONVOYER_FAIL)
            {
                supervisor_RobotReport(arg->network->supervisor, ROBOT_FAIL);
                continue;
            }

            arg->robot->piece = arg->network->convoyer->loaded_piece;
            arg->network->convoyer->loaded_piece = NULL;

            if(arg->robot->piece->is_processed == PIECE_NOT_PROCESSED)
            {
                supervisor_RobotReport(arg->network->supervisor, ROBOT_FAIL);
                continue;
            }

            supervisor_RobotReport(arg->network->supervisor, ROBOT_SUCCESS);
            arg->robot->piece = NULL;

            convoyer_Free(arg->network->convoyer);
            printf("Robot Unloader : Déchargement terminé\n");
            waited_time_total = 0;
        }

    }

    pthread_exit(0);
}

void* supervisor_Thread(void* args)
{
    Supervisor_Args* arg = (Supervisor_Args*)args;

    while(arg->supervisor->is_system_running == SYSTEM_RUNNING)
    {
        fflush(stdout);
        sem_wait(&arg->supervisor->padlock_piece);
        if(arg->supervisor->entering_piece != NULL)
        {
            printf("Superviseur : Entrée d'une pièce dans le système\n");

            int result = supervisor_AppendPiece(
                arg->supervisor,
                arg->supervisor->entering_piece,
                arg->network
            );

            if(result == SUPERVISOR_FAIL)
            {
                arg->supervisor->sys_state = ERROR;
            }
            else
            {
                arg->supervisor->entering_piece = NULL;
                printf("Superviseur : Succès chargement\n");
            }
        }
        sem_post(&arg->supervisor->padlock_piece);

        if(arg->supervisor->sys_state == ERROR)
        {
            printf("Superviseur : ERROR\n");
            arg->supervisor->is_system_running = SYSTEM_NOT_RUNNING;
        }
    }

    /**
     * Réveil des tables d'usinage qui dorment
     */
    factoryTable_WakeUp(arg->network->table_process_1);
    factoryTable_WakeUp(arg->network->table_process_2);
    factoryTable_WakeUp(arg->network->table_process_3);

    /**
     * Réveil des robots de chargement/déchargement
     */
    robot_WakeUp(arg->network->robot_loader, ROBOT_FAIL);
    robot_WakeUp(arg->network->robot_unloader, ROBOT_FAIL);

    pthread_exit(0);
}

void* convoyer_Thread(void* args)
{
    Convoyer_Args* arg = (Convoyer_Args*)args;

    while(arg->network->supervisor->is_system_running == SYSTEM_RUNNING)
    {
        // printf("Convoyeur : Pas de pièce\n");
        // fflush(stdout);
        if(arg->convoyer->loaded_piece != NULL)
        {
            printf("Convoyeur : Position de la pièce sur le convoyeur : %d\n",
                arg->convoyer->position);
            fflush(stdout);
            if(arg->convoyer->position < 100)
            {
                convoyer_Move(arg->convoyer);
            }
            else if(arg->convoyer->position > 100)
            {
                arg->convoyer->position = 100;
            }
        }
        usleep(CONVOYER_MOVE_TIME);
    }

    pthread_exit(0);
}

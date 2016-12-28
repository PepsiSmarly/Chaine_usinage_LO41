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

        while(arg->network->convoyer->loaded_piece != NULL
            && waited_time < ROBOT_LOAD_TIMEOUT)
        {
            waited_time += clock() / CLOCKS_PER_SEC;
        }

        if(waited_time >= ROBOT_LOAD_TIMEOUT)
        {
            // signaler échec au superviseur
            supervisor_LoadingReport(arg->network->supervisor, ROBOT_FAIL);

            continue;
        }
        results = convoyer_Use(arg->network->convoyer,
            ROBOT_LOAD_TIMEOUT - (int)waited_time);
        if(results == CONVOYER_FAIL)
        {
            // Signaler au superviseur l'échec
            supervisor_LoadingReport(arg->network->supervisor, ROBOT_FAIL);

            continue;
        }

        arg->network->convoyer->loaded_piece = arg->robot->piece;
        arg->network->convoyer->position = ROBOT_LOADER_POS;
        convoyer_Free(arg->network->convoyer);
        arg->robot->piece = NULL;

        // Signaler succès au superviseur
        supervisor_LoadingReport(arg->network->supervisor, ROBOT_SUCCESS);
    }

    pthread_exit(0);
}

void* robot_unloader_Thread(void* args)
{
    pthread_exit(0);
}

void* supervisor_Thread(void* args)
{
    Supervisor_Args* arg = (Supervisor_Args*)args;

    while(arg->supervisor->is_system_running == SYSTEM_RUNNING)
    {
        sem_wait(&arg->supervisor->padlock_piece);
        if(arg->supervisor->entering_piece != NULL)
        {
            supervisor_AppendPiece(
                arg->supervisor,
                arg->supervisor->entering_piece,
                arg->network
            );

            arg->supervisor->entering_piece = NULL;
        }
        sem_post(&arg->supervisor->padlock_piece);

        if(arg->supervisor->sys_state == ERROR)
        {
            arg->supervisor->is_system_running = SYSTEM_NOT_RUNNING;
        }
    }

    pthread_exit(0);
}

void* convoyer_Thread(void* args)
{
    pthread_exit(0);
}

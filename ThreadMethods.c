#include "ThreadMethods.h"

void* factoryTable_Thread(void* args)
{
    FactoryTable_Args* arg = (FactoryTable_Args*)args;

    pthread_exit(0);
}

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

void* robot_loader_Thread(void* args)
{
    Robot_Args* arg = (Robot_Args*)args;
    double waited_time = 0;

    while(arg->network->supervisor->is_system_running != SYSTEM_NOT_RUNNING)
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

            continue;
        }
        convoyer_Use(arg->network->convoyer,
            ROBOT_LOAD_TIMEOUT - (int)waited_time);
    }

    pthread_exit(0);
}

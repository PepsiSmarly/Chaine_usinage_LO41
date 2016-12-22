#include "ThreadMethods.h"

void* factoryTable_Thread(void* args)
{
    FactoryTable_Args* args = (FactoryTable_Args*)args;

}

FactoryTable_Args* factoryTable_Args_Create(
    FactoryTable*   _factoryTable,
    Network*        _network
)
{
    FactoryTable_Args* ft_args = malloc(sizeof(FactoryTable_Args));

    ft_args->factoryTable = _factoryTable;
    ft_args->network = _network;

    pthread_mutex_init(ft_args->padlock, 0);
    pthread_cond_init(ft_args->is_piece_append, 0);

    return ft_args;
}

void factoryTable_Args_Destroy(FactoryTable_Args* _ft_Args)
{
    if(_ft_Args == NULL)
        return;
    free(_ft_Args);
}

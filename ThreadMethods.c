#include "ThreadMethods.h"

void* factoryTable_Thread(void* args)
{
    FactoryTable_Args* args = (FactoryTable_Args*)args;

}

FactoryTable_Args* factoryTable_Args_Create(
    FactoryTable*   _factoryTable,
    Supervisor*     _supervisor,
    Convoyer*       _convoyer
)
{
    FactoryTable_Args* ft_args = malloc(sizeof(FactoryTable_Args));

    ft_args->factoryTable = _factoryTable;
    ft_args->supervisor = _supervisor;
    ft_args->convoyer = _convoyer;

    pthread_cond_init(ft_args->is_piece_append, NULL);
}

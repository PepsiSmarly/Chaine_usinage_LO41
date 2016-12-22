#include "FactoryTable.h"

FactoryTable* factoryTable_Create(int _process_code, int _position)
{
    FactoryTable* ft = malloc(sizeof(FactoryTable));

    ft->is_in_process = FACTORYTABLE_FALSE;
    ft->position = _position;
    ft->process_code = _process_code;
    ft->is_brocken = FACTORYTABLE_FALSE;
    ft->is_ready = FACTORYTABLE_FALSE;

    pthread_mutex_init(ft_args->padlock, 0);
    pthread_cond_init(ft_args->is_piece_append, 0);

    return ft;
}

void factoryTable_Destroy(FactoryTable* _factoryTable)
{
    if(_ft == NULL)
        return;

    pthread_mutex_destroy(_factoryTable->padlock);
    pthread_cond_destroy(_factoryTable->is_piece_append);
    free(_ft);
}

int factoryTable_LoadPieceOnConvoyer(FactoryTable* _factoryTable, Convoyer* _convoyer)
{

}

void factoryTable_SignalConvoyerToSupervisor(FactoryTable* _factoryTable,
                                            Supervisor* _supervisor,
                                            int _code)
{

}

int factoryTable_WakeUp(FactoryTable* _factoryTable)
{
    if(_factoryTable->is_in_process == FACTORYTABLE_TRUE)
    {
        return FACTORYTABLE_FALSE;
    }

    int result = pthread_cond_signal(_factoryTable->is_piece_append);
    if(result != 0)
    {
        return FACTORYTABLE_FALSE;
    }
    return FACTORYTABLE_TRUE;
}

#include "FactoryTable.h"

FactoryTable* factoryTable_Create(int _process_code, int _position)
{
    FactoryTable* ft = malloc(sizeof(FactoryTable));

    ft->is_in_process = FACTORYTABLE_FALSE;
    ft->position = _position;
    ft->process_code = _process_code;
    ft->is_brocken = FACTORYTABLE_FALSE;
    ft->is_ready = FACTORYTABLE_FALSE;

    pthread_mutex_init(&ft->padlock, 0);
    pthread_cond_init(&ft->is_piece_append, 0);

    ft->waited_time = 0L;

    return ft;
}

void factoryTable_Destroy(FactoryTable* _factoryTable)
{
    if(_factoryTable == NULL)
        return;

    pthread_mutex_destroy(&_factoryTable->padlock);
    pthread_cond_destroy(&_factoryTable->is_piece_append);
    free(_factoryTable);
}

int factoryTable_WakeUp(FactoryTable* _factoryTable)
{
    if(_factoryTable->is_in_process == FACTORYTABLE_TRUE)
    {
        return FACTORYTABLE_FALSE;
    }

    int result = pthread_cond_signal(&_factoryTable->is_piece_append);
    if(result != 0)
    {
        return FACTORYTABLE_FALSE;
    }
    return FACTORYTABLE_TRUE;
}

int factoryTable_WaitPiece(FactoryTable* _factoryTable, Convoyer* _convoyer)
{
    struct timeval before_time, after_time;
    gettimeofday(&before_time, NULL);

    int lower_mark = _factoryTable->position - FACTORYTABLE_CONVOYER_INTERVAL;
    int upper_mark = _factoryTable->position + FACTORYTABLE_CONVOYER_INTERVAL;

    if(_convoyer->position >= lower_mark && _convoyer->position <= upper_mark)
    {
        int result = convoyer_Use(_convoyer, FACTORYTABLE_EXTRACT_TIME -
            (_factoryTable->waited_time / 1000000));

        if(result == CONVOYER_FAIL)
        {
            gettimeofday(&after_time, NULL);
            _factoryTable->waited_time +=
                before_time.tv_usec - after_time.tv_usec;

            return FACTORYTABLE_FALSE;
        }

        _factoryTable->piece = _convoyer->loaded_piece;
        _convoyer->loaded_piece = NULL;

        convoyer_Free(_convoyer);
        _factoryTable->waited_time = 0L;

        return FACTORYTABLE_TRUE;
    }
    else
    {
        gettimeofday(&after_time, NULL);
        _factoryTable->waited_time += before_time.tv_usec - after_time.tv_usec;

        return FACTORYTABLE_FALSE;
    }

}

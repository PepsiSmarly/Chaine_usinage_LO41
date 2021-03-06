#include "FactoryTable.h"

FactoryTable* factoryTable_Create(int _process_code, int _position)
{
    FactoryTable* ft = malloc(sizeof(FactoryTable));

    ft->is_in_process = FACTORYTABLE_FALSE;
    ft->position = _position;
    ft->process_code = _process_code;
    ft->is_brocken = FACTORYTABLE_FALSE;
    ft->is_ready = FACTORYTABLE_FALSE;

    ft->piece = NULL;

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

int factoryTable_LoadPieceOnConvoyer(FactoryTable* _factoryTable, Convoyer* _convoyer)
{
    if(_factoryTable->piece != NULL)
    {
        int result = convoyer_Use(_convoyer, FACTORYTABLE_LOADING_TIME);
        if(result == CONVOYER_FAIL)
        {
            return FACTORYTABLE_FALSE;
        }

        _convoyer->loaded_piece = _factoryTable->piece;
        _factoryTable->piece = NULL;
        convoyer_Free(_convoyer);

        return FACTORYTABLE_TRUE;
    }

    return FACTORYTABLE_FALSE;
}

int factoryTable_EnteringSleep(FactoryTable* _factoryTable)
{
    pthread_mutex_lock(&_factoryTable->padlock);
    if(_factoryTable->is_in_process == FACTORYTABLE_FALSE)
    {
        printf("FactoryTable %d : Mise en attente\n", _factoryTable->process_code);
        pthread_cond_wait(&_factoryTable->is_piece_append, &_factoryTable->padlock);

        return FACTORYTABLE_TRUE;
    }

    printf("FactoryTable %d : Ne peut être mis en attente...\n", _factoryTable->process_code);
    pthread_mutex_unlock(&_factoryTable->padlock);
    return FACTORYTABLE_FALSE;
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
    printf("FactoryTable %d : Réveil\n", _factoryTable->process_code);

    return FACTORYTABLE_TRUE;
}

int factoryTable_WaitPiece(FactoryTable* _factoryTable, Convoyer* _convoyer)
{
    double waited_time_start = 0;
    double waited_time_end = 0;
    double waited_time_total = 0;

    int lower_mark = _factoryTable->position - FACTORYTABLE_CONVOYER_INTERVAL;
    int upper_mark = _factoryTable->position + FACTORYTABLE_CONVOYER_INTERVAL;

    while(_convoyer->position < lower_mark && waited_time_total < FACTORYTABLE_EXTRACT_TIME)
    {
        waited_time_start = clock();
        waited_time_end = clock();
        waited_time_total += (waited_time_end - waited_time_start) / CLOCKS_PER_SEC;
        continue;
    }

    printf("FactoryTable %d : Temps attendu de %lf secondes\n", _factoryTable->process_code, waited_time_total);

    if(_convoyer->position >= lower_mark && _convoyer->position <= upper_mark
            && waited_time_total < FACTORYTABLE_EXTRACT_TIME)
    {
        printf("FactoryTable %d : Temps d'attente de %lf secondes\n", _factoryTable->process_code, waited_time_total);
        int result = convoyer_Use(_convoyer, FACTORYTABLE_EXTRACT_TIME - waited_time_total);

        if(result == CONVOYER_FAIL)
        {
            printf("FactoryTable %d : Impossible de prendre le convoyeur\n", _factoryTable->process_code);
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
        printf("FactoryTable %d : Impossible de prendre le convoyeur 2\n", _factoryTable->process_code);
        return FACTORYTABLE_FALSE;
    }

}

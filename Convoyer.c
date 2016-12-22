#include "Convoyer.h"

Convoyer* convoyer_Create()
{
    Convoyer* c = malloc(sizeof(Convoyer));

    c->loaded_piece = NULL;
    c->position = CONVOYER_NO_PIECE_POS;

    sem_init(&c->padlock, 0, CONVOYER_CAPACITY);
}

void convoyer_Destroy(Convoyer* _convoyer)
{
    if(_convoyer == NULL)
        return;

    sem_destroy(&_convoyer->padlock);
    free(_convoyer);
}

int convoyer_Use(Convoyer* _convoyer)
{
    struct timespec ts;
    ts.tv_sec = 20;

    int result = sem_timedwait(&_convoyer->padlock, &ts);
    if(result != 0)
    {
        return CONVOYER_FAIL;
    }
    return CONVOYER_SUCCESS;
}

void convoyer_Free(Convoyer* _convoyer)
{
    sem_post(&_convoyer->padlock);
}

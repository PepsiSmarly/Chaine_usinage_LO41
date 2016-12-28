#include "Convoyer.h"

Convoyer* convoyer_Create()
{
    Convoyer* c = malloc(sizeof(Convoyer));

    c->position = CONVOYER_NO_PIECE_POS;

    sem_init(&c->padlock, 0, CONVOYER_CAPACITY);
    return c;
}

void convoyer_Destroy(Convoyer* _convoyer)
{
    if(_convoyer == NULL)
        return;

    sem_destroy(&_convoyer->padlock);
    free(_convoyer);
}

int convoyer_Use(Convoyer* _convoyer, int _timeout_s)
{
    struct timespec ts;
    ts.tv_sec = _timeout_s;

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

void convoyer_Move(Convoyer* _convoyer)
{
    sem_wait(&_convoyer->padlock);
    if(_convoyer->position == -1)
    {
        return;
    }

    _convoyer->position += CONVOYER_SPEED;
    sem_post(&_convoyer->padlock);
}

#include "Convoyer.h"

Convoyer* convoyer_Create()
{
    Convoyer* c = malloc(sizeof(Convoyer));

    c->position = CONVOYER_NO_PIECE_POS;
    c->loaded_piece = NULL;

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
    double waited_time = 0;

    printf("Convoyer : Tentative de monopolisation pendant %d secondes\n", _timeout_s);
    fflush(stdout);

    int result;
    while((result = sem_trywait(&_convoyer->padlock)) == -1 && waited_time < _timeout_s)
    {
        printf("Convoyer : Impossible de monopoliser pour le moment...\n");
        fflush(stdout);
        continue;
    }
    printf("Convoyer : sem_timedwait code : %d\n", result);
    if(result != 0)
    {
        printf("Convoyer : Attente pour utilisation dépassé\n");
        fflush(stdout);
        return CONVOYER_FAIL;
    }
    printf("Convoyer : Succès de la demande d'utilisation\n");
    fflush(stdout);
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

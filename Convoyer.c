#include "Convoyer.h"

Convoyer* convoyer_Create()
{
    Convoyer* c = malloc(sizeof(Convoyer));

    c->loaded_piece = NULL;
    c->position = CONVOYER_NO_PIECE_POS;

    sem_init(c->padlock, 0, CONVOYER_CAPACITY);
}

void convoyer_Destroy(Convoyer* _convoyer)
{
    if(_convoyer == NULL)
        return;

    sem_destroy(&_convoyer->padlock);
    free(_convoyer);
}

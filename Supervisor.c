#include "Supervisor.h"

Supervisor* supervisor_Create()
{
    Supervisor* s = malloc(sizeof(Supervisor));

    s->sys_state = OK;
    s->sys_state = CONVOYER_FREE;

    return s;
}

void supervisor_Destroy(Supervisor* _supervisor)
{
    if(_supervisor == NULL)
        return;
    free(_supervisor);
}

int supervisor_AppendPiece(Supervisor* _supervisor, Piece* _piece)
{

}

int supervisor_DetermineFactoryTable(Supervisor* _supervisor, Piece* _piece)
{

}

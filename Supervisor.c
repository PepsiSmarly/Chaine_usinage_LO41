#include "Supervisor.h"

Supervisor* supervisor_Create()
{
    Supervisor* s = malloc(sizeof(Supervisor));

    s->sys_state = OK;
    s->sys_state = CONVOYER_FREE;
    s->last_target = NULL;

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
    int result = supervisor_DetermineFactoryTable(_supervisor, _piece);

    if(result == SUPERVISOR_SUCCESS)
    {
        if(_supervisor->last_target == NULL)
        {
            return SUPERVISOR_FAIL;
        }

        
        return SUPERVISOR_SUCCESS;
    }
    else
    {
        return SUPERVISOR_FAIL;
    }
}

int supervisor_DetermineFactoryTable(Supervisor* _supervisor, Piece* _piece)
{
    int code = _piece->process_code;


}

void supervisor_changeConvoyerState(Supervisor* _supervisor, int _state)
{
    _supervisor->convoyer_state = _state;
}

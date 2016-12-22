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

int supervisor_AppendPiece(Supervisor* _supervisor, Piece* _piece, Network* _network)
{
    int result = supervisor_DetermineFactoryTable(_supervisor, _piece, _network);

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

int supervisor_DetermineFactoryTable(Supervisor* _supervisor, Piece* _piece, Network* _network)
{
    int code = _piece->process_code;

    switch (code) {
        case _network->table_process_1->process_code:
        {
            _supervisor->last_target = _network->table_process_1;
            break;
        }
        case _network->table_process_2->process_code:
        {
            _supervisor->last_target = _network->table_process_2;
            break;
        }
        case _network->table_process_3->process_code:
        {
            _supervisor->last_target = _network->table_process_3;
            break;
        }
        default:
        {
            return SUPERVISOR_FAIL;
        }
    }
    return SUPERVISOR_SUCCESS;
}

void supervisor_changeConvoyerState(Supervisor* _supervisor, int _state)
{
    _supervisor->convoyer_state = _state;
}

#include "Supervisor.h"

Supervisor* supervisor_Create()
{
    Supervisor* s = malloc(sizeof(Supervisor));

    s->sys_state = OK;
    s->sys_state = CONVOYER_FREE;
    s->is_system_running = SYSTEM_RUNNING;

    s->last_target = NULL;
    s->entering_piece = NULL;

    sem_init(&s->padlock_lt, 0, 1);
    sem_init(&s->padlock_piece, 0, 1);

    return s;
}

void supervisor_Destroy(Supervisor* _supervisor)
{
    if(_supervisor == NULL)
        return;

    sem_destroy(&_supervisor->padlock_lt);
    sem_destroy(&_supervisor->padlock_piece);

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

        result = factoryTable_WakeUp(_supervisor->last_target);
        if(result == FACTORYTABLE_FALSE)
        {
            return SUPERVISOR_FAIL;
        }

        _network->robot_loader->piece = _piece;
        robot_WakeUp(_network->robot_loader);

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
        case FACTORY_PROCESS_CODE_1:
        {
            _supervisor->last_target = _network->table_process_1;
            break;
        }
        case FACTORY_PROCESS_CODE_2:
        {
            _supervisor->last_target = _network->table_process_2;
            break;
        }
        case FACTORY_PROCESS_CODE_3:
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

void supervisor_LoadingReport(Supervisor* _supervisor, int _code)
{
    if(_code == ROBOT_FAIL)
    {
        _supervisor->sys_state = ERROR;
    }
}

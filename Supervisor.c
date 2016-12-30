#include "Supervisor.h"

Supervisor* supervisor_Create()
{
    Supervisor* s = malloc(sizeof(Supervisor));

    s->sys_state = OK;
    s->convoyer_state = CONVOYER_FREE;
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
    printf("Supervisor : Table d'usinage déterminée : %d !\n", _supervisor->last_target->process_code);

    if(result == SUPERVISOR_SUCCESS)
    {
        printf("Superviseur : Table d'usinage déterminée\n");
        if(_supervisor->last_target == NULL)
        {
            return SUPERVISOR_FAIL;
        }

        sem_wait(&_supervisor->padlock_lt);
        result = factoryTable_WakeUp(_supervisor->last_target);
        sem_post(&_supervisor->padlock_lt);
        if(result == FACTORYTABLE_FALSE)
        {
            return SUPERVISOR_FAIL;
        }

        robot_SetPiece(_network->robot_loader, _piece);
        printf("Superviseur : Insertion de la nouvelle pièce dans le robot de chargement\n");
        robot_WakeUp(_network->robot_loader, ROBOT_SUCCESS);

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

    printf("Superviseur : Table d'usinage en cours de détermination\n");
    sem_wait(&_supervisor->padlock_lt);
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
            sem_post(&_supervisor->padlock_lt);
            return SUPERVISOR_FAIL;
        }
    }
    sem_post(&_supervisor->padlock_lt);
    printf("Superviseur : Détermination de table d'usinage terminée\n");
    return SUPERVISOR_SUCCESS;
}

void supervisor_changeConvoyerState(Supervisor* _supervisor, int _state)
{
    _supervisor->convoyer_state = _state;
}

void supervisor_RobotReport(Supervisor* _supervisor, int _code)
{
    if(_code == ROBOT_FAIL)
    {
        _supervisor->sys_state = ERROR;
    }
}

int supervisor_FactoryTableReport(Supervisor* _supervisor, Convoyer* _convoyer, int _code)
{
    if(_code == FACTORYTABLE_FALSE)
    {
        _supervisor->sys_state = ERROR;
        return SUPERVISOR_FAIL;
    }

    while(_convoyer->loaded_piece != NULL && _supervisor->is_system_running);

    return SUPERVISOR_SUCCESS;
}

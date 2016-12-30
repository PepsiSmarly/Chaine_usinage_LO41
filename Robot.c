#include "Robot.h"

Robot* robot_Create()
{
    Robot* r = malloc(sizeof(Robot));

    r->work_to_perform = ROBOT_FAIL;
    r->piece = NULL;
    sem_init(&r->padlock_piece, 0, 1);

    pthread_mutex_init(&r->padlock, NULL);
    pthread_cond_init(&r->work_available, NULL);

    return r;
}

void robot_Destroy(Robot* _robot)
{
    if(_robot == NULL)
        return;

    sem_destroy(&_robot->padlock_piece);

    pthread_mutex_destroy(&_robot->padlock);
    pthread_cond_destroy(&_robot->work_available);
    free(_robot);
}

int robot_LoadConvoyer(Robot* _robot, Convoyer* _convoyer)
{
    int result = convoyer_Use(_convoyer, 20);
    if(result == CONVOYER_FAIL)
    {
        return ROBOT_FAIL;
    }

    printf("Robot : Chargement pièce sur le convoyeur !\n");
    _convoyer->loaded_piece = _robot->piece;
    _convoyer->position = ROBOT_LOADER_POS;
    convoyer_Free(_convoyer);
    _robot->piece = NULL;
    return ROBOT_SUCCESS;
}

int robot_UnloadConvoyer(Robot* _robot, Convoyer* _convoyer)
{
    int result = convoyer_Use(_convoyer, 30);
    if(result == CONVOYER_FAIL)
    {
        return ROBOT_FAIL;
    }

    _robot->piece = _convoyer->loaded_piece;
    _convoyer->loaded_piece = NULL;
    _convoyer->position = CONVOYER_NO_PIECE_POS;
    convoyer_Free(_convoyer);

    return ROBOT_SUCCESS;
}

void robot_WaitWork(Robot* _robot)
{
    pthread_mutex_lock(&_robot->padlock);
    _robot->work_to_perform = ROBOT_FAIL;
    pthread_cond_wait(&_robot->work_available, &_robot->padlock);
}

void robot_WakeUp(Robot* _robot, int _work_to_perform)
{
    pthread_mutex_lock(&_robot->padlock);
    pthread_cond_signal(&_robot->work_available);
    printf("Robot : Travail disponible !\n");
    _robot->work_to_perform = _work_to_perform;
    pthread_mutex_unlock(&_robot->padlock);
}

void robot_SetPiece(Robot* _robot, Piece* _piece)
{
    sem_wait(&_robot->padlock_piece);
    _robot->piece = _piece;
    sem_post(&_robot->padlock_piece);
}

#include "Robot.h"

Robot* robot_Create()
{
    Robot* r = malloc(sizeof(Robot));

    return r;
}

void robot_Destroy(Robot* _robot)
{
    if(_robot == NULL)
        return;

    free(_robot);
}

int robot_LoadConvoyer(Robot* _robot, Convoyer* _convoyer)
{
    int result = convoyer_Use(_convoyer, 20);

    if(result == CONVOYER_FAIL)
    {
        return ROBOT_FAIL;
    }

    _convoyer->loaded_piece = _robot->piece;
    convoyer_Free(_convoyer);
    _robot->piece = NULL;
    return ROBOT_SUCCESS;
}

int robot_UnloadConvoyer(Robot* _robot, Convoyer* _convoyer)
{

}

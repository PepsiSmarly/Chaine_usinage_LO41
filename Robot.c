#include "Robot.h"

Robot* robot_Create()
{
    Robot* r = malloc(sizeof(Robot));

    r->piece = NULL;
    return r;
}

void robot_Destroy(Robot* _robot)
{
    if(_robot == NULL)
        return;

    free(_robot);
}

int robot_loadConvoyer(Robot* _robot, Convoyer* _convoyer)
{

}

int robot_unloadConvoyer(Robot* _robot, Convoyer* _convoyer)
{
    
}

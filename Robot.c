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

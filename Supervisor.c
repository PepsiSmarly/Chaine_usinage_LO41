#include "Supervisor.h"

Supervisor* supervisor_Create()
{
    Supervisor* s = malloc(sizeof(Supervisor));

    s->sys_state = OK;

    return s;
}

void supervisor_Destroy(Supervisor* _supervisor)
{
    if(_supervisor == NULL)
        return;
    free(_supervisor);
}

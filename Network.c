#include "Network.h"

Network* network_Create()
{
    Network* n = (Network*)malloc(sizeof(Network));

    n->supervisor = NULL;
    n->convoyer = NULL;

    n->table_process_1 = NULL;
    n->table_process_2 = NULL;
    n->table_process_3 = NULL;

    n->robot_loader = NULL;
    n->robot_unloader = NULL;

    return n;
}

void network_Destroy(Network* _network)
{
    if(_network == NULL)
        return;

    // free(_network->supervisor);
    // free(_network->convoyer);
    //
    // free(_network->table_process_1);
    // free(_network->table_process_2);
    // free(_network->table_process_3);
    //
    // free(_network->robot_loader);
    // free(_network->robot_unloader);

    free(_network);
}

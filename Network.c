#include "Network.h"

Network* network_Create()
{
    Network* n = (Network*)malloc(sizeof(Network));

    n->supervisor = malloc(sizeof(Supervisor));
    n->convoyer = malloc(sizeof(Convoyer));

    n->table_process_1 = malloc(sizeof(FactoryTable));
    n->table_process_2 = malloc(sizeof(FactoryTable));
    n->table_process_3 = malloc(sizeof(FactoryTable));

    n->robot_loader = malloc(sizeof(Robot));
    n->robot_unloader = malloc(sizeof(Robot));

    return n;
}

void network_Destroy(Network* _network)
{
    if(_network == NULL)
        return;

    free(_network->supervisor);
    free(_network->convoyer);

    free(_network->table_process_1);
    free(_network->table_process_2);
    free(_network->table_process_3);

    free(_network->robot_loader);
    free(_network->robot_unloader);

    free(_network);
}

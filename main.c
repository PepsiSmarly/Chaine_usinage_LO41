/**
 * Auteur: Thomas Gredin
 *
 * Projet LO41 - Modélisation d'une ligne d'usinage
 */

#define SYSTEME_RUN_TRUE    1
#define SYSTEME_RUN_FALSE   0

#include "Config.h"
#include "Network.h"

void clean_up();

Network* network;

int main(int argc, char const *argv[])
{
    network = network_Create();

    clean_up();
    return 0;
}

void clean_up()
{
    network_Destroy(network);
}
/**
 * TODO: Créer le Supervisor
 */

/**
 * Auteur Thomas Gredin
 *
 * Structure qui va représenter et contenir tous les éléments du système pour
 * faciliter et permettre la communication entre les différents modules du
 * système. Cette structure va en fait représenter le réseau qui existe sur la
 * topologie du sujet
 */

#ifndef NETWORK_H
#define NETWORK_H

#include "Objects.h"

/**
 * Constructeur de Network
 * @return le Network nouvellement crée
 */
Network* network_Create();

/**
 * Destructeur de Network
 * @param _network le Network à détruire
 */
void network_Destroy(Network* _network);

#endif

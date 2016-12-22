/**
 * Auteur: Thomas Gredin
 *
 * Représente les tables d'usinage
 */

#ifndef FACTORY_TABLE_H
#define FACTORY_TABLE_H

#define FACTORYTABLE_TRUE   1
#define FACTORYTABLE_FALSE  0

/**
 * Les différents code dont les pièces se muniront pour spécifier les opérations
 * d'usinage qu'elles demandent et donc les tables d'usinage vers lesquelles elles
 * doivent être conduitent
 */
#define FACTORY_PROCESS_CODE_1 10
#define FACTORY_PROCESS_CODE_2 20
#define FACTORY_PROCESS_CODE_3 30

#include <stdlib.h>
#include "pthread.h"

#include "Convoyer.h"
#include "Supervisor.h"
#include "Piece.h"

/**
 * Créer une Table d'usinage
 * @param  _process_code le numéro de process qui sera appliqué aux pièces
 * @param  _position     position de la pièce sur le tapis pour pouvoir effectuer
 *                       une récupération de la pièce
 * @return               la table nouvellement créée
 */
FactoryTable*   factoryTable_Create(int _process_code, int _position);

/**
 * Détruire la table d'usinage
 * @param  _ft table d'usinage à détruire
 */
void            factoryTable_Destroy(FactoryTable* _factoryTable);

/**
 * Permet de charger une pièce provenant d'une table d'usinage sur le convoyeur
 * donnée tout en vérifiant bien que ce dernier est disponible pour recevoir et
 * transporter une pièce
 * @param  _factoryTable table d'usinage à décharger
 * @param  _convoyer     convoyeur sur lequel charger la pièce
 * @return               FACTORYTABLE_TRUE si succès et FACTORYTABLE_FALSE si
 *                       échec
 */
int             factoryTable_LoadPieceOnConvoyer(FactoryTable* _factoryTable,
                                Convoyer* _convoyer);

/**
 * Signal un changement d'état du convoyeur au Superviseur suite à une
 * manipulation mené par la table (chargement, déchargement de pièce)
 * @param  _factoryTable la table émetrice du changement
 * @param  _supervisor   le Superviseur
 * @param  _code         le code d'état du convoyeur (voir Convoyer.h)
 */
void            factoryTable_SignalConvoyerToSupervisor(
                                FactoryTable* _factoryTable,
                                Supervisor* _supervisor,
                                int _code);

/**
 * Permet de "réveiller" la table d'usinage pour l'arriver d'une pièce à traiter
 * @param  _factoryTable la table à réveiller
 * @return               FACTORYTABLE_TRUE en cas de succès,
 *                       FACTORYTABLE_FALSE dans les autres cas
 */
int             factoryTable_WakeUp(FactoryTable* _factoryTable);

#endif

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

/**
 * Les différentes positions de chacune des tables d'usinage par rapport au
 * tapis
 */
#define FACTORYTABLE_POS_1 25
#define FACTORYTABLE_POS_2 50
#define FACTORYTABLE_POS_3 75

/**
 * Constante qui indique la marge de position possible pour que les tables
 * d'usinage puissent prendre les pièces sur le tapis. Ainsi pour former
 * l'intervalle ou la pièce peut être prise par la table, on prend la position
 * de cette dernière et pour la borne basse on lui soustrait cette constante, en
 * ce qui converne la borne haute, on lui additionne.
 *
 * borne basse = pos - FACTORYTABLE_CONVOYER_INTERVAL
 * borne haute = pos + FACTORYTABLE_CONVOYER_INTERVAL
 */
#define FACTORYTABLE_CONVOYER_INTERVAL 5

/**
 * Représente le temps que possède la table pour extraire la pièce du tapis une
 * fois que le convoyeur l'a prévenu de l'arrivée de cette dernière
 */
#define FACTORYTABLE_EXTRACT_TIME 50

/**
 * Représente le temps qui va être attendu par la table d'usinage pour tenter
 * de déposer la pièce qui vient d'être usiné sur le convoyeur une fois que le
 * compte rendu d'usinage aura été examiné par le Superviseur et que l'ordre de
 * dépôt aura été donné par ce dernier
 */
#define FACTORYTABLE_LOADING_TIME 2

#include <stdlib.h>
#include <pthread.h>

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
 * Permet de mettre la table dans état d'attente, elle attend que le Superviseur
 * la réveille, ce qui signifie qu'une pièce qui lui est destiné est injectée
 * dans le système
 * @param  _factoryTable la table à "endormir"
 */
int             factoryTable_EnteringSleep(FactoryTable* _factoryTable);

/**
 * Permet de "réveiller" la table d'usinage pour l'arriver d'une pièce à traiter
 * @param  _factoryTable la table à réveiller
 * @return               FACTORYTABLE_TRUE en cas de succès,
 *                       FACTORYTABLE_FALSE dans les autres cas
 */
int             factoryTable_WakeUp(FactoryTable* _factoryTable);

/**
 * Permet d'attendre la pièce en scrutant le convoyeur, mais la table stop son
 * observation au bout de 50 secondes
 * @param  _factoryTable la table qui observe
 * @param  _convoyer     le convoyeur à observer
 * @return               FACTORYTABLE_TRUE en cas de succès
 *                       FACTORYTABLE_FALSE en cas d'échec
 */
int             factoryTable_WaitPiece(FactoryTable* _factoryTable, Convoyer* _convoyer);

#endif

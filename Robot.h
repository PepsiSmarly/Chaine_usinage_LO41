/**
 * Auteur: Thomas Gredin
 *
 * Représente les robots de chargement et de retrait du convoyeur
 */

#ifndef ROBOT_H
#define ROBOT_H

#define ROBOT_SUCCESS   1
#define ROBOT_FAIL      0

#define ROBOT_LOADER_POS    0
#define ROBOT_UNLOADER_POS  100

#include "Objects.h"
#include "Piece.h"
#include "Convoyer.h"

/**
 * Constructeur de Robot
 * @return le Robot nouvellement construit
 */
Robot*  robot_Create();

/**
 * Détruit le Robot donnée
 * @param  _robot le Robot à détruire
 */
void    robot_Destroy(Robot* _robot);

/**
 * Charger la pièce tenu par le Robot sur le convoyeur
 * @param  _robot    le robot qui doit charger le convoyeur
 * @param  _convoyer le convoyeur à charger
 * @return           ROBOT_SUCCESS en cas de succès de chargement
 *                   ROBOT_FAIL en cas d'impossibilité de charger
 */
int     robot_loadConvoyer(Robot* _robot, Convoyer* _convoyer);

/**
 * Permet de décherger une pièce se trouvant sur le convoyeur
 * @param  _robot    le robot qui doit prendre la pièce sur le convoyeur
 * @param  _convoyer le convoyeur sur lequel se trouve la Piece
 * @return           ROBOT_SUCCESS si le déchargement est un succès
 *                   ROBOT_FAIL si le déchargement est un échec
 */
int     robot_unloadConvoyer(Robot* _robot, Convoyer* _convoyer);

#endif

/**
 * Auteur: Thomas Gredin
 *
 * Représente les robots de chargement et de retrait du convoyeur
 */

#ifndef ROBOT_H
#define ROBOT_H

/**
 * Constantes utilisées pour les valeurs de retour des méthodes de
 * Robot
 */
#define ROBOT_SUCCESS   1
#define ROBOT_FAIL      0

/**
 * Position des deux robots (robot de chargement et de déchargement)
 */
#define ROBOT_LOADER_POS    0
#define ROBOT_UNLOADER_POS  100

/**
 * Le temps maximum que le robot de chargement va passer à essayer de
 * charger la pièce sur le convoyeur avant d'abandonner
 */
#define ROBOT_LOAD_TIMEOUT 20

/**
 * Le temps maximum que le robot de chargement va passer à essayer de
 * décharger la pièce du convoyeur avant d'abandonner
 */
#define ROBOT_UNLOAD_TIMEOUT 30

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
int     robot_LoadConvoyer(Robot* _robot, Convoyer* _convoyer);

/**
 * Permet de décherger une pièce se trouvant sur le convoyeur
 * @param  _robot    le robot qui doit prendre la pièce sur le convoyeur
 * @param  _convoyer le convoyeur sur lequel se trouve la Piece
 * @return           ROBOT_SUCCESS si le déchargement est un succès
 *                   ROBOT_FAIL si le déchargement est un échec
 */
int     robot_UnloadConvoyer(Robot* _robot, Convoyer* _convoyer);

/**
 * Permet de mettre le thread du robot dans un état d'attente. Tant que personne
 * ne lui signal qu'il doit travailler (avec la méthode robot_WakeUp), il ne
 * sort pas de cet état
 * @param  _robot le robot à faire dormir
 */
void    robot_WaitWork(Robot* _robot);

/**
 * Permet de réveiller le robot pour qu'il se mette au travail
 * @param  _robot le robot à réveiller
 */
void    robot_WakeUp(Robot* _robot, int _work_to_perform);

/**
 * Permet d'attribuer une pièce au robot en protégeant le tout par un semaphore
 * @param  _robot le robot auquel attribuer une pièce
 * @param  _piece la pièce à attribuer
 */
void    robot_SetPiece(Robot* _robot, Piece* _piece);

#endif

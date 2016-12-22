/**
 * Auteur: Thomas Gredin
 *
 * Représente le convoyeur
 */

#ifndef CONVOYER_H
#define CONVOYER_H

#include <time.h>
#include <semaphore.h>
#include <stdlib.h>

#include "Objects.h"
#include "Piece.h"

/**
 * Position donnée au convoyeur quand il ne porte pas de pièce
 */
#define CONVOYER_NO_PIECE_POS   -1

/**
 * Nombre de pièce que peut transporter le convoyeur en même temps
 */
#define CONVOYER_CAPACITY       1
#define CONVOYER_SPEED          2

/**
 * Pour indiquer si le convoyeur est prit ou lacher lors de chargement
 * déchargement
 */
#define CONVOYER_FREE 1
#define CONVOYER_TAKE 0

#define CONVOYER_SUCCESS    1
#define CONVOYER_FAIL       0

/**
 * Créer un convoyer
 * @return le convoyer crée
 */
Convoyer*   convoyer_Create();

/**
 * Détruit le convoyer
 * @param  _convoyer convoyer à détruire
 */
void        convoyer_Destroy(Convoyer* _convoyer);

/**
 * Permet de monopoliser le convoyeur
 * @param  _convoyer  le convoyeur à monopoliser
 * @param  _timeout_s le temps en cas d'attente avant de renvoyer une erreur
 * @return            CONVOYER_SUCCESS si pas de problème
 *                    CONVOYER_FAIL si problème ou si ça fait _timeout_s secondes que
 *                    l'on attend
 */
int         convoyer_Use(Convoyer* _convoyer, int _timeout_s);

/**
 * Permet de libérer le convoyeur de la monopolisation pour permettre aux
 * autres de l'utiliser
 * @param  _convoyer le convoyeur à libérer
 */
void        convoyer_Free(Convoyer* _convoyer);

/**
 * Permet de bouger le convoyer par sa vitesse
 * @param  _convoyer le convoyeur à faire tourner
 */
void        convoyer_Move(Convoyer* _convoyer);

#endif

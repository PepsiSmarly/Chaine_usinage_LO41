/**
 * Auteur: Thomas Gredin
 *
 * Représente le convoyeur
 */

#ifndef CONVOYER_H
#define CONVOYER_H

#include <semaphore.h>
#include <stdlib.h>

#include "Piece.h"

/**
 * Position donnée au convoyeur quand il ne porte pas de pièce
 */
#define CONVOYER_NO_PIECE_POS   0

/**
 * Nombre de pièce que peut transporter le convoyeur en même temps
 */
#define CONVOYER_CAPACITY       1

/**
 * Pour indiquer si le convoyeur est prit ou lacher lors de chargement
 * déchargement
 */
#define CONVOYER_TAKE 0
#define CONVOYER_FREE 1

/**
 * Structure qui représente le convoyer
 *
 * position     : position actuelle de la pièce se trouvant sur le convoyer si
 *                si pièce il y à
 * loaded_piece : pièce actuellement chargé sur le convoyeur si elle existe
 *                sinon la valeur est sur NULL
 */
typedef struct
{
    int position;
    Piece* loaded_piece;

    sem_t padlock;
}
Convoyer;

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
 * @param  _convoyer le convoyeur à monopoliser
 */
void        convoyer_Use(Convoyer* _convoyer);

/**
 * Permet de libérer le convoyeur de la monopolisation pour permettre aux
 * autres de l'utiliser
 * @param  _convoyer le convoyeur à libérer
 */
void        convoyer_Free(Convoyer* _convoyer);

#endif

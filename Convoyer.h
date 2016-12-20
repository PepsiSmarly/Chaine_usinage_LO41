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

#define CONVOYER_NO_PIECE_POS   0
#define CONVOYER_CAPACITY       1

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

#endif

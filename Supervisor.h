/**
 * Auteur: Thomas Gredin
 *
 * Le Superviseur est responsable des tâches suivantes :
 * - Reçoit des ordres de l'opérateur
 * - Détermine la machine qui traite une nouvelle pièce
 *   (une pièce annoncé par l'opérateur)
 * - Demande au Robot d'alimentation de poser la pièce
 *   sur le Convoyeur
 * - Demande à la machine de traitement concerné par l'arrivée
 *   de la pièce de se préparer
 */

#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#define SUPERVISOR_SUCCESS  0
#define SUPERVISOR_FAIL     1

#include <stdlib.h>

#include "Piece.h"
#include "FactoryTable.h"

/**
 * Les différents états possibles du système
 */
typedef enum { OK, ERROR } SystemState;

typedef struct
{
    SystemState sys_state;
    int convoyer_state;
}
Supervisor;

/**
 * Créer un Supervisor
 * @return le Supervisor crée
 */
Supervisor*     supervisor_Create();

/**
 * Détruit le Supervisor donné
 * @param  _supervisor le Supervisor à détruire
 */
void            supervisor_Destroy(Supervisor* _supervisor);

/**
 * Introduire une pièce dans le système
 * @param  _supervisor le Supervisor du système dans laquelle la pièce est
 *                     introduite
 * @param  _piece      la pièce à introduire
 * @return             succès ou non
 */
int             supervisor_AppendPiece(Supervisor* _supervisor, Piece* _piece);

/**
 * Détermine la table d'usinage à laquelle la pièce soumise sera transmise
 * @param  _supervisor le Supervisor
 * @param  _piece      la pièce soumise au système
 * @return             succès ou non
 */
int             supervisor_DetermineFactoryTable(Supervisor* _supervisor,
                                                    Piece* _piece);

/**
 * Changer l'état du convoyer (utilisé ou non)
 * @param  _supervisor le Supervisor
 * @param  _state      le nouvel état du convoyer
 */
void            supervisor_changeConvoyerState(Supervisor* _supervisor, int _state);

#endif

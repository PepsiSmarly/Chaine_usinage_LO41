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

    FactoryTable* table1;
    FactoryTable* table2;
    FactoryTable* table3;
}
Supervisor;

Supervisor*     supervisor_Create();
void            supervisor_Destroy(Supervisor* _supervisor);

int             supervisor_AppendPiece(Supervisor* _supervisor, Piece* _piece);
int             supervisor_DetermineFactoryTable(Supervisor* _supervisor,
                                                    Piece* _piece);

#endif

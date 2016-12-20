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

/**
 * Les différents états possibles du système
 */
typedef enum { OK, ERROR } SystemState;

typedef struct
{
    SystemState sys_state;
}
Supervisor;

/**
 * Auteur: Thomas Gredin
 *
 * Représente les robots de chargement et de retrait du convoyeur
 */

#include "Piece.h"

typedef struct
{
    Piece* loaded_piece;
}
Robot;

Robot*  robot_Create();
void    robot_Destroy(Robot* _robot);

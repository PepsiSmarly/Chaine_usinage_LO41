/**
 * Auteur: Thomas Gredin
 *
 * Représente les pièces qui vont être usiné par le système
 */

#ifndef PIECE_H
#define PIECE_H

#include "Objects.h"
#include "FactoryTable.h"

/**
 * Pour construire une pièce
 * @param  _id           id unique de la pièce
 * @param  _process_code opération à effectuer sur la pièce
 * @return               la pièce nouvellement créée
 */
Piece* piece_Create(int _id, int _process_code);

/**
 * Détruit la pièce donnée
 * @param _piece la pièce à détruire
 */
void piece_Destroy(Piece* _piece);

#endif

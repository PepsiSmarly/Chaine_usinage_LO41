/**
 * Auteur: Thomas Gredin
 *
 * Représente les tables d'usinage
 */

#define FACTORYTABLE_TRUE   1
#define FACTORYTABLE_FALSE  0

#include <stdlib.h>

/**
 * Structure qui représente une table d'usinage
 *
 * process_code     : code qui détermine la nature du traitement de la machine
 * is_in_process    : la valeur varie si la machine est en train de traiter une
 *                    pièce ou non
 * is_brocken       : la valeur varie si la machine est en panne ou non
 * position         : position ou doit se trouver la pièce sur le tapis pour que
 *                    la table d'usinage puisse la récupérer et la traiter, c'est
 *                    également l'endroit ou elle sera déposé à la fin du
 *                    traitement
 */
typedef struct
{
    int process_code;
    int is_in_process;
    int is_brocken;
    int is_ready;

    int position;
}
FactoryTable;

/**
 * Créer une Table d'usinage
 * @param  _process_code le numéro de process qui sera appliqué aux pièces
 * @param  _position     position de la pièce sur le tapis pour pouvoir effectuer
 *                       une récupération de la pièce
 * @return               la table nouvellement créée
 */
FactoryTable*   factoryTable_Create(int _process_code, int _position);

/**
 * Détruire la table d'usinage
 * @param  _ft table d'usinage à détruire
 */
void            factoryTable_Destroy(FactoryTable* _ft);

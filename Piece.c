#include "Piece.h"

Piece* piece_Create(int _id, int _process_code)
{
    Piece* p = malloc(sizeof(Piece));

    p->id = _id;
    p->process_code = _process_code;

    return p;
}

void piece_Destroy(Piece* _piece)
{
    if(p == NULL)
        return;

    free(_piece);
}

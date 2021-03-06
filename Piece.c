#include "Piece.h"

Piece* piece_Create(int _id, int _process_code)
{
    Piece* p = malloc(sizeof(Piece));

    p->id = _id;
    p->process_code = _process_code;
    p->is_processed = PIECE_NOT_PROCESSED;

    return p;
}

void piece_Destroy(Piece* _piece)
{
    if(_piece == NULL)
        return;

    free(_piece);
}

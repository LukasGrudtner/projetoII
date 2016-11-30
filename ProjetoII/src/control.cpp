#include "control.h"

Control::Control()
{
    index = new IndexList();
    secondIndex = new SecondaryIndexing(index);
    reader = new Reader(secondIndex);
    //secondIndex->mostraChaves();
    writer = new Writer(index);
    index = reader->mountInvertedList();

    /* Mostra que a nova lista funciona */
    cout << "Index Size = " << index->size() << endl;
}

Control::~Control()
{
    //dtor
}

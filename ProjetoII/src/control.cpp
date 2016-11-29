#include "control.h"

Control::Control()
{
    secondIndex = new SecondaryIndexing();
    reader = new Reader(secondIndex);

    //secondIndex->mostraChaves();
}

Control::~Control()
{
    //dtor
}

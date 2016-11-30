#include "control.h"

Control::Control()
{
    index = new IndexList();
    secondIndex = new SecondaryIndexing(index);
    reader = new Reader(secondIndex);
    //secondIndex->mostraChaves();
    writer = new Writer(index);

}

Control::~Control()
{
    //dtor
}

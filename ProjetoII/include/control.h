#ifndef CONTROL_H
#define CONTROL_H

#include "secondary_indexing.h"
#include "reader.h"
#include <iostream>


class Control
{
    public:
        Control();
        virtual ~Control();

    protected:

    private:
        SecondaryIndexing* secondIndex;
        Reader* reader;
};

#endif // CONTROL_H

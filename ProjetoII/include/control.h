#ifndef CONTROL_H
#define CONTROL_H

#include "secondary_indexing.h"
#include "reader.h"
#include "writer.h"
#include <iostream>


class Control
{
    public:
        Control();
        virtual ~Control();
        void Menu();

    protected:

    private:
        SecondaryIndexing* secondIndex;
        Reader* reader;
        Writer *writer;
        IndexList *index;
};

#endif // CONTROL_H

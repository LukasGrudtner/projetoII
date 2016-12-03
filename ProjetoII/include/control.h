#ifndef CONTROL_H
#define CONTROL_H

#include "secondary_indexing.h"
#include "reader.h"
#include "writer.h"
#include "search_engine.h"
#include <iostream>


class Control
{
    public:
        Control();
        virtual ~Control();
        void Menu();
        void menuAvancado();

    protected:

    private:
        SecondaryIndexing* secondIndex;
        Reader* reader;
        Writer *writer;
        IndexList *index;
        SearchEngine *searchEngine;
};

#endif // CONTROL_H

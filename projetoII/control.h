#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>

#include "secondary_indexing.h"
#include "reader.h"
#include "writer.h"
#include "search_engine.h"

class Control
{
    public:
        Control(int argc, char *argv[]);
        virtual ~Control();
        void mainMenu(int argc, char *argv[]);
        void advancedMenu(int argc, char *argv[]);

    protected:

    private:
        SecondaryIndexing* secondIndex;
        Reader* reader;
        Writer *writer;
        IndexList *index;
        SearchEngine *searchEngine;
};

#endif // CONTROL_H

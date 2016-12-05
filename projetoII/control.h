#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>

#include "primary_indexing.h"
#include "avl_tree.h"
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
        PrimaryIndexing *primaryIndex;
        AvlTree *tree;

        SecondaryIndexing* secondIndex;
        IndexList *index;

        SearchEngine *searchEngine;

        Reader* reader;
        Writer *writer;
};

#endif // CONTROL_H

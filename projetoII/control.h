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

        /* Abre o menu principal, onde serão realizadas as buscas. */
        void mainMenu(int argc, char *argv[]);

        /* Abre o menu avançado, onde serão criados os arquivos. */
        void advancedMenu(int argc, char *argv[]);

    protected:

    private:
        /* Variáveis para indexação primária. */
        PrimaryIndexing *primaryIndex;
        AvlTree *tree;

        /* Variáveis para indexação secundária. */
        SecondaryIndexing* secondIndex;
        IndexList *index;

        /* Classes auxiliares para leitura/escrita nos arquivos. */
        SearchEngine *searchEngine;
        Reader* reader;
        Writer *writer;
};

#endif // CONTROL_H

#ifndef PRIMARYINDEXING_H
#define PRIMARYINDEXING_H

#include <string>

#include "avl_tree.h"

using namespace std;

class PrimaryIndexing
{
    public:
        PrimaryIndexing();
        virtual ~PrimaryIndexing();
        void addIndexKey(string name, int offset);
        void initTree();
        void saveTree();
        void loadTree();
        void deleteTree();

    protected:

    private:
        AvlTree *tree;
};

#endif // PRIMARYINDEXING_H

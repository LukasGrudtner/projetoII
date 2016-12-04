#ifndef PRIMARYINDEXING_H
#define PRIMARYINDEXING_H

#include <string>

#include "binary_tree.h"

using namespace std;

class PrimaryIndexing
{
    public:
        PrimaryIndexing(BinaryTree *tree_);
        virtual ~PrimaryIndexing();
        void addIndexKey(string name, string contents);

    protected:

    private:
        BinaryTree *tree;
};

#endif // PRIMARYINDEXING_H

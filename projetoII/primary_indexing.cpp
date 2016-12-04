#include "primary_indexing.h"

PrimaryIndexing::PrimaryIndexing(BinaryTree *tree_)
{
    tree = tree_;
}

PrimaryIndexing::~PrimaryIndexing()
{
    //dtor
}

/* Inserir também o contents de cada manpage */
void PrimaryIndexing::addIndexKey(string name, string contents)
{
    tree->insert(name, contents);
}

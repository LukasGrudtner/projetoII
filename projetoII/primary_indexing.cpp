#include "primary_indexing.h"

PrimaryIndexing::PrimaryIndexing()
{

}

PrimaryIndexing::~PrimaryIndexing()
{
    //dtor
}

void PrimaryIndexing::addIndexKey(string name, int offset)
{
    tree->Insert(name, offset);
}

void PrimaryIndexing::initTree()
{
    tree = new AvlTree();
}

void PrimaryIndexing::saveTree()
{
    tree->Save("dados/avlTree.dat");
}

void PrimaryIndexing::loadTree()
{
    tree->Load("dados/avlTree.dat");
}

void PrimaryIndexing::deleteTree()
{
    delete tree;
}

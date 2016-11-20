#include "secondary_indexing.h"

SecondaryIndexing::SecondaryIndexing()
{
    //indexKeys = new LinkedList();
}

SecondaryIndexing::~SecondaryIndexing()
{
    //dtor
}

void SecondaryIndexing::addIndexKey(string name)
{
    LinkedList* registerAdress = new LinkedList();
    indexKeys->push_back(name, registerAdress);
}

LinkedList* SecondaryIndexing::findIndexKey(string name)
{
    return indexKeys->find(name);
}

void SecondaryIndexing::addRegister(string data, string indexKey)
{
    indexKeys->find(indexKey)->push_back(data);
}

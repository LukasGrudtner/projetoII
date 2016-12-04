#include "secondary_indexing.h"

SecondaryIndexing::SecondaryIndexing(IndexList* index)
{
    indexKeys = index;
}

SecondaryIndexing::~SecondaryIndexing()
{
    //dtor
}

bool SecondaryIndexing::addIndexKey(string name)
{
    if (!checksForKeyExistence(name)) {
        RegisterList* registerAdress = new RegisterList();
        indexKeys->push_back(name, registerAdress);
        return true;
    } else {
        indexKeys->incQuantidadeNode(name);
        return false;
    }
}

RegisterList* SecondaryIndexing::findIndexKey(string name)
{
    return indexKeys->find(name);
}

void SecondaryIndexing::addRegister(string data, string indexKey, std::size_t quantidade_)
{
    indexKeys->find(indexKey)->push_back_register(data, quantidade_);
}

bool SecondaryIndexing::checksForKeyExistence(string word)
{
    return indexKeys->contains(word);
}

void SecondaryIndexing::showKeys()
{
    /* Listar todos os elementos da IndexList, assim como todos os elementos da RegisterList para cada índice */

    indexKeys->printsAllTheElements();
}



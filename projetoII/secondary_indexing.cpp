#include "secondary_indexing.h"

SecondaryIndexing::SecondaryIndexing(IndexList* index)
{
    indexList = index;
}

SecondaryIndexing::~SecondaryIndexing()
{
    //dtor
}

bool SecondaryIndexing::addIndexKey(string name)
{
    if (!checksForKeyExistence(name)) {
        RecordAdressesList* registerAdress = new RecordAdressesList();
        indexList->push_back(name, registerAdress);
        return true;
    } else {
        indexList->inc_amount_node(name);
        return false;
    }
}

RecordAdressesList* SecondaryIndexing::findIndexKey(string name)
{
    return indexList->find(name);
}

void SecondaryIndexing::addRecordAdress(string data, string indexKey, std::size_t quantidade_)
{
    indexList->find(indexKey)->push_back(data, quantidade_);
}

bool SecondaryIndexing::checksForKeyExistence(string word)
{
    return indexList->contains(word);
}

void SecondaryIndexing::showKeys()
{
    /* Listar todos os elementos da IndexList, assim como todos os elementos da RecordAdressesList para cada índice */
    indexList->printsAllTheElements();
}

#include "secondary_indexing.h"

SecondaryIndexing::SecondaryIndexing()
{

}

SecondaryIndexing::~SecondaryIndexing()
{
    //dtor
}

bool SecondaryIndexing::addIndexKey(string name)
{
cout << "addIndexKey" << endl;
    if (!verificaExistenciaDeChave(name)) {
        RegisterList* registerAdress = new RegisterList();
        indexKeys->push_back(name, registerAdress);
        return true;
    } else {
        indexKeys->incQuantidadeNode(name);
        cout << "IndexKey REPETIDA" << endl;
        return false;
    }
}

RegisterList* SecondaryIndexing::findIndexKey(string name)
{
    return indexKeys->find(name);
}

void SecondaryIndexing::addRegister(int data, string indexKey, std::size_t quantidade_)
{
    indexKeys->find(indexKey)->push_back_register(data, quantidade_);
}

bool SecondaryIndexing::verificaExistenciaDeChave(string word)
{
    return indexKeys->contains(word);
}

void SecondaryIndexing::mostraChaves()
{
    std::cout << "um: "<< indexKeys->getQuantidadeNode("um") << endl;
    std::cout << "dois: "<< indexKeys->getQuantidadeNode("dois") << endl;
    std::cout << "três: "<< indexKeys->getQuantidadeNode("três") << endl;
    std::cout << "sete: "<< indexKeys->getQuantidadeNode("sete") << endl;
    std::cout << "vinte: "<< indexKeys->getQuantidadeNode("vinte") << endl;
    std::cout << "e: "<< indexKeys->getQuantidadeNode("e") << endl;

}

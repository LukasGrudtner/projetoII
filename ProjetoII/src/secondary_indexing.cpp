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
    if (!verificaExistenciaDeChave(name)) {
        LinkedList* registerAdress = new LinkedList();
        indexKeys->push_back(name, registerAdress);
        std::cout << "Não repetida: " << name << std::endl;
    } else {
        indexKeys->incQuantidadeNode(name);
        std::cout << "Repetida: " << name << std::endl;
    }
}

LinkedList* SecondaryIndexing::findIndexKey(string name)
{
    return indexKeys->find(name);
}

void SecondaryIndexing::addRegister(string data, string indexKey)
{
    indexKeys->find(indexKey)->push_back(data);
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

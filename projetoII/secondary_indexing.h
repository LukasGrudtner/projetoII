#ifndef SECONDARYINDEXING_H
#define SECONDARYINDEXING_H

#include "index_list.h"
#include "register_list.h"
#include <iostream>

class SecondaryIndexing
{
    public:
        SecondaryIndexing(IndexList *index);
        virtual ~SecondaryIndexing();

        // Adiciona chaves com o paramatro nome, e cria um endereço de registro para essa chave
        // E retorna true caso a palavra não estiver na lista e false se a palavra for repetida
        bool addIndexKey(string name);

        // Retorna a chave com o parametro nome
        RegisterList* findIndexKey(string name);

        // Adiciona um registro
        void addRegister(string data, string indexKey, std::size_t quantidade_);

        // Verifica se a chave já foi adicionada
        bool checksForKeyExistence(string word);

        void showKeys();

    protected:

    private:
        IndexList *indexKeys;
};

#endif // SECONDARYINDEXING_H
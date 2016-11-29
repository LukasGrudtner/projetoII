#ifndef SECONDARYINDEXING_H
#define SECONDARYINDEXING_H

#include "index_list.h"
#include "register_list.h"
#include <iostream>

class SecondaryIndexing
{
    public:
        SecondaryIndexing();
        virtual ~SecondaryIndexing();

        // Adiciona chaves com o paramatro nome, e cria um endereço de registro para essa chave
        // E retorna true caso a palavra não estiver na lista e false se a palavra for repetida
        bool addIndexKey(string name);

        // Retorna a chave com o parametro nome
        RegisterList* findIndexKey(string name);

        // Adiciona um registro
        void addRegister(int data, string indexKey, std::size_t quantidade_);

        // Verifica se a chave já foi adicionada
        bool verificaExistenciaDeChave(string word);

        void mostraChaves();




    protected:

    private:
        IndexList* indexKeys = new IndexList();
};

#endif // SECONDARYINDEXING_H

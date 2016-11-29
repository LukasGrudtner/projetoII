#ifndef SECONDARYINDEXING_H
#define SECONDARYINDEXING_H

#include "linked_list.h"
#include <iostream>

class SecondaryIndexing
{
    public:
        SecondaryIndexing();
        virtual ~SecondaryIndexing();

        // Adiciona chaves com o paramatro nome, e cria um endereço de registro para essa chave
        void addIndexKey(string name);

        // Retorna a chave com o parametro nome
        LinkedList* findIndexKey(string name);

        // Adiciona um registro
        void addRegister(string data, string indexKey);

        // Verifica se a chave já foi adicionada
        bool verificaExistenciaDeChave(string word);

        void mostraChaves();




    protected:

    private:
        LinkedList* indexKeys = new LinkedList();
};

#endif // SECONDARYINDEXING_H

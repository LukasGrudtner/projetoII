#ifndef SECONDARYINDEXING_H
#define SECONDARYINDEXING_H

#include "linked_list.h"

class SecondaryIndexing
{
    public:
        SecondaryIndexing();
        virtual ~SecondaryIndexing();

        // Adiciona chaves com o paramatro nome, e cria um endereço de registro para essa chave
        void addIndexKey(string name);

        // Retorna a chave com o parametro nome
        LinkedList* findIndexKey(string name);

        void addRegister(string data, string indexKey);

    protected:

    private:
        LinkedList* indexKeys = new LinkedList();
};

#endif // SECONDARYINDEXING_H

#ifndef SECONDARYINDEXING_H
#define SECONDARYINDEXING_H

#include <iostream>

#include "index_list.h"
#include "record_adresses_list.h"

class SecondaryIndexing
{
    public:
        SecondaryIndexing(IndexList *index);
        virtual ~SecondaryIndexing();

        // Adiciona chaves com o paramatro nome, e cria um endereço de registro para essa chave
        // E retorna true caso a palavra não estiver na lista e false se a palavra for repetida
        /*  Adiciona as chaves, recebidas como parâmetro, na Lista de Índices.
            Retorna "true" caso a palavra não esteja na lista, e "false" caso
            a palavra seja repetida.
        */
        bool addIndexKey(string name);

        /*  Retorna a Lista de Endereços de Registro para a chave, recebida
            como parâmetro, name.
        */
        RecordAdressesList* findIndexKey(string name);

        /*  Adiciona um Endereço de Registro na Lista de Endereços de Registro.
            Ou seja, adiciona todas as manpages que possuem, em seu conteúdo,
            o Índice a qual esta Lista de Endereços pertence.
        */
        void addRecordAdress(string data, string indexKey, std::size_t quantidade_);

        /* Verifica se a chave já foi adicionada. */
        bool checksForKeyExistence(string word);

        /*  Imprime as chaves da Lista de Índices. */
        void showKeys();

    protected:

    private:
        IndexList *indexList;
};

#endif // SECONDARYINDEXING_H

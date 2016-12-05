#ifndef READER_H
#define READER_H

#include <string.h>
#include <fstream>
#include <iostream>
#include <stdio.h>

#include "linked_list.h"
#include "primary_indexing.h"
#include "secondary_indexing.h"

class Reader
{
    public:
        Reader(PrimaryIndexing *indicePrimario, SecondaryIndexing* indiceSecundario);
        virtual ~Reader();

        /*  Para cada chave primária recebida como parâmetro (argv[]), o
            arquivo "manpage.dat", carrega o registro em uma struct, e chama
            o método "addIndexKey()" da classe PrimaryIndexing para a inserção
            do índice primário na Árvore AVL.
        */
        void insertPrimaryKeys(int argc, char *argv[]);

        /*  Lê o arquivo "secondaryKeys.dat" com todas as chaves secundárias
            já separadas, e, caso ainda não estejam na Lista de Índices, é
            chamado o método "insertRegisters()" para a criação da Lista de
            Endereços de Registro para este índice.
        */
        void insertSecondaryKeys();

        /*  Recebe como parâmetro uma Chave Secundária, e tem como objetivo
            encontrar e adicionar todos os registros (manpages) que contenham
            essas chaves na Lista de Endereços de Registro da classe de
            Indexação Secundária.
        */
        void insertRegisterAdresses(string pivo);

        /*  À partir do arquivo "invertedList.dat", é carregada em memória
            uma Lista Invertida na forma de lista encadeada.
        */
        IndexList* loadInvertedList();

        /*  Retorna o tamanho do maior nome dentro todas as manpages. */
        int longerName(int argc, char* argv[]);

        /* Retorna o tamanho do maior arquivo dentre todas as manpages. */
        int largerFile(int argc, char* argv[]);

        /* Realiza a filtragem dos Índices Secundários. */
        bool selectWord(string word);

        /* Remove a pontução das palavras para realizar a filtragem. */
        string removePuntuaction(string word);

        /* Procura possíveis Chaves Secundárias em cada manpage. */
        void searchSecondaryKeys(int argc, char* argv[]);

        /*  A partir da lista de manpages recebida como parâmetro (arg[v]),
            cada manpage é carregada em uma struct, e depois escrita em disco
            no arquivo "manpage.dat" em forma de registro, para acesso
            posterior.
        */
        void createRegisters(int argc, char* argv[]);

        /* Retorna o número de palavras em um dado arquivo. */
        unsigned long numberOfWordsInFile(string source);

        /* Remove as palavras repetidas da lista "bruta" de índices. */
        void removeRepeatedWords(int argc, char* argv[]);

    protected:

    private:
        PrimaryIndexing *primaryIndex;
        SecondaryIndexing *secondIndex;
        unsigned long cont;
};

#endif // READER_H

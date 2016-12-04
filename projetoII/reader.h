#ifndef READER_H
#define READER_H

#include <string.h>
#include <fstream>
#include <iostream>
#include <stdio.h>

#include "linked_list.h"
#include "secondary_indexing.h"

class Reader
{
    public:
        Reader(SecondaryIndexing* indiceSecundario);
        virtual ~Reader();
        void insertSecondaryKeys();
        void insertRegisters(string pivo);
        IndexList* mountInvertedList();

        /* Retorna o maior nome dentre todas as manpages */
        int longerName(int argc, char* argv[]);
        /* Retorna o maior arquivo dentre todas as manpages */
        int largerFile(int argc, char* argv[]);
        /* Realiza a filtragem dos índices secundários */
        bool selectWord(string word);
        /* Remove a pontução das palavras */
        string removePuntuaction(string word);
        /* Procura as chaves secundárias em cada manpage */
        void searchSecondaryKeys(int argc, char* argv[]);
        /* Cria os registros no arquivo "manpages.dat" */
        void createRegisters(int argc, char* argv[]);
        /* Retorna o número de palavras em um dado arquivo */
        unsigned long numberOfWordsInFile(string source);
        /* Remove as palavras repetidas da lista "bruta" de índices */
        void removeRepeatedWords(int argc, char* argv[]);

    protected:

    private:
        SecondaryIndexing* secondIndex;
        unsigned long cont;
};

#endif // READER_H

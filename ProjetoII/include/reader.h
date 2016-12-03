#ifndef READER_H
#define READER_H

#include <string.h>
#include <fstream>
#include <iostream>
#include <stdio.h>

#include "secondary_indexing.h"

class Reader
{
    public:
        Reader(SecondaryIndexing* indiceSecundario);
        virtual ~Reader();
        void insertSecondaryKeys();
        void insertRegisters(string pivo);
        IndexList* mountInvertedList();
        void searchInvertedFile();
        void conjunctiveSearch();

    protected:

    private:
        SecondaryIndexing* secondIndex;
        unsigned long cont;
};

#endif // READER_H

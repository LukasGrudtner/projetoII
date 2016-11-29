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

    protected:

    private:
        SecondaryIndexing* secondIndex;
};

#endif // READER_H

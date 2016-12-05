#ifndef WRITER_H
#define WRITER_H

#include <fstream>
#include <iostream>

#include "index_list.h"
#include "record_adresses_list.h"

class Writer
{
    public:
        Writer(IndexList *indexList_);
        virtual ~Writer();

        /*  Escreve a Lista Invertida em disco.
            Cada índice da Lista de Índices e o tamanho de sua Lista de
            Endereços é mantida em uma linha diferente, e ao longo de sua linha
            é armazenado sequências das manpages e a incidência deste índice
            na manpage. Com isto é possível carregar de volta para a memória
            toda a Lista Invertida.
        */
        void writeList();

    protected:

    private:
        IndexList *indexList;

};

#endif // WRITER_H

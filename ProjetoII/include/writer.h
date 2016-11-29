#ifndef WRITER_H
#define WRITER_H

#include <fstream>
#include <iostream>
#include "index_list.h"
#include "register_list.h"

class Writer
{
    public:
        Writer(IndexList *indexList_);
        virtual ~Writer();
        void writeList();

    protected:

    private:
        IndexList *indexList;

};

#endif // WRITER_H

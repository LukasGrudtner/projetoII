#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <string>
#include <fstream>
#include <iostream>

#include "register_list.h"

using namespace std;

class SearchEngine
{
    public:
        SearchEngine();
        virtual ~SearchEngine();
        void secondarySearch(string index);
        void conjunctiveSearch(string index1, string index2);

    protected:

    private:
};

#endif // SEARCHENGINE_H

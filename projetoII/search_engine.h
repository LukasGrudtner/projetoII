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
        void primarySearch(string index);
        void secondarySearch(string index);
        void conjunctiveSearch(string index1, string index2);

    protected:

    private:
        string checksFormat(string word);
};

#endif // SEARCHENGINE_H

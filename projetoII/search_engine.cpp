#include "search_engine.h"

SearchEngine::SearchEngine()
{
    //ctor
}

SearchEngine::~SearchEngine()
{
    //dtor
}

void SearchEngine::secondarySearch(string index)
{
    fstream file;
    int size;
    string word, name;
    bool teste = false;

    file.open("dados/invertedList.dat");

    file >> size;

    int i = 0;
    while (teste == false && i < size) {
        file >> word;
        if (word == index)
            teste = true;
        else
            getline(file, word);
        i++;
    }

    if (i == size) {
        cout << "==============================================================\n"
             << "Desculpe, o índice [" << index << "] não consta em nossos servidores... \nBusque por outra palavra.\n";
    } else {

        int qtdeRegister;
        file >> qtdeRegister;
        int qtde;
        cout << "===========================REGISTROS==========================\n";
        for (int j = 0; j < qtdeRegister; j++) {
            file >> name >> qtde;
            cout << name << "  " << qtde << endl;
        }
    }

    file.close();
}

void SearchEngine::conjunctiveSearch(string index1, string index2)
{
    RegisterList* indexList1 = new RegisterList();
    RegisterList* indexList2 = new RegisterList();
    RegisterList* searchList = new RegisterList();
    fstream file;
    int size1, size2;
    string word, name1, name2;
    bool teste = false;

    file.open("dados/invertedList.dat");

    /* #################################### */
    file >> size1;
    int i = 0;
    while (teste == false && i < size1) {
        file >> word;
        if (word == index1)
            teste = true;
        else
            getline(file, word);
        i++;
    }


    if (i == size1) {
        cout << "==============================================================\n"
             << "Desculpe, o índice [" << index1 << "] não consta em nossos servidores... \nBusque por outra palavra.\n";
    } else {
        int qtdeRegister;
        file >> qtdeRegister;
        size_t qtde1;
        for (int j = 0; j < qtdeRegister; j++) {
            file >> name1 >> qtde1;
            indexList1->push_back_register(name1, qtde1);
        }
    }
    /* #################################### */

    file.seekg(0, file.beg);
    teste = false;
    file >> size2;
    int k = 0;
    while (teste == false && k < size2) {
        file >> word;
        if (word == index2)
            teste = true;
        else
            getline(file, word);
        k++;
    }

    if (k == size2) {
        cout << "==============================================================\n"
             << "Desculpe, o índice [" << index2 << "] não consta em nossos servidores... \nBusque por outra palavra.\n";
    } else {
        int qtdeRegister;
        file >> qtdeRegister;
        int qtde2;
        for (int j = 0; j < qtdeRegister; j++) {
            file >> name2 >> qtde2;
            indexList2->push_back_register(name2, qtde2);
        }
    }
    /* #################################### */
    file.close();

    string registroProcurado;

    for (int m = 0; m < indexList1->size(); m++) {
        registroProcurado = indexList1->at(m);
        for (int n = 0; n < indexList2->size(); n++) {
            if (registroProcurado == indexList2->at(n)) {
                searchList->push_back_register(registroProcurado, 0);
            }
        }
    }

    delete indexList1;
    delete indexList2;

    if (k != size1 || i != size2) {
        cout << "===========================REGISTROS==========================\n";
        for (int k = 0; k < searchList->size(); k++) {
            cout << searchList->at(k) << "\n";
    }
}
    delete searchList;



}

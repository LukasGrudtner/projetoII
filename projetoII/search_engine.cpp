#include "search_engine.h"

SearchEngine::SearchEngine()
{
    //ctor
}

SearchEngine::~SearchEngine()
{
    //dtor
}

void SearchEngine::primarySearch(string index)
{
    ifstream file, manpage;
    string key;
    unsigned long value;
    struct manpages {
        char name[52];
        char contents[139715];
    };

    index = checksFormat(index);

    file.open("dados/avlTree.dat");
    bool finded = false;

    int i = 0;
    while (!file.eof() && finded == false) {
        file >> key >> value;
        if (key == index)
            finded = true;
    }

    if (!finded) {
        cout << "\n==============================================================\n\n"
             << "Desculpe, o índice [" << index << "] não consta em nossos servidores..."
             << "\nBusque por outra palavra.\n";
    } else {
        struct manpages registro;
        manpage.open("dados/manpage.dat");
        manpage.seekg(value*sizeof(struct manpages), ios_base::beg);
        manpage.read((char*) &registro, sizeof(struct manpages));

        cout << "\n=========================== " << key << " ==========================\n\n"
             << registro.contents;
    }
}

string SearchEngine::checksFormat(string word)
{
    string aux = "    ";
    for (int i = 4; i > 0; i--) {
        aux[4-i] = word[word.size()-i];
    }

    if (aux != ".txt")
        word = word + ".txt";

    return word;
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
        cout << "\n==============================================================\n\n"
             << "Desculpe, o índice [" << index << "] não consta em nossos servidores..."
             << "\nBusque por outra palavra.\n";
    } else {

        int qtdeRegister;
        file >> qtdeRegister;
        int qtde;
        cout << "\n========================== REGISTROS =========================\n\n";
        for (int j = 0; j < qtdeRegister; j++) {
            file >> name >> qtde;
            cout << name << "  " << qtde << "\n";
        }
    }

    file.close();
}

void SearchEngine::conjunctiveSearch(string index1, string index2)
{
    RecordAdressesList* listIndex1 = new RecordAdressesList();
    RecordAdressesList* listIndex2 = new RecordAdressesList();
    RecordAdressesList* searchList = new RecordAdressesList();
    fstream file;
    int size1, size2;
    string word, name1, name2;
    bool teste = false;

    file.open("dados/invertedList.dat");

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
        cout << "\n==============================================================\n\n"
             << "Desculpe, o índice [" << index1 << "] não consta em nossos servidores..."
             << "\nBusque por outra palavra.\n";
    } else {
        int qtdeRegister;
        file >> qtdeRegister;
        size_t qtde1;
        for (int j = 0; j < qtdeRegister; j++) {
            file >> name1 >> qtde1;
            listIndex1->push_back(name1, qtde1);
        }
    }

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
        cout << "\n==============================================================\n\n"
             << "Desculpe, o índice [" << index2 << "] não consta em nossos servidores..."
             << "\nBusque por outra palavra.\n";
    } else {
        int qtdeRegister;
        file >> qtdeRegister;
        int qtde2;
        for (int j = 0; j < qtdeRegister; j++) {
            file >> name2 >> qtde2;
            listIndex2->push_back(name2, qtde2);
        }
    }

    file.close();

    string registroProcurado;

    for (int m = 0; m < listIndex1->size(); m++) {
        registroProcurado = listIndex1->at(m);
        for (int n = 0; n < listIndex2->size(); n++) {
            if (registroProcurado == listIndex2->at(n)) {
                searchList->push_back(registroProcurado, 0);
            }
        }
    }

    delete listIndex1;
    delete listIndex2;

    if (k != size1 && i != size2) {
        cout << "\n========================== REGISTROS =========================\n\n";
        for (int k = 0; k < searchList->size(); k++) {
            cout << searchList->at(k) << "\n";
        }
        cout << "\n";
    }
    delete searchList;



}

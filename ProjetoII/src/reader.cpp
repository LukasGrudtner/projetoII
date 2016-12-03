#include <fstream>
#include <iostream>
#include <string>

#include "reader.h"

Reader::Reader(SecondaryIndexing* indiceSecundario)
{
    secondIndex = indiceSecundario;
}

Reader::~Reader()
{
    //dtor
}

void Reader::insertSecondaryKeys()
{
    std::ifstream file;
    std::string word;
    file.open("secondaryKeys.dat");
    while (!file.eof()) {
        getline(file, word);
        if (word[0] != '\0') {
            if (secondIndex->addIndexKey(word)) {
                insertRegisters(word);
            }
        }
    }
    file.close();
}

void Reader::insertRegisters(string pivo)
{
    std::ifstream file;
    file.open("manpage.dat");
    long posicaoName, posicaoContents;
    std::size_t counter;
    string name, contents;
    int numRegistro = 0;

    struct manpage {
        char name[52];
        char contents[139715];
    };

    struct manpage registro;


    while (!file.eof()) {
        counter = 0;
        file.seekg(139767*numRegistro);
        file.read((char *) &registro, sizeof(struct manpage));
        name = registro.name;
        contents = registro.contents;

        posicaoName = 0;
        while (posicaoName != -1) {
            posicaoName = name.find(pivo);
            if (posicaoName != -1) {
                counter++;
                name[posicaoName] = '\0';
            }
        }


        posicaoContents = 0;
        while (posicaoContents != -1) {
            posicaoContents = contents.find(pivo);
            if (posicaoContents != -1) {
                counter++;
                contents[posicaoContents] = '\0';
            }
        }

        if (counter > 0)
            secondIndex->addRegister(name, pivo, counter);
        numRegistro++;

    }
    cont++;
    cout << cont << ". " << pivo << "\n";
    file.close();


}

IndexList* Reader::mountInvertedList()
{
    IndexList *indexKeys = new IndexList();
    string index;
    size_t qtdeIndex, qtdeRegister;
    string register_;
    ifstream file;
    file.open("invertedList.dat");

    int sizeIndex, sizeRegister;

    file >> sizeIndex;
    cout << "Size Index: " << sizeIndex << endl;

    for (int i = 0; i < sizeIndex; i++) {
        file >> index >> qtdeIndex;
        RegisterList *registerList = new RegisterList();
        cout << index << endl;
        indexKeys->push_back(index, registerList);
        for (int j = 0; j < qtdeIndex; j++) {
            file >> register_ >> qtdeRegister;
            registerList->push_back_register(register_, qtdeRegister);
        }
    }

    return indexKeys;
}

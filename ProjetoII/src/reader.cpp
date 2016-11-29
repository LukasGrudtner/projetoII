#include "reader.h"
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <string>

Reader::Reader(SecondaryIndexing* indiceSecundario)
{
    secondIndex = indiceSecundario;
    insertSecondaryKeys();
    //insertRegisters("across");
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
                cout << "===== InsertRegisters =====: " << word << endl;
                insertRegisters(word);
                cout << "===== InsertRegisters =====: " << word << endl;
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
    std::size_t counter = 0;
    string name, contents;
    int numRegistro = 0;

    struct manpage {
        char name[52];
        char contents[139715];
    };

    struct manpage registro;


    for (int i = 0; i < 2; i++) {
        cout << "numRegistro: " << numRegistro << endl;
        file.seekg(139767*i);
        file.read((char *) &registro, sizeof(struct manpage));
        name = registro.name;
        cout << "NAME: " << name << endl;
        contents = registro.contents;

        posicaoName = 0;
        while (posicaoName != -1) {
            posicaoName = name.find(pivo);
            if (posicaoName != -1) {
                counter++;
                name[posicaoName+1] = 'c';
            }
        }


        posicaoContents = 0;
        while (posicaoContents != -1) {
            posicaoContents = contents.find(pivo);
            cout << "posicaoContents: " << posicaoContents << endl;
            if (posicaoContents != -1) {
                counter++;
                contents[posicaoContents] = 'c';
                contents[posicaoContents+1] = 'c';
            }
        }

        cout << "Counter: " << counter << endl;
        //secondIndex->addRegister(numRegistro, pivo, counter);
        //numRegistro++;

    }
    file.close();


}






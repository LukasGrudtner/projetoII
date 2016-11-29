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
    insertRegisters("6to4relay.1m.txt");
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
        if (secondIndex->addIndexKey(word)) {
            //insertRegisters(word);
        }
    }
    file.close();
}

void Reader::insertRegisters(string pivo)
{
    std::ifstream file;
    string word, teste;
    file.open("manpage.dat");
    int counter;

    struct manpage {
        char name[52];
        char contents[139715];
    };

    struct manpage registro;

    file.read((char *) &registro, sizeof(struct manpage));
    //word = registro.name;
    //cout << endl << "Word: " << word << endl << endl;

    /*
    int j = 0;
    for (int k = 0; k < 52; k++) {
        if (word[k] != ' ' || word[k] != '0') {
            teste[j] = word[k];
            j++;
            cout << word[k] << endl;
        } else {
            if (teste == pivo) {
                counter++;
                j = 0;
            }
        }
    }*/

/*
    int d = 0;
    for (int k = 0; k < 51; k++) {
        if (word[k] == pivo[k]) {
            d++;
            teste += word[k];
        } else {
            if (strcmp(teste, pivo)) {
                cout << "igual" << endl;
                d = 0;
            }
        }
    }
    */
/*
    char word[] = registro.name;
    char teste[] = pivo;

    auto te = strstr(word, teste);
    */
    string l = registro.name;
    string z = registro.contents;

    int posicao = 0;
    while (posicao != -1) {
        posicao = z.find("support");
        std::cout << "Posição: " << posicao << endl;
        z[posicao+1] = 'c';
    }



    file.close();

}






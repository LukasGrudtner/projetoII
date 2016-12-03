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
    //insertSecondaryKeys();
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
            secondIndex->addRegister(numRegistro, pivo, counter);
        //cout << "Registro: " << numRegistro << endl;
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
    int register_;
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

void Reader::searchInvertedFile()
{
    fstream file;
    int size;
    string word, index;
    cout << "Qual palavra deseja buscar?\n";
    cin >> index;
    file.open("invertedList.dat");
    bool teste = false;

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
        cout << "\nDesculpe, o índice [" << index << "] não consta em nossos servidores... \nBusque por outra palavra.\n";
    } else {

        int qtdeRegister;
        file >> qtdeRegister;
        int register_, qtde;
        for (int j = 0; j < qtdeRegister; j++) {
            file >> register_ >> qtde;
            cout << "Register: " << register_ << " Qtde: " << qtde;
        }
    }

    file.close();

}

void Reader::conjunctiveSearch()
{
    RegisterList* lista1 = new RegisterList();
    RegisterList* lista2 = new RegisterList();
    RegisterList* listaBusca = new RegisterList();
    fstream file;
    int size;
    string word, index1, index2;
    cout << "Digite as 2 palavras (separadas por um espaço): \n";
    cin >> index1 >> index2;
    file.open("invertedList.dat");
    bool teste = false;

    /* #################################### */
    file >> size;
    int i = 0;
    while (teste == false && i < size) {
        file >> word;
        if (word == index1)
            teste = true;
        else
            getline(file, word);
        i++;
    }


    if (i == size) {
        cout << "\nDesculpe, o índice [" << index1 << "] não consta em nossos servidores... \nBusque por outra palavra.\n";
    } else {
        int qtdeRegister;
        file >> qtdeRegister;
        int register1;
        size_t qtde1;
        for (int j = 0; j < qtdeRegister; j++) {
            file >> register1 >> qtde1;
            lista1->push_back_register(register1, qtde1);
        }
    }
    /* #################################### */

    file.seekg(0, file.beg);
    teste = false;
    file >> size;
    int k = 0;
    while (teste == false && k < size) {
        file >> word;
        if (word == index2)
            teste = true;
        else
            getline(file, word);
        k++;
    }

    if (k == size) {
        cout << "\nDesculpe, o índice [" << index2 << "] não consta em nossos servidores... \nBusque por outra palavra.\n";
    } else {
        int qtdeRegister;
        file >> qtdeRegister;
        int register2, qtde2;
        for (int j = 0; j < qtdeRegister; j++) {
            file >> register2 >> qtde2;
            lista2->push_back_register(register2, qtde2);
        }
    }
    /* #################################### */
    file.close();

    int registroProcurado;

    for (int i = 0; i < lista1->size(); i++) {
        registroProcurado = lista1->at(i);
        for (int j = 0; j < lista2->size(); j++) {
            if (registroProcurado == lista2->at(j)) {
                listaBusca->push_back_register(registroProcurado, 0);
            }
        }
    }

    delete lista1;
    delete lista2;

    for (int k = 0; k < listaBusca->size(); k++) {
        cout << "Igual: " << listaBusca->at(k) << "\n";
    }

    delete listaBusca;



}

#include "reader.h"

Reader::Reader(SecondaryIndexing* indiceSecundario)
{
    secondIndex = indiceSecundario;
    insertSecondaryKeys();
}

Reader::~Reader()
{
    //dtor
}

void Reader::insertSecondaryKeys()
{
    int counter = 0;
    std::ifstream file;
    std::string word;
    file.open("secondaryKeys.dat");

    while (!file.eof()) {
        getline(file, word);
        secondIndex->addIndexKey(word);
        counter++;
    }
    cout << counter << endl;
    file.close();


}





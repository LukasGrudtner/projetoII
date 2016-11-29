#include "writer.h"

Writer::Writer(IndexList *indexList_)
{
    indexList = indexList_;
    writeList();
}

Writer::~Writer()
{
    //dtor
}

void Writer::writeList()
{
    std::ofstream file;
    file.open("invertedList.dat");

    /* Coisas para escrever */
    int tamanhoIndexList = indexList->size();
    //file.write((char *) &tamanhoIndexList, sizeof(tamanhoIndexList));
    file << tamanhoIndexList;

    string data = indexList->getWriteData();
    RegisterList* registerList = indexList->find(data);

    int tamanhoRegisterList = registerList->size();

    file << '\n' << data << ' ' << tamanhoRegisterList << ' ';
    for (int i = 0; i < tamanhoRegisterList; ++i) {
        file << registerList->getWriteData()+1 << ' ' << registerList->getWriteQtde()+1 << ' ';
        std::cout << registerList->getWriteData()+1 << ' ' << registerList->getWriteQtde()+1 << ' ';
    }
    file.close();



}

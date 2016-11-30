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

    for (int j = 0; j < tamanhoIndexList; ++j) {
        string data = indexList->getWriteData();
        RegisterList* registerList = indexList->find(data);
        int tamanhoRegisterList = registerList->size();
        //cout << "Tamanho da Lista de Registros: " << registerList->size() << endl;

        file << '\n' << data << ' ' << tamanhoRegisterList << ' ';
        for (int i = 0; i < tamanhoRegisterList; ++i) {
            int writeQtde = registerList->getWriteQtde();
            int regist = registerList->getWriteData();
            file << regist << ' ' << writeQtde << ' ';
            //std::cout << registerList->getWriteData() << ' ' << registerList->getWriteQtde() << ' ';
        }
    }
    file.close();



}

#include "writer.h"

Writer::Writer(IndexList *indexList_)
{
    indexList = indexList_;
}

Writer::~Writer()
{
    //dtor
}

void Writer::writeList()
{
    std::ofstream file;
    file.open("dados/invertedList.dat");

    /* Coisas para escrever */
    int tamanhoIndexList = indexList->size();
    file << tamanhoIndexList;

    for (int j = 0; j < tamanhoIndexList; ++j) {
        string data = indexList->get_write_data();
        RecordAdressesList* recordAdressesList = indexList->find(data);
        int tamanhoRecordAdressesList = recordAdressesList->size();

        file << '\n' << data << ' ' << tamanhoRecordAdressesList << ' ';
        for (int i = 0; i < tamanhoRecordAdressesList; ++i) {
            int writeQtde = recordAdressesList->get_write_amount();
            string recordName = recordAdressesList->get_write_data();
            file << recordName << ' ' << writeQtde << ' ';
        }
    }
    file.close();



}

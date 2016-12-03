#include "control.h"

Control::Control()
{
    index = new IndexList();
    secondIndex = new SecondaryIndexing(index);
    reader = new Reader(secondIndex);
    //secondIndex->mostraChaves();
    //writer = new Writer(index);

    Menu();
    //index = reader->mountInvertedList();
    //reader->searchInvertedFile();

    /* Mostra que a nova lista funciona */
    //cout << "Index Size = " << index->size() << endl;
}

Control::~Control()
{
    //dtor
}

void Control::Menu()
{
    unsigned answer;
    do {
        cout << "\nO que você deseja fazer?\n\n"
             << "1. Pesquisar um índice secundário.\n"
             << "2. Sair.\n\n";
        cin >> answer;
        cout << "\n";

        if (answer == 1)
            reader->searchInvertedFile();
    } while (answer != 2);
}

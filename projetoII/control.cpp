#include "control.h"

Control::Control(int argc, char *argv[])
{
    primaryIndex = new PrimaryIndexing();

    index = new IndexList();
    secondIndex = new SecondaryIndexing(index);

    reader = new Reader(primaryIndex, secondIndex);
    //secondIndex->mostraChaves();
    //writer = new Writer(index); // (ativar para escrever a lista invertida)

    mainMenu(argc, argv);

    //index = reader->mountInvertedList();
    //reader->searchInvertedFile();

    /* Mostra que a nova lista funciona */
    //cout << "Index Size = " << index->size() << endl;
}

Control::~Control()
{
    delete index;
    delete primaryIndex;
    delete secondIndex;
    delete reader;
}

void Control::mainMenu(int argc, char *argv[])
{
    unsigned answer;
    do {
        cout << "\n==============================================================\n"
             << "\nO que você deseja fazer?\n\n"
             << "1. Pesquisar um índice secundário.\n"
             << "2. Busca conjuntiva.\n"
             << "3. Pesquisar um índice primário.\n"
             << "4. Opções avançadas.\n"
             << "5. Sair.\n\n"
             << "==============================================================\n\n";
        cin >> answer;

        if (answer == 1) {
            string index;
            cout << "Qual palavra deseja buscar?\n";
            cin >> index;
            searchEngine->secondarySearch(index);
        }

        if (answer == 2) {
            string index1, index2;
            cout << "Quais palavras deseja buscar?\n\n";
            cin >> index1 >> index2;
            searchEngine->conjunctiveSearch(index1, index2);
        }

        if (answer == 3) {
            string index;
            cout << "Qual manpage deseja buscar?\n\n";
            cin >> index;
            searchEngine->primarySearch(index);
        }

        if (answer == 4)
            advancedMenu(argc, argv);

    } while (answer != 5);
}

void Control::advancedMenu(int argc, char *argv[])
{
    unsigned answer;
    do {
        cout << "==============================================================\n"
             << "\nO que você deseja fazer?\n\n"
             << "1. Criar o arquivo MANPAGES (contendo todas as MANPAGES).\n"
             << "2. Iniciar a construção do Arquivo Invertido.\n"
             << "3. Iniciar a construção da Árvore AVL.\n"
             << "4. Voltar para o Menu Inicial.\n\n"
             << "==============================================================\n";
        cin >> answer;

        if (answer == 1) {
            reader->searchSecondaryKeys(argc, argv);
            reader->createRegisters(argc, argv);
            reader->removeRepeatedWords(argc, argv);
        }

        if (answer == 2) {
            writer = new Writer(index);
            reader->insertSecondaryKeys();
            writer->writeList();
            delete writer;
        }

        if (answer == 3) {
            primaryIndex->initTree();
            reader->insertPrimaryKeys(argc, argv);
            primaryIndex->saveTree();
            primaryIndex->deleteTree();
        }

    } while (answer != 4);
}

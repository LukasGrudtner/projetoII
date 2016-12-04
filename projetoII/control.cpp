#include "control.h"

Control::Control(int argc, char *argv[])
{
    tree = new BinaryTree();
    primaryIndex = new PrimaryIndexing(tree);

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
    delete secondIndex;
    delete reader;
}

void Control::mainMenu(int argc, char *argv[])
{
    unsigned answer;
    do {
        cout << "==============================================================\n"
             << "O que você deseja fazer?\n\n"
             << "1. Pesquisar um índice secundário.\n"
             << "2. Busca conjuntiva.\n"
             << "3. Opções avançadas.\n"
             << "4. Sair.\n"
             << "==============================================================\n";
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
            //reader->conjunctiveSearch();
        if (answer == 3)
            advancedMenu(argc, argv);

    } while (answer != 4);
}

void Control::advancedMenu(int argc, char *argv[])
{
    unsigned answer;
    do {
        cout << "==============================================================\n"
             << "\nO que você deseja fazer?\n\n"
             << "1. Criar o arquivo MANPAGES (contendo todas as MANPAGES).\n"
             << "2. Iniciar a construção do Arquivo Invertido.\n"
             << "3. Iniciar a construção da Árvore Binária.\n"
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
        }

        if (answer == 3) {
            reader->insertPrimaryKeys(argc, argv);
        }

    } while (answer != 4);
}

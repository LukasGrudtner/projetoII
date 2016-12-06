#include "control.h"

Control::Control(int argc, char *argv[])
{
    primaryIndexing = new PrimaryIndexing();

    index = new IndexList();
    secondaryIndexing = new SecondaryIndexing(index);

    reader = new Reader(primaryIndexing, secondaryIndexing);

    mainMenu(argc, argv);
}

Control::~Control()
{
    delete index;
    delete primaryIndexing;
    delete secondaryIndexing;
    delete reader;
}

void Control::mainMenu(int argc, char *argv[])
{
    unsigned answer;
    do {
        cout << "\n==============================================================\n"
             << "\nO que você deseja fazer?\n\n"
             << "1. Pesquisar um índice primário.\n"
             << "2. Pesquisar um índice secundário.\n"
             << "3. Busca conjuntiva.\n"
             << "4. Opções avançadas.\n"
             << "5. Sair.\n\n"
             << "==============================================================\n\n";
        cin >> answer;

        if (answer == 1) {
            string index;
            cout << "Qual manpage deseja buscar?\n\n";
            cin >> index;
            searchEngine->primarySearch(index);
        }

        if (answer == 2) {
            string index;
            cout << "Qual palavra deseja buscar?\n";
            cin >> index;
            searchEngine->secondarySearch(index);
        }

        if (answer == 3) {
            string index1, index2;
            cout << "Quais palavras deseja buscar?\n\n";
            cin >> index1 >> index2;
            searchEngine->conjunctiveSearch(index1, index2);
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

        /* Cria o arquivo com os registros das MANPAGES. */
        if (answer == 1) {
            reader->searchSecondaryKeys(argc, argv);
            reader->createRegisters(argc, argv);
            reader->removeRepeatedWords(argc, argv);
        }

        /* Inicia a construção do Arquivo Invertido. */
        if (answer == 2) {
            writer = new Writer(index);
            reader->insertSecondaryKeys();
            writer->writeList();
            delete writer;
        }

        /* Inicia a construção da Árvore AVL. */
        if (answer == 3) {
            primaryIndexing->initTree();
            reader->insertPrimaryKeys(argc, argv);
            primaryIndexing->saveTree();
            primaryIndexing->deleteTree();
        }

    } while (answer != 4);
}

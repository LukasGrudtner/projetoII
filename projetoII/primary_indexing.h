#ifndef PRIMARYINDEXING_H
#define PRIMARYINDEXING_H

#include <string>

#include "avl_tree.h"

using namespace std;

class PrimaryIndexing
{
    public:
        PrimaryIndexing();
        virtual ~PrimaryIndexing();
        /* Adiciona uma chave (índice) na Árvore. */
        void addIndexKey(string name, int offset);

        /* Inicializa a Árvore. */
        void initTree();

        /* Salva a Árvore em disco em Pré-Ordem. */
        void saveTree();

        /* Carrega a Árvore do disco para a memória. */
        void loadTree();

        /* Deleta a Árvore. */
        void deleteTree();

    protected:

    private:
        AvlTree *tree;
};

#endif // PRIMARYINDEXING_H

#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

#include <fstream>
#include <string>
#include "tree_node.h"


using namespace std;


/*  Classe Árvore AVL
    Fornece métodos para criar e manipular Árvores AVL.
    Trabalha com nós cuja chave é do tipo string, para guardar o Índice
    Primário, e o valor é do tipo long unsigned, para guardar a posição do
    registro no arquivo.
*/
class AvlTree
{
    public:

        /* Construtor e destrutor padrões. */
        AvlTree();
        ~AvlTree();

        /*  Insere um novo nodo na árvore. */
        void Insert(const string& key, const unsigned long& value);

        /*  Remove uma entrada da árvore, aceitando uma string e um valor como
            parâmetros. Retorna falso caso a palavra não exista.
        */
        bool Remove(const string& key);

        /*  Procura um valor na árvore, aceitando uma chave como
            parâmetro. Se encontrado, o valor será armazenado na
            variável value e retornado como referência. Retorna
            verdadeiro se encontrar o valor, falso caso contrario.
        */
        bool Search(const string& key, unsigned long& value);

        /*  Limpa a Árvore. */
        void Clear();

        /*  Imprime a Árvore na tela. */
        void PrintNodeDetails();

        /*  Carrega uma Árvore do arquivo, aceitando o caminho do arquivo
            (path) como parâmetro. Caso esta não exista, retorna NULL.
        */
        static AvlTree* Load(const char* path);

        /*  Armazena uma Árvore em arquivo, aceitando o caminho do arquivo
            (path) como parâmetro. O arquivo é armazenado em pós-ordem.
        */
        bool Save(const char* path);


    private:

        TreeNode* root;

        /*  Rotações. */
        void rotateTwice(TreeNode*& node, Direction dir);
        void rotateOnce (TreeNode*& node, Direction dir);

        /*  Rebalanceamentos. */
        void updateBalance  (TreeNode* tree,  Direction dir);
        void rebalanceInsert(TreeNode*& tree, Direction dir, bool& hChanged);
        void rebalanceRemove(TreeNode*& tree, Direction dir, bool& hChanged);

        /*  Inserção e Remoção. */
        void insert(const string& key, const unsigned long& value, TreeNode*& node, bool& hChanged);
        bool remove(const string& key, TreeNode*& node, bool& hChanged);

        /*  Métodos auxiliares. */
        bool save(ofstream& stream, TreeNode* node);
        void printNodeDetails(TreeNode* node);
        inline Direction opposite(Direction dir);
};


#endif // AVLTREE_H_INCLUDED

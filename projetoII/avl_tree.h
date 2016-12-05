#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

#include <fstream>
#include <string>
#include "tree_node.h"


using namespace std;


// Classe �rvore AVL
//  Fornece m�todos para criar e manipular �rvores AVL.
//  Trabalha com n�s cuja chave e informa��o s�o do tipo string,
//  mas a classe poderia ser facilmente adaptada para trabalhar
//  com templates. Mantida nesta forma para uma maior did�tica.
class AvlTree
{

	// Classe de desenho para console
    friend class AsciiTreeView;


    public:

        // Construtor e destrutor padr�es
        AvlTree();
        ~AvlTree();

        // Insere uma nova entrada na �rvore, aceitando
        //   um arranjo chave e valor como par�metros
        void Insert(const string& key, const unsigned long& value);

        // Remove uma entrada da �rvore, aceitando
        //   um arranjo chave e valor como par�metros
        //   Retorna falso caso a palavra n�o exista.
        bool Remove(const string& key);

        // Procura um valor na �rvore, aceitando uma  chave como
        //  par�metro. Se encontrado, o valor ser� armazenado na
        //  vari�vel value e retornado como refer�ncia. Retorna
        //  verdadeiro se encontrar o valor, falso caso contr�rio.
        bool Search(const string& key, unsigned long& value);

        // Limpa a �rvore
        void Clear();

        // Exibe a �rvore na tela
        // void Print();
        void PrintNodeDetails();

        // Carrega uma �rvore do arquivo, aceitando o caminho do arquivo
        //  (path) como par�metro. Caso esta n�o exista, retorna NULL
        static AvlTree* Load(const char* path);

        // Armazena uma �rvore em arquivo, aceitando o caminho do arquivo
        //  (path) como par�metro. O arquivo � armazenado em p�s-ordem.
        bool Save(const char* path);


    private:

        // Raiz da �rvore
        TreeNode* root;


        // Rota��es
        void rotateTwice(TreeNode*& node, Direction dir);
        void rotateOnce (TreeNode*& node, Direction dir);


        // Rebalanceamentos
        void updateBalance  (TreeNode* tree,  Direction dir);
        void rebalanceInsert(TreeNode*& tree, Direction dir, bool& hChanged);
        void rebalanceRemove(TreeNode*& tree, Direction dir, bool& hChanged);


        // Inser��o e remo��o recursivos
        void insert(const string& key, const unsigned long& value, TreeNode*& node, bool& hChanged);
        bool remove(const string& key, TreeNode*& node, bool& hChanged);


        // M�todos auxiliares
        bool save(ofstream& stream, TreeNode* node);
        void printNodeDetails(TreeNode* node);
        inline Direction opposite(Direction dir);
};


#endif // AVLTREE_H_INCLUDED

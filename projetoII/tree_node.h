#ifndef TREENODE_H_INCLUDED
#define TREENODE_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

// Enumera��o para acesso �s sub�rvores e dire��o
//  de procura da pesquisa bin�ria. Serve tamb�m
//  para indicar o fator de balanceamento dos n�s.
enum Direction
{
    // Indica que a sub�rvore esquerda tem maior altura,
    // Que devemos caminhar para a esquerda na pesquisa
    // ou que queremos acessar a Sub�rvore da esquerda.
    LEFT  = 0,

    // Indica que a sub�rvore direita tem maior altura,
    // Que devemos caminhar para a direita na pesquisa
    // ou que queremos acessar a Sub�rvore da direita.
    RIGHT = 1,

    // Indica que as sub�rvore tem alturas iguais.
    // N�o � v�lida nos outros contextos.
    EQUAL = 2,
};

// N� da �rvore AVL
//  Esta classe est� implementada para trabalhar com chaves do tipo
//  string e valores associados �s chaves tamb�m do tipo string. No
//  entanto, esta classe pode ser facilmente adaptada para trabalhar
//  com templates. Mantida nessa forma apenas para uma maior did�tica.
class TreeNode
{
    public:
        // Constr�i um novo n� a partir de um item e uma chave
        TreeNode(const string& chave, const unsigned long& value)
        {
            this->Key   = chave;
            this->Value = value;
            this->Subtree[LEFT]  = NULL;
            this->Subtree[RIGHT] = NULL;
            this->Balance = EQUAL;
        }

        // Destrutor
        ~TreeNode()
        {
            // Note que destrui��o de um n� iniciar� uma opera��o
			//   em cadeia em todos os seus filhos. Caso um dos
			//   filhos n�o deva ser apagado, deve-se setar NULL
			//   em sua refer�ncia antes de destruir este n�.
            delete this->Subtree[LEFT];
            delete this->Subtree[RIGHT];
        }


        // Balanceamento do n�
        unsigned short Balance;

        // Filhos da �rvore
        // As sub�rvores direita e esquerda devem ser acessadas
        // utilizando apenas ->Subtree[LEFT] e ->Subtree[RIGHT]
        TreeNode* Subtree[2];

        // Arranjo <chave, valor>
        //  associado ao n�
        string Key;
        unsigned long Value;
};


#endif // TREENODE_H_INCLUDED

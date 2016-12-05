#include <iostream>
#include <string>
#include <fstream>
#include "avl_tree.h"

using namespace std;


// -------------------------------------------------
// Construtor & Destrutor
// -------------------------------------------------
// Construtor
AvlTree::AvlTree()
{
    // Inicializamos a ra�z com null.
    this->root = NULL;
}

// Destrutor
AvlTree::~AvlTree()
{
    this->Clear();
}

// Limpa a �rvore (remove todos seus n�s)
void AvlTree::Clear()
{
    // O destrutor de TreeNode cuidar�
    //  de destruir todas as sub�rvores.
    delete root;
    this->root = NULL;
}




// -------------------------------------------------
// Pesquisa
// -------------------------------------------------
// Procura um item na �rvore, realizando pesquisa bin�ria.
//   aceita como par�metro uma string como chave de busca.
//   retorna o item procurado ou NULL caso n�o o encontre.
bool AvlTree::Search(const string& chave, unsigned long& value)
{
    // Come�amos com a raiz
    TreeNode* current = this->root;

    // Como, por defini��o, a �rvore AVL est�
    //  ordenada, utilizamos a pesquisa bin�ria
    while (current != NULL)
    {
        // Comparamos
        if (chave > current->Key)
        {
            // O valor est� mais � direita
            current = current->Subtree[RIGHT];
        }
        else if (chave < current->Key)
        {
            // O valor est� mais � esquerda
            current = current->Subtree[LEFT];
        }
        else
        {
            // Achamos, retornamos o item
            value = current->Value;
            return true;
        }
    }

    // O valor n�o estava na �rvore
    return false;
}





// -------------------------------------------------
// Rota��es
// -------------------------------------------------
// Realiza uma rota��o simples numa determinada dire��o.
//  aceita como par�metro um n� onde a opera��o ser� efetuada
//  e uma dire��o (esquerda ou direita) para realizar a rota��o.
void AvlTree::rotateOnce(TreeNode*& node, Direction dir)
{
    int opposite = this->opposite(dir);

    TreeNode* child = node->Subtree[dir];
    node->Subtree[dir] = child->Subtree[opposite];
    child->Subtree[opposite] = node;

    node = child;
}

// Realiza uma rota��o dupla numa determinada dire��o.
//  aceita como par�metro um n� onde a opera��o ser� efetuada
//  e uma dire��o (esquerda ou direita) para realizar a rota��o.
void AvlTree::rotateTwice(TreeNode*& node, Direction dir)
{
    int opposite = this->opposite(dir);

    TreeNode* child = node->Subtree[dir]->Subtree[opposite];
    node->Subtree[dir]->Subtree[opposite] = child->Subtree[dir];
    child->Subtree[dir] = node->Subtree[dir];
    node->Subtree[dir] = child;
    child = node->Subtree[dir];
    node->Subtree[dir] = child->Subtree[opposite];
    child->Subtree[opposite] = node;

    node = child;
}





// -------------------------------------------------
// Balanceamento
// -------------------------------------------------
// Atualiza os fatores de balanceamento ap�s uma rota��o
void AvlTree::updateBalance(TreeNode* node, Direction dir)
{
    int opposite = this->opposite(dir);

    int bal = node->Subtree[dir]->Subtree[opposite]->Balance;

    // Se o fator est� pesado no mesmo lado
    if (bal == dir)
    {
        node->Balance = EQUAL;
        node->Subtree[dir]->Balance = opposite;
    }

    // Se o fator est� pesado do lado oposto
    else if (bal == opposite)
    {
        node->Balance = dir;
        node->Subtree[dir]->Balance = EQUAL;
    }

    else // O fator de balanceamento est� igual
    {
        node->Balance = node->Subtree[dir]->Balance = EQUAL;
    }

    node->Subtree[dir]->Subtree[opposite]->Balance = EQUAL;
}

// Efetua o rebalanceamento ap�s uma opera��o de inser��o
void AvlTree::rebalanceInsert(TreeNode*& node, Direction dir,
							  bool& hChanged)
{
    int opposite = this->opposite(dir);

    // Se o fator de balanceamento do n� era
    //  igual a dire��o em que houve a inser��o,
    if (node->Balance == dir) // (ou seja o n� foi inserido
    {                         //  na sub�rvore de maior altura
        // Temos 2 casos:
        if (node->Subtree[dir]->Balance == dir)
        {
            node->Subtree[dir]->Balance = 2;
            node->Balance = EQUAL;

            // Precisamos fazer uma rota��o
            rotateOnce(node, dir);
        }
        else // Seu filho estava equilibrado ou
        {    //  pendendo para o lado oposto,

            updateBalance(node, dir);
            rotateTwice(node, dir);
        }

        hChanged = false;
    }

    // J� se foi exatamente o oposto,
    else if (node->Balance == opposite)
    {
        // O n� agora est� balanceado
        node->Balance = 2;
        hChanged = false;
    }

    else // Se n�o, o n� j� estava equilibrado
    {
        // e agora seu equilibrio foi deslocado.
        node->Balance = dir;
    }
}

// Efetua o rebalanceamento ap�s uma opera��o de remo��o
void AvlTree::rebalanceRemove(TreeNode*& node, Direction dir,
							  bool& hChanged)
{
    Direction opposite = this->opposite(dir);

    // Se o fator de balanceamento do n� era
    //  igual a dire��o em que houve a remo��o,
    if (node->Balance == dir) // (ou seja, o n� foi removido
    {                         //da sub�rvore de maior altura)

        // o n� agora est� balanceado.
        node->Balance = EQUAL;
    }

    // J� se era o oposto,
    else if (node->Balance == opposite)
    {
        // Temos 3 casos:
        if (node->Subtree[opposite]->Balance == opposite)
        {
            // Se o filho do outro lado estava "mais pesado"
            //  do lado oposto, ent�o
            node->Subtree[opposite]->Balance = EQUAL;
            node->Balance = EQUAL;
            rotateOnce(node, opposite);
        }
        else if (node->Subtree[opposite]->Balance == EQUAL)
        {
            // Se o filho do outro lado estava equilibrado,
            node->Subtree[opposite]->Balance = dir;
            rotateOnce(node, opposite);
        }
        else
        {
            // Se o filho do outro lado estava "mais pesado"
            //  do lado mais pr�ximo de onde foi feita a inser��o,
            updateBalance(node, opposite);
            rotateTwice(node, opposite);
        }

        hChanged = false;
    }
    else
    {
        node->Balance = opposite;
        hChanged = false;
    }
}





// -------------------------------------------------
// M�todos de Inser��o
// -------------------------------------------------
// Insere um novo item na �rvore, aceitando seus componentes
//   palavra (chave) e origem (dado)
void AvlTree::Insert(const string& chave, const unsigned long& value)
{
    bool hChanged = false; // Para passagem por refer�ncia

    // Chamamos o m�todo recursivo para realizar a opera��o
    this->insert(chave, value, this->root, hChanged);
}


// Insere um novo item na �rvore (recursivo)
void AvlTree::insert(const string& chave, const unsigned long& value,
                        TreeNode*& node, bool& hChanged)
{
    // Se o n� atual � nulo,
    if (node == NULL)
    {
        // � aqui mesmo onde vamos inserir
        node = new TreeNode(chave, value);

        // marcamos que a altura mudou, �
        //  preciso chegar o balanceamento
        hChanged = true;
    }

    else if (node->Key == chave)
    {
        // A informa��o j� estava na �rvore
        return;
    }

    else // Ainda n�o chegamos onde quer�amos
    {
        // Prosseguimos com a pesquisa bin�ria
        Direction dir = (chave > node->Key) ? RIGHT : LEFT;

        hChanged = false; // preparamos e chamamos recurs�o
        insert(chave, value, node->Subtree[dir], hChanged);


        if (hChanged) // Se a altura mudou,
        {
            // Efetuamos o rebalanceamento
            this->rebalanceInsert(node, dir, hChanged);
        }
    }
}




// -------------------------------------------------
// M�todos de Remo��o
// -------------------------------------------------
// Remove um item da �rvore a partir de sua chave (palavra)
//  retorna true caso o item tenha sido removido com sucesso,
//  falso caso o item n�o tenha sido encontrado na �rvore.
bool AvlTree::Remove(const string& palavra)
{
    bool hChanged = false; // para passagem por refer�ncia

    // Chamamos o m�todo recursivo para realizar a opera��o.
    return this->remove(palavra, this->root, hChanged);
}

// Remove um item da �rvore a partir de sua chave (palavra)
//  retorna true caso o item tenha sido removido com sucesso,
//  falso caso o item n�o tenha sido encontrado na �rvore. (recursivo)
bool AvlTree::remove(const string& chave, TreeNode*& node,
					 bool& hChanged)
{
   // debug("Tree: remocao recursiva: " + chave + ", " + node->Key);
    bool success = false;

    // O n� n�o foi encontrado
    if (node == NULL)
    {
        hChanged = false;
        return false;
    }

    // Achamos o n�
    else if (chave == node->Key)
    {

        // Se o n� tiver ambos os filhos
        if (node->Subtree[LEFT] != NULL && node->Subtree[RIGHT] != NULL )
        {
            // Encontraremos um substituto para o n�
            TreeNode* substitute = node->Subtree[LEFT];

            // Navegamos at� o n� mais a direita da sub�rvore da esquerda
            while (substitute->Subtree[RIGHT] != NULL)
            {
                substitute = substitute->Subtree[RIGHT];
            }

            // Trocamos suas informa��es <chave,valor>
            node->Key   = substitute->Key;

            // Chamamos recurs�o para remover o n�
            success = remove(node->Key, node->Subtree[LEFT], hChanged);

            if (hChanged) // Se a altura mudou,
            {
                // Rebalanceamos
                rebalanceRemove(node, LEFT, hChanged);
            }
        }

        else // O n� tem apenas um ou nenhum filho
        {
            // Preparamos para apagar o n�
            TreeNode* temp = node;

            // Vemos se um dos seus filhos � diferente de NULL
            Direction dir = (node->Subtree[LEFT] == NULL) ? RIGHT : LEFT;

            // Substitu�mos o n� por um dos seus filhos
            node = node->Subtree[dir];

            // Deletamos o n� (lembramos que devemos
            //  setar os filhos para null para que o
            //  destrutor n�o inicie a destru��o em cadeia
            temp->Subtree[LEFT]  = NULL;
            temp->Subtree[RIGHT] = NULL;
            delete temp;

            // A altura mudou, propagamos a mudan�a
            hChanged = true;
        }

        // Retornamos verdadeiro, achamos o n�
        //  e a opera��o foi conclu�da
        return true;
    }

    else // Ainda n�o encontramos o n�
    {
        // Continuamos procurando (pesquisa bin�ria)
        Direction dir = (chave > node->Key) ? RIGHT : LEFT;

        if (node->Subtree[dir] != NULL)
        {
            // Recurs�o para a dire��o onde dever� estar a chave
            success = this->remove(chave, node->Subtree[dir], hChanged);
        }
        else
        {
            // O n� n�o est� na �rvore
            hChanged = false;
            return false;
        }

        if (hChanged) // Se a altura mudou,
        {
            // Rebalanceamos
            this->rebalanceRemove(node, dir, hChanged);
        }

        // Retornamos informando se achamos o n� ou n�o
        return success;
    }
}




// -------------------------------------------------
// M�todos de Impress�o (exibir na tela)
// -------------------------------------------------
// Exibe a �rvore na tela utilizando arte ASCII. �rvores
//  muito grandes ou esparsas ter�o dificuldade para
//  caberem no console.
// void AvlTree::Print()
// {
//     // Verificamos se h� �rvore
//     if (this->root != NULL)
//     {
//         // Instanciamos um novo objeto da classe AsciiTreeView
//         AsciiTreeView treeView(this);
//
//         // Solicitamos a impress�o.
//         treeView.Print();
//     }
//     else // A �rvore est� vazia
//     {
//         cout << "Arvore vazia" << endl;
//     }
// }

// Imprime detalhes sobre cada n� da �rvore,
//  percorrendo-a em ordem.
// void AvlTree::PrintNodeDetails()
// {
//     this->printNodeDetails(this->root);
// }

// Imprime detalhes sobre cada n� da �rvore,
//  percorrendo-a em ordem (recursivo).
void AvlTree::printNodeDetails(TreeNode* node)
{
    if (node != NULL)
    {
        this->printNodeDetails(node->Subtree[LEFT]);
        cout << "Node Key: "  << node->Key     << endl;
        cout << "- Origem: "  << node->Value   << endl;
        cout << "- Balance: " << node->Balance << endl;
        if (node->Subtree[LEFT] != NULL)
        cout << "- Left: "  << node->Subtree[LEFT]->Key << endl;
        if (node->Subtree[RIGHT] != NULL)
        cout << "- Right: " << node->Subtree[RIGHT]->Key << endl;

        cout << endl;
        this->printNodeDetails(node->Subtree[RIGHT]);
    }
}




// -------------------------------------------------
// M�todos para Salvar & Carregar
// -------------------------------------------------
// Carrega uma �rvore a partir de um arquivo, aceitando
//  como entrada o seu caminho.
AvlTree* AvlTree::Load(const char* path)
{
    // Constr�i a �rvore a partir do arquivo, construindo
    //  a �rvore diretamente j� que os items no arquivo
    //  foram armazenados em pr�-ordem.
    //  (e portanto o carregamento ser� da ordem de O(n)
    ifstream stream(path);

    if (stream.is_open())
    {
        AvlTree* tree = new AvlTree();

        string chave;
        int value;

        while (!stream.eof())
        {
            // Lemos os valores:
            //  primeiro a palavra, depois a origem
            stream >> chave;
            stream >> value;

            if (stream.fail()) break;


            // Inserimos na �rvore. Como estamos lendo
            //  em pr�-ordem, esta opera��o dura O(1)
            tree->Insert(chave, value);
        }
        stream.close();
        return tree;
    }

    return NULL;
}


// Salva a �rvore para um arquivo em disco, aceitando
//  uma cadeia de caracteres indicando seu caminho.
//  Retorna true em caso de sucesso, falso caso contr�rio.
bool AvlTree::Save(const char* path)
{
    // Se a �rvore est� vazia,
    if (this->root == NULL)
    {
        // Apagamos o arquivo.
        std::remove(path);
        return true;
    }

    // Armazenamos as entradas no arquivo, salvando
    //  as entradas em pr�-ordem, primeiro a palavra,
    //  depois a origem.
    ofstream stream(path);

    if (stream.is_open())
    {
        // Chamamos fun��o recursiva
        this->save(stream, this->root);
        stream.close();

        // Arquivo salvo com sucesso
        return true;
    }
    else
    {
        // Erro ao salvar arquivo
        return false;
    }
}

// Salva a �rvore para um arquivo, recursivamente, de n�
//  em n�, em pr�-ordem, retornando false em caso de erro.
bool AvlTree::save(ofstream& stream, TreeNode* node)
{
    if (stream.is_open())
    {
        if (node != NULL)
        {

            // Salvamos os valores em pr�-ordem;
            //  primeiro a palavra, depois a origem
            stream << node->Key   << endl;
            stream << node->Value << endl;

            // Caminhamos com a recurs�o
            this->save(stream, node->Subtree[LEFT]);
            this->save(stream, node->Subtree[RIGHT]);
        }
        // N� salvo com sucesso
        return true;
    }
    // Algum erro ocorreu
    else return false;
}





// -------------------------------------------------
// M�todos Auxiliares
// -------------------------------------------------
// Retorna a dire��o oposta � dire��o dada
inline Direction AvlTree::opposite(Direction dir)
{
    return (dir == RIGHT) ? LEFT : RIGHT;
}

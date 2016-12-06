#include <iostream>
#include <string>
#include <fstream>
#include "avl_tree.h"

using namespace std;

AvlTree::AvlTree()
{
    this->root = NULL;
}

/*  Destrutor */
AvlTree::~AvlTree()
{
    this->Clear();
}

/*  Limpa a árvore (remove todos seus nós). */
void AvlTree::Clear()
{
    delete root;
    this->root = NULL;
}

/*  Procura um item na árvore, realizando pesquisa binária.
    Aceita como parâmetro uma string como chave de busca.
    Retorna o item procurado ou NULL caso não o encontre.
*/
bool AvlTree::Search(const string& chave, unsigned long& value)
{
    TreeNode* current = this->root;

    while (current != NULL)
    {
        if (chave > current->Key) {
            current = current->Subtree[RIGHT];
        } else if (chave < current->Key) {
            current = current->Subtree[LEFT];
        } else {
            value = current->Value;
            return true;
        }
    }
    return false;
}

/*  Realiza uma rotação simples numa determinada direção.
    Aceita como parâmetro um nó onde a operação será efetuada e uma direção
    (esquerda ou direita) para realizar a rotação.
*/
void AvlTree::rotateOnce(TreeNode*& node, Direction dir)
{
    int opposite = this->opposite(dir);

    TreeNode* child = node->Subtree[dir];
    node->Subtree[dir] = child->Subtree[opposite];
    child->Subtree[opposite] = node;

    node = child;
}

/*  Realiza uma rotação dupla numa determinada direção.
    Aceita como parâmetro um nó onde a operação será efetuada e uma direção
    (esquerda ou direita) para realizar a rotação.
*/
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

/*  Atualiza os fatores de balanceamento após uma rotação. */
void AvlTree::updateBalance(TreeNode* node, Direction dir)
{
    int opposite = this->opposite(dir);
    int bal = node->Subtree[dir]->Subtree[opposite]->Balance;

    if (bal == dir) {
        node->Balance = EQUAL;
        node->Subtree[dir]->Balance = opposite;

    } else if (bal == opposite) {
        node->Balance = dir;
        node->Subtree[dir]->Balance = EQUAL;

    } else {
        node->Balance = node->Subtree[dir]->Balance = EQUAL;
    }

    node->Subtree[dir]->Subtree[opposite]->Balance = EQUAL;
}

/*  Efetua o rebalanceamento após uma operação de inserção. */
void AvlTree::rebalanceInsert(TreeNode*& node, Direction dir, bool& hChanged)
{
    int opposite = this->opposite(dir);

    if (node->Balance == dir) {

        if (node->Subtree[dir]->Balance == dir) {
            node->Subtree[dir]->Balance = 2;
            node->Balance = EQUAL;

            rotateOnce(node, dir);
        } else {
            updateBalance(node, dir);
            rotateTwice(node, dir);
        }
        hChanged = false;

    } else if (node->Balance == opposite) {
        node->Balance = 2;
        hChanged = false;
    } else {
        node->Balance = dir;
    }
}

/*  Efetua o rebalanceamento após uma operação de remoção. */
void AvlTree::rebalanceRemove(TreeNode*& node, Direction dir, bool& hChanged)
{
    Direction opposite = this->opposite(dir);

    if (node->Balance == dir) {
        node->Balance = EQUAL;
    } else if (node->Balance == opposite) {

        if (node->Subtree[opposite]->Balance == opposite)
        {
            node->Subtree[opposite]->Balance = EQUAL;
            node->Balance = EQUAL;
            rotateOnce(node, opposite);
        } else if (node->Subtree[opposite]->Balance == EQUAL) {
            node->Subtree[opposite]->Balance = dir;
            rotateOnce(node, opposite);
        } else {
            updateBalance(node, opposite);
            rotateTwice(node, opposite);
        }

        hChanged = false;
    } else {
        node->Balance = opposite;
        hChanged = false;
    }
}

/*  Insere um novo item na Árvore, aceitando seus componentes (chave e dado). */
void AvlTree::Insert(const string& chave, const unsigned long& value)
{
    bool hChanged = false;
    this->insert(chave, value, this->root, hChanged);
}

/*  Insere um novo item na Árvore (recursivo) */
void AvlTree::insert(const string& chave, const unsigned long& value, TreeNode*& node, bool& hChanged)
{
    if (node == NULL) {
        node = new TreeNode(chave, value);
        hChanged = true;
    } else if (node->Key == chave) {
        return;
    } else {
        Direction dir = (chave > node->Key) ? RIGHT : LEFT;

        hChanged = false;
        insert(chave, value, node->Subtree[dir], hChanged);

        if (hChanged) {
            this->rebalanceInsert(node, dir, hChanged);
        }
    }
}

/*  Remove um item da Árvore a partir de sua chave. Retorna true caso o item
    tenha sido removido com sucesso, falso caso o item não tenha sido
    encontrado na árvore.
*/
bool AvlTree::Remove(const string& palavra)
{
    bool hChanged = false;
    return this->remove(palavra, this->root, hChanged);
}

/*  Remove um item da Árvore a partir de sua chave. Retorna true caso o item
    tenha sido removido com sucesso, falso caso o item não tenha sido
    encontrado na árvore. (recursivo)
*/
bool AvlTree::remove(const string& chave, TreeNode*& node, bool& hChanged)
{
    bool success = false;

    if (node == NULL) {
        hChanged = false;
        return false;
    } else if (chave == node->Key) {

        if (node->Subtree[LEFT] != NULL && node->Subtree[RIGHT] != NULL ) {
            TreeNode* substitute = node->Subtree[LEFT];

            while (substitute->Subtree[RIGHT] != NULL) {
                substitute = substitute->Subtree[RIGHT];
            }

            node->Key = substitute->Key;
            success = remove(node->Key, node->Subtree[LEFT], hChanged);

            if (hChanged) {
                rebalanceRemove(node, LEFT, hChanged);
            }
        } else {
            TreeNode* temp = node;
            Direction dir = (node->Subtree[LEFT] == NULL) ? RIGHT : LEFT;
            node = node->Subtree[dir];

            temp->Subtree[LEFT]  = NULL;
            temp->Subtree[RIGHT] = NULL;
            delete temp;
            hChanged = true;
        }
        return true;

    } else {
        Direction dir = (chave > node->Key) ? RIGHT : LEFT;

        if (node->Subtree[dir] != NULL) {
            success = this->remove(chave, node->Subtree[dir], hChanged);
        } else {
            hChanged = false;
            return false;
        }

        if (hChanged) {
            this->rebalanceRemove(node, dir, hChanged);
        }

        return success;
    }
}

/*  Imprime detalhes sobre cada nó da Árvore, percorrendo-a em ordem. */
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

/*  Carrega uma Árvore a partir de um arquivo, aceitando como parâmetro
    o seu caminho.
*/
AvlTree* AvlTree::Load(const char* path)
{
    ifstream stream(path);

    if (stream.is_open()) {
        AvlTree* tree = new AvlTree();

        string chave;
        int value;

        while (!stream.eof()) {
            stream >> chave;
            stream >> value;

            if (stream.fail()) break;

            tree->Insert(chave, value);
        }
        stream.close();
        return tree;
    }
    return NULL;
}

/*  Salva a Árvore para um arquivo em disco, aceitando como parâmetro o
    seu caminho. Retorna true em caso de sucesso, falso caso contrário.
*/
bool AvlTree::Save(const char* path)
{
    if (this->root == NULL) {
        std::remove(path);
        return true;
    }

    ofstream stream(path);

    if (stream.is_open()) {
        this->save(stream, this->root);
        stream.close();
        return true;
    } else {
        return false;
    }
}

/*  Salva a Árvore para um arquivo, recursivamente, de nó em nó, em pré-ordem,
    retornado false em caso de erro.
*/
bool AvlTree::save(ofstream& stream, TreeNode* node)
{
    if (stream.is_open()) {
        if (node != NULL) {
            stream << node->Key   << endl;
            stream << node->Value << endl;

            this->save(stream, node->Subtree[LEFT]);
            this->save(stream, node->Subtree[RIGHT]);
        }
        return true;
    } else {
        return false;
    }
}

/*  Retorna a direção oposta à direção data. */
inline Direction AvlTree::opposite(Direction dir)
{
    return (dir == RIGHT) ? LEFT : RIGHT;
}

#include "index_list.h"
#include "register_list.h"
#include <iostream>

IndexList::IndexList()
{
    size_ = 0;
    head = new Node();
    write = head;
}

IndexList::~IndexList()
{
    clear();
    delete(head);
}

void IndexList::clear()
{
    while (!empty()) {
        pop_front();
    }
}

void IndexList::push_back(const string& data, RegisterList* regAdress)
{
    insert(data, size(), regAdress);
}

void IndexList::push_front(const string& data, RegisterList* regAdress)
{
    Node* novo;
    novo = new Node(data, regAdress);

    if (novo == NULL) {
        throw std::out_of_range("Erro Lista Cheia!");
    } else {
        if(size() == 0) {
            head->next(novo);
            size_++;
            novo->incQuantidade();
        } else {
            novo->next(head->next());
            head->next(novo);
            novo->incQuantidade();
            size_++;
        }
    }
}

void IndexList::push_front(const string& data)
{
    Node* novo;
    novo = new Node(data);

    if (novo == NULL) {
        throw std::out_of_range("Erro Lista Cheia!");
    } else {
        if(size() == 0) {
            head->next(novo);
            novo->incQuantidade();
            size_++;
        } else {
            novo->next(head->next());
            head->next(novo);
            novo->incQuantidade();
            size_++;
        }
    }
}

void IndexList::insert(const string& data, std::size_t index, RegisterList* regAdress)
{
    Node *novo;
    Node *anterior;

    if (index < 0 || index > size_) {
        throw std::out_of_range("Erro Posição!");
    } else {

        if (index == 0) {
            push_front(data, regAdress);
        } else {
            novo = new Node(data, regAdress);

            if (novo == NULL) {
                throw std::out_of_range("Erro Lista Cheia!");

            } else {
                anterior = head->next();

                for (auto i = 0u; i < index - 1; ++i) {
                    anterior = anterior->next();
                }

                novo->next(anterior->next());
                anterior->next(novo);
                novo->incQuantidade();
                size_++;
            }
        }
    }
}

void IndexList::insert(const string& data, std::size_t index)
{
    Node *novo;
    Node *anterior;

    if (index < 0 || index > size_) {
        throw std::out_of_range("Erro Posição!");
    } else {

        if (index == 0) {
            push_front(data);
        } else {
            novo = new Node(data);

            if (novo == NULL) {
                throw std::out_of_range("Erro Lista Cheia!");

            } else {
                anterior = head->next();

                for (auto i = 0u; i < index - 1; ++i) {
                    anterior = anterior->next();
                }

                novo->next(anterior->next());
                anterior->next(novo);
                novo->incQuantidade();
                size_++;
            }
        }
    }
}

void IndexList::insert_sorted(const string& data, RegisterList* regAdress)
{
    Node* atual;
    auto posicao = 0;

    if (empty()) {
        push_front(data, regAdress);
    } else {
        atual = head->next();

        while (atual->next() != NULL && data > atual->data()) {
            atual = atual->next();
            posicao++;
        }

        if (data > atual->data()) {
            insert(data, posicao+1, regAdress);
        } else {
            insert(data, posicao, regAdress);
        }
    }
}

string& IndexList::at(std::size_t index)
{
    Node* anterior = head;

    if (empty()) {
        throw std::out_of_range("Erro Lista Vazia!");
    } else {
        if (index < 0 || index > size_) {
            throw std::out_of_range("ERRO");
        } else {

            anterior = head->next();

            for (auto i = 0; i < index; ++i) {
                anterior = anterior->next();
            }

            return anterior->data();
        }
    }
}

string IndexList::pop(std::size_t index)
{
    Node *atual;
    Node *eliminar;
    string volta = 0;

    if (index < 0 || index > size_ -1) {
        throw std::out_of_range("Erro Posição!");
    } else {
        if (index == 0) {
            pop_front();
        } else {
            atual = head->next();

            for (auto i = 0u; i < index - 1; ++i) {
                atual = atual->next();
            }

            eliminar = atual->next();
            volta = eliminar->data();

            if (index < size() - 1) {
                atual->next(eliminar->next());
            }

            size_--;
            delete(eliminar);
            return volta;
        }
    }

    return volta;
}

string IndexList::pop_back()
{
    if (empty()) {
        throw std::out_of_range("Erro Lista Vazia!");
    }
    return pop(size()-1);
}

string IndexList::pop_front()
{
    Node* saiu;
    string volta;

    if (empty()) {
        throw std::out_of_range("Erro Lista Vazia!");
    } else {
        saiu = head->next();
        volta = saiu->data();
        if (size_ > 0) {
            head->next(saiu->next());
        }
        size_--;
        delete(saiu);
        return volta;
    }
}

void IndexList::remove(const string& data)
{
    Node *atual = head->next();
    Node *anterior = head;

    while (atual->data() != data) {
        anterior = anterior->next();
        atual = atual->next();
    }

    anterior->next(atual->next());
    delete(atual);
    size_--;
}

bool IndexList::empty() const
{
    return (size_ == 0);
}

bool IndexList::contains(const string& data) const
{
    Node *anterior = head;

    for (auto i = 0u; i < size_; ++i) {
        anterior = anterior->next();
        if (anterior->data() == data) {
            return true;
        }
    }

    return false;
}

RegisterList* IndexList::find(const string& data) const
{
    auto i = 0u;
    Node* anterior = head->next();

    while (anterior->data() != data && i < size()) {
        ++i;

        if (i < size())
            anterior = anterior->next();
    }
    return anterior->getLista();
}

std::size_t IndexList::size() const
{
    return size_;
}

std::size_t IndexList::getQuantidadeNode(const string& data) const
{
    auto i = 0u;
    Node* anterior = head->next();

    while (anterior->data() != data && i < size()) {
        ++i;
        anterior = anterior->next();
    }
    return anterior->getQuantidade();
}

void IndexList::incQuantidadeNode(const string& data)
{
    auto i = 0u;
    Node* anterior = head->next();

    while (anterior->data() != data && i < size()) {
        ++i;
        anterior = anterior->next();
    }
    anterior->incQuantidade();
}

void IndexList::printaTodosOsElementos()
{
    Node* atual = head->next();

    while (atual->next() != nullptr) {
        cout << "= " << atual->data() << " | " << atual->getQuantidade() << " =" << endl;
        atual->getLista()->printaTodosOsElementos();
        atual = atual->next();
        cout << endl << endl;
    }

}

string IndexList::getWriteData()
{
    write = write->next();
    return write->data();
}

std::size_t IndexList::getWriteQtde()
{
    return write->getQuantidade();
}

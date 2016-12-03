#include "register_list.h"
#include <iostream>

RegisterList::RegisterList()
{
    size_ = 0;
    head = new Node();
    write = head;
}

RegisterList::~RegisterList()
{
    clear();
    delete head;
}

void RegisterList::clear()
{
    while (!empty()) {
        pop_front();
    }
}

void RegisterList::push_back_register(const int& data, size_t quantidade_)
{
    Node* atual;
    Node* novo;

   // if (novo == NULL) {
    //    throw std::out_of_range("Erro Lista Cheia!");
    //} else {
        if(size() == 0) {
            novo = new Node(data);
            novo->setQuantidade(quantidade_);
            head->next(novo);
            size_++;
        } else {
            atual = head->next();
            while (atual->data() != data && atual->next() != nullptr) {
                atual = atual->next();
            }
            if (atual->data() == data) {
                atual->setQuantidade(quantidade_);
            } else {
                novo = new Node(data);
                novo->setQuantidade(quantidade_);
                atual->next(novo);
                size_++;
            }
        }
    //}
}

void RegisterList::push_front(const int& data)
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

void RegisterList::insert(const int& data, std::size_t index)
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

int& RegisterList::at(std::size_t index)
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

int RegisterList::pop(std::size_t index)
{
    Node *atual;
    Node *eliminar;
    int volta = 0;

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

int RegisterList::pop_back()
{
    if (empty()) {
        throw std::out_of_range("Erro Lista Vazia!");
    }
    return pop(size()-1);
}

int RegisterList::pop_front()
{
    Node* saiu;
    int volta;

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

void RegisterList::remove(const int& data)
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

bool RegisterList::empty() const
{
    return (size_ == 0);
}

bool RegisterList::contains(const int& data) const
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

std::size_t RegisterList::size() const
{
    return size_;
}

std::size_t RegisterList::getQuantidadeNode(const int& data) const
{
    auto i = 0u;
    Node* anterior = head->next();

    while (anterior->data() != data && i < size()) {
        ++i;
        anterior = anterior->next();
    }
    return anterior->getQuantidade();
}

void RegisterList::incQuantidadeNode(const int& data)
{
    auto i = 0u;
    Node* anterior = head->next();

    while (anterior->data() != data && i < size()) {
        ++i;
        anterior = anterior->next();
    }
    anterior->incQuantidade();
}

void RegisterList::printaTodosOsElementos()
{
    Node* atual = head->next();

    while (atual->next() != nullptr) {
        cout << "[" << atual->data() << "]: " << atual->getQuantidade() << " ";
        atual = atual->next();
    }
}

int RegisterList::getWriteData()
{
    return write->data();
}

std::size_t RegisterList::getWriteQtde()
{
    write = write->next();
    return write->quantidade_;
}


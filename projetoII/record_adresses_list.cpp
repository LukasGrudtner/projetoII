#include "record_adresses_list.h"
#include <iostream>

RecordAdressesList::RecordAdressesList()
{
    size_ = 0;
    head = new Node();
    write = head;
}

RecordAdressesList::~RecordAdressesList()
{
    clear();
    delete head;
}

void RecordAdressesList::clear()
{
    while (!empty()) {
        pop_front();
    }
}

void RecordAdressesList::push_back(const string& data, size_t amount_)
{
    Node* atual;
    Node* novo;

    if(size() == 0) {
        novo = new Node(data);
        novo->set_amount(amount_);
        head->next(novo);
        size_++;
    } else {
        atual = head->next();
        while (atual->data() != data && atual->next() != nullptr) {
            atual = atual->next();
        }
        if (atual->data() == data) {
            atual->set_amount(amount_);
        } else {
            novo = new Node(data);
            novo->set_amount(amount_);
            atual->next(novo);
            size_++;
        }
    }
}

void RecordAdressesList::push_front(const string& data)
{
    Node* novo;
    novo = new Node(data);

    if (novo == NULL) {
        throw std::out_of_range("Erro Lista Cheia!");
    } else {
        if(size() == 0) {
            head->next(novo);
            novo->inc_amount();
            size_++;
        } else {
            novo->next(head->next());
            head->next(novo);
            novo->inc_amount();
            size_++;
        }
    }
}

void RecordAdressesList::insert(const string& data, size_t index)
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
                novo->inc_amount();
                size_++;
            }
        }
    }
}

string& RecordAdressesList::at(size_t index)
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

string RecordAdressesList::pop(size_t index)
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
            delete eliminar;
            return volta;
        }
    }

    return volta;
}

string RecordAdressesList::pop_back()
{
    if (empty()) {
        throw std::out_of_range("Erro Lista Vazia!");
    }
    return pop(size()-1);
}

string RecordAdressesList::pop_front()
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
        delete saiu;
        return volta;
    }
}

void RecordAdressesList::remove(const string& data)
{
    Node *atual = head->next();
    Node *anterior = head;

    while (atual->data() != data) {
        anterior = anterior->next();
        atual = atual->next();
    }

    anterior->next(atual->next());
    delete atual;
    size_--;
}

bool RecordAdressesList::empty() const
{
    return (size_ == 0);
}

bool RecordAdressesList::contains(const string& data) const
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

size_t RecordAdressesList::size() const
{
    return size_;
}

size_t RecordAdressesList::get_amount_node(const string& data) const
{
    auto i = 0u;
    Node* anterior = head->next();

    while (anterior->data() != data && i < size()) {
        ++i;
        anterior = anterior->next();
    }
    return anterior->get_amount();
}

void RecordAdressesList::inc_amount_node(const string& data)
{
    auto i = 0u;
    Node* anterior = head->next();

    while (anterior->data() != data && i < size()) {
        ++i;
        anterior = anterior->next();
    }
    anterior->inc_amount();
}

void RecordAdressesList::printsAllTheElements()
{
    Node* atual = head->next();

    while (atual->next() != nullptr) {
        cout << "[" << atual->data() << "]: " << atual->get_amount() << " ";
        atual = atual->next();
    }
}

string RecordAdressesList::get_write_data()
{
    return write->data();
}

std::size_t RecordAdressesList::get_write_amount()
{
    write = write->next();
    return write->amount_;
}

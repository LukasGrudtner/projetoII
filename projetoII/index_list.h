#ifndef INDEXLIST_H
#define INDEXLIST_H

#include <string>
#include <stdexcept>

#include "record_adresses_list.h"

using namespace std;

/*  Classe de Lista Encadeada para Lista de Índices. */
class IndexList
{
    public:
        /*  Construtor */
        IndexList();

        /*  Destrutor */
        virtual ~IndexList();

        /*  Limpa a lista, apagando elemento por elemento. */
        void clear();

        /*  Insere um elemento no fim da lista. */
        void push_back(const string& data, RecordAdressesList* regAdress);

        /*  Insere um elemento no início da lista. */
        void push_front(const string& data, RecordAdressesList* regAdress);

        /*  Insere um elemento no início da lista. */
        void push_front(const string& data);

        /*  Insere um elemento em uma posição informada por parâmetro. */
        void insert(const string& data, std::size_t index, RecordAdressesList* regAdress);

        /*  Insere um elemento em uma posição informada por parâmetro. */
        void insert(const string& data, std::size_t index);

        /*  Insere um elemento em uma posição ordenada. */
        void insert_sorted(const string& data, RecordAdressesList* regAdress);

        /*  Retorna o elemento na posição passada por parâmetro. */
        string& at(std::size_t index);

        /*  Remove o elemento na posição passada por parâmetro. */
        string pop(std::size_t index);

        /*  Remove o elemento do fim da lista. */
        string pop_back();

        /*  Remove o elemento do início da lista. */
        string pop_front();

        /*  Remove o elemento cuja dado é igual ao passado por parâmetro. */
        void remove(const string& data);

        /*  Verifica se a lista está vazia. */
        bool empty() const;

        /*  Verifica se o dado passado por parâmetro está contido na lista. */
        bool contains(const string& data) const;

        /*  Retorna a Lista de Endereços de Registro do elemento na lista. */
        RecordAdressesList* find(const string& data) const;

        /*  Retorna a quantidade do node com o dado passado por parâmetro. */
        std::size_t get_amount_node(const string& data) const;

        /*  Incrementa a quantidade do node com o dado passado por parâmetro. */
        void inc_amount_node(const string& data);

        /*  Retorna o tamanho da lista. */
        std::size_t size() const;

        /*  Retorna o dado do nodo à ser escrito pela classe Writer. */
        string get_write_data();

        /*  Retorna a quantidade do nodo à ser escrito pela classe Writer. */
        std::size_t get_write_amount();

        /*  Imprime todos os elementos da lista. */
        void printsAllTheElements();

    protected:

    private:
        class Node { // Elemento
         public:

            //! Construtor
            /*! Método construtor da classe Node com um parâmetro de dados.
                /param data dado a ser inserido no Node.
            */
            Node(){};

            Node(const string& data):
                data_{data}
            {}

            //! Construtor
            /*! Método construtor da classe Node com dois parâmetros.
                /param data dado a ser inserido no Node.
                /param next ponteiro para o próximo Node.
            */
            Node(const string& data, RecordAdressesList* list):
                data_{data},
                list_{list}
            {}

            //! Data
            /*! Método getter de um Node.
                /return o dado do elemento.
            */
            string& data() {
                return data_;
            }

            //! Data Const
            /*! Método getter de um Node, onde o dado retornado não será alterado.
                /return o dado do elemento.
            */
            const string& data() const {
                return data_;
            }

            //! Next
            /*! Método getter de um Node.
                /return o ponteiro para o próximo elemento.
            */
            Node* next() { // getter: próximo
                return next_;
            }

            //! Next
            /*! Método getter de um Node, onde o ponteiro retornado não será alterado.
                /return o ponteiro para o próximo elemento.
            */
            const Node* next() const {
                return next_;
            }

            //! Next
            /*! Método setter de um Node.
                /param um ponteiro, que será o indicador do próximo elemento.
            */
            void next(Node* node) { // setter: próximo
                next_ = node;
            }

            void inc_amount() {
                amount_++;
            }

            void set_amount(std::size_t amount) {
                amount_ = amount;
            }

            void set_list(RecordAdressesList* list) {
                list_ = list;
            }

            RecordAdressesList* get_list() {
                return list_;
            }

            std::size_t get_amount() {
                return amount_;
            }

         private:
            string data_; /**< Declaração do dado, do tipo T. */
            std::size_t amount_ = 0; /* Quantidade do nodo */
            RecordAdressesList* list_{nullptr}; /* Ponteiro para a lista de
                                                endereços de registro do nodo */
            Node* next_{nullptr}; /**< Declaração do ponteiro para o próximo Node. */
    };

    Node* head{nullptr}; /**< Declaração da cabeça da lista. */
    std::size_t size_{0u}; /**< Declaração do tamanho da lista. */
    Node* write;

};

#endif // INDEXLIST_H

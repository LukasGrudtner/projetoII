#ifndef REGISTERLIST_H
#define REGISTERLIST_H

#include <string>
#include <stdexcept>

using namespace std;

class RegisterList
{
    public:
        RegisterList();
        virtual ~RegisterList();
        void clear();
        void push_back_register(const int& data, std::size_t quantidade_);
        void push_front(const int& data);
        void insert(const int& data, std::size_t index);
        int& at(std::size_t index);
        int pop(std::size_t index);
        int pop_back();
        int pop_front();
        void remove(const int& data);
        bool empty() const;
        bool contains(const int& data) const;
        std::size_t getQuantidadeNode(const int& data) const;
        void incQuantidadeNode(const int& data);
        void setQuantidadeNode(const int& data);
        std::size_t size() const;

    protected:

    private:
        class Node { // Elemento
         public:

            //! Construtor
            /*! Método construtor da classe Node com um parâmetro de dados.
                /param data dado a ser inserido no Node.
            */
            Node(){};

            Node(const int& data):
                data_{data}
            {}

            //! Data
            /*! Método getter de um Node.
                /return o dado do elemento.
            */
            int& data() {
                return data_;
            }

            //! Data Const
            /*! Método getter de um Node, onde o dado retornado não será alterado.
                /return o dado do elemento.
            */
            const int& data() const {
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

            void incQuantidade() {
                quantidade_++;
            }

            void setQuantidade(std::size_t quantidade) {
                quantidade_ = quantidade;
            }

            std::size_t getQuantidade() {
                return quantidade_;
            }

         private:
            int data_; /**< Declaração do dado, do tipo T. */
            std::size_t quantidade_ = 0;
            Node* next_{nullptr}; /**< Declaração do ponteiro para o próximo Node. */
    };

    Node* head{nullptr}; /**< Declaração da cabeça da lista. */
    std::size_t size_{0u}; /**< Declaração do tamanho da lista. */

};

#endif // REGISTERLIST_H


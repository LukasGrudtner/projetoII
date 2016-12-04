#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <string>
#include <stdexcept>

using namespace std;

class BinaryTree
{
    public:
        BinaryTree();
        virtual ~BinaryTree();
        void insert(const string& data, const string& contents);
        void remove(const string& data);
        bool contains(const string& data) const;
        bool empty() const;
        std::size_t size() const;


    protected:

    private:
        struct Node {
            explicit Node(const string& data, const string& contents) {
                left_ = nullptr;
                right_ = nullptr;
                data_ = data;
                contents_ = contents;
            }

            string data_;         /**< Declaração da dado. */
            string contents_;
            Node* left_;  /**< Declaração do ponteiro para o filho da esquerda. */
            Node* right_; /**< Declaração do ponteiro para o filho da direita. */

            //! Insert
            /*! Insere elementos na árvore binária.
                \param data o dado para ser inserido na lista.
            */
            void insert(const string& data, const string& contents) {
                Node* novo;

                if (data < data_) {  // Inserção à esquerda.
                    if (left_ == nullptr) {
                        novo = new Node(data, contents);
                        novo->left_ = nullptr;
                        novo->right_ = nullptr;
                        left_ = novo;
                    } else {
                        left_->insert(data, contents);
                    }
                } else {  // Inserção à direita.
                    if (right_ == nullptr) {
                        novo = new Node(data, contents);
                        novo->left_ = nullptr;
                        novo->right_ = nullptr;
                        right_ = novo;
                    } else {
                        right_->insert(data, contents);
                    }
                }
            }

            //! Remove
            /*! Remove um elemento específico.
                /param data conteúdo do elemento a ser removido.
            */
            bool remove(const string& data) {
                Node* aux;

                if (this == NULL) {
                    return false;
                } else {
                    if (data < data_) {  // Vá à esquerda.
                        return left_->remove(data);
                    } else {
                        if (data > data_) {  // Vá à direita.
                            return right_->remove(data);
                        } else {  // Encontrei o elemento que quero deletar.
                            if (right_ != nullptr && left_ != nullptr) {
                                aux = right_->minimo();
                                data_ = aux->data_;
                                return right_->remove(data_);
                            } else {  // Tem 1 filho.
                                if (right_ != nullptr) {  // Filho à direita.
                                    data_ = right_->data_;
                                    return right_->remove(data_);
                                } else {
                                    if (left_ != nullptr) {  // Filho à esquerda.
                                        data_ = left_->data_;
                                        return left_->remove(data_);
                                    } else {  // Folha.
                                        delete this;
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            //! Minimo
            /*! Retorna o node mínimo da esquerda.
            */
            Node* minimo() {
                Node* minimo = this;
                while (minimo->left_ != nullptr) {
                    minimo = minimo->left_;
                }
                return minimo;
            }

            //! Contains
            /*! Verifica se o parâmetro data está na árvore.
                /param data o dado que será verificado se está contido na árvore.
                /return um valor do tipo bool.
            */
            bool contains(const string& data) const {
                if (data == data_)
                    return true;
                if (data < data_ && left_ != nullptr)
                    return left_->contains(data);
                if (data > data_ && right_ != nullptr)
                    return right_->contains(data);
                return false;
            }
    };
    Node* root;             /**< Declaração da raiz da árvore. */
    std::size_t size_;      /**< Declaração do tamanho da árvore. */
};

#endif // BINARYTREE_H

#include "binary_tree.h"

BinaryTree::BinaryTree()
{
    root = nullptr;
    size_ = 0u;
}

BinaryTree::~BinaryTree()
{
    delete root;
}

void BinaryTree::insert(const string& data, const string& contents)
{
    if (empty()) {
        root = new Node(data, contents);
        size_++;
    } else {
        root->insert(data, contents);
        size_++;
    }
}

void BinaryTree::remove(const string& data)
{
    if (empty()) {
        throw std::out_of_range("Erro!");
    } else {
        if (root->remove(data)) {
            size_--;
        }
    }
}

bool BinaryTree::contains(const string& data) const
{
    return root->contains(data);
}

bool BinaryTree::empty() const
{
    return size_ == 0;
}

std::size_t BinaryTree::size() const
{
    return size_;
}

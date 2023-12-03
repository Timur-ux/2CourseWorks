#ifndef BIN_TREE_H_
#define BIN_TREE_H_

#include <memory>
#include <stdexcept>

template <typename TData>
class BinTree {
private:
    struct Node {
        int id;
        TData data;
        std::shared_ptr<Node> right;
        std::shared_ptr<Node> left;

        Node(int _id, TData _data) : id(_id), data(_data), right(nullptr), left(nullptr) {}
    };

    std::shared_ptr<Node>root{ nullptr };
public:
    BinTree() = default;

    void add(int id, TData data);
    void remove(int id);
    TData find(int id);
};

template <typename TData>
inline BinTree<TData>::add(int id, TData data) {
    if (!root) {
        root = std::make_shared<Node>(id, data);
        return;
    }

    std::shared_ptr<Node> currentNode = root;
    while (true) {
        if (id == currentNode->id) {
            throw std::invalid_argument("Already exist");
        }
        if (id > currentNode->id) {
            if (currentNode->right == nullptr) {
                currentNode->right = std::make_shared<Node>(id, data);
                return;
            }

            currentNode = currentNode->right;
            continue;
        }
        if (id < currentNode->id) {
            if (currentNode->left == nullptr) {
                currentNode->left = std::make_shared<Node>(id, data);
                return;
            }

            currentNode = currentNode->left;
            continue;
        }
    }
}

#endif
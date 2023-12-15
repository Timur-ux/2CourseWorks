#include "BinTree.hpp"
#include <iostream>

bool closeProcess(PROCESS_INFORMATION pi) {
    return TerminateProcess(
        pi.hProcess
        , 0
    );
}

std::shared_ptr<BinTree::Node> BinTree::findNode(long long id) {
    if (!root) {
        throw std::invalid_argument("id: Not found");
    }
    std::shared_ptr<Node> currentNode = root;
    while (currentNode->id != id) {
        if (id > currentNode->id) {
            if (currentNode->right == nullptr) {
                throw std::invalid_argument("id: Not found");
            }
            currentNode = currentNode->right;
        }
        else if (id < currentNode->id) {
            if (currentNode->left == nullptr) {
                throw std::invalid_argument("id: Not found");
            }
            currentNode = currentNode->left;
        }
    }

    return currentNode;
}

void BinTree::add(long long id, CalcCenterData data) {
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

void BinTree::remove(long long id) {
    std::shared_ptr<Node> currentNode = root;
    std::shared_ptr<Node> parentNode = nullptr;
    while (currentNode->id != id) {
        if (id > currentNode->id) {
            if (currentNode->right == nullptr) {
                throw std::invalid_argument("id: Not found");
            }

            parentNode = currentNode;
            currentNode = currentNode->right;
        }
        else if (id < currentNode->id) {
            if (currentNode->left == nullptr) {
                throw std::invalid_argument("id: Not found");
            }

            parentNode = currentNode;
            currentNode = currentNode->left;
        }
    }

    if (!parentNode) {
        if (!root->left && !root->right) {
            root = nullptr;
        }
        else if (root->right) {
            root = root->right;
        }
        else {
            root = root->left;
        }
        return;
    }

    if (parentNode->right == currentNode) {
        std::shared_ptr<Node> cr = currentNode->right, cl = currentNode->left, crl;
        parentNode->right = cr;
        if (cr) {
            crl = cr->left;
        }
        else {
            return;
        }

        while (crl && crl->left != nullptr) {
            crl = crl->left;
        }

        crl->left = cl;
    }
    else if (parentNode->left == currentNode) {
        std::shared_ptr<Node> cr = currentNode->right, cl = currentNode->left, clr;
        parentNode->left = cl;
        if (cl) {
            clr = cl->right;
        }
        else {
            return;
        }

        if (clr == nullptr) {
            cl->right = cr;
        }

        while (clr && clr->right != nullptr) {
            clr = clr->right;
        }

        clr->right = cr;
    }
}

CalcCenterData BinTree::find(long long id) {
    return findNode(id)->data;
}

void BinTree::closeAllProcesses(std::shared_ptr<Node> fromNode) {
    if (!fromNode) {
        return;
    }

    closeAllProcesses(fromNode->right);
    closeAllProcesses(fromNode->left);

    CloseHandle(fromNode->data.pi->hProcess);
    closeProcess(*fromNode->data.pi);
    remove(fromNode->id);
}

BinTree::~BinTree() {
    closeAllProcesses(root);
}
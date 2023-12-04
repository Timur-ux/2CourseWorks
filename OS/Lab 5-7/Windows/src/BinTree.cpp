#include "BinTree.hpp"
#include <iostream>

bool closeProcess(PROCESS_INFORMATION pi)
{
    return TerminateProcess(
        pi.hProcess
        , 0
    );
}

std::shared_ptr<BinTree::Node> BinTree::findNode(long long id)
{
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
                lastId = id;
                return;
            }

            currentNode = currentNode->right;
            continue;
        }
        if (id < currentNode->id) {
            if (currentNode->left == nullptr) {
                currentNode->left = std::make_shared<Node>(id, data);
                lastId = id;
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
        root = nullptr;
    }

    if (parentNode->right == currentNode) {
        std::shared_ptr<Node> cr = currentNode->right, cl = currentNode->left, crl = cr->left;
        parentNode->right = cr;

        if (crl == nullptr) {
            cr->left = cl;
        }

        while (crl->left != nullptr) {
            crl = crl->left;
        }

        crl->left = cl;
    }
    else if (parentNode->left == currentNode) {
        std::shared_ptr<Node> cr = currentNode->right, cl = currentNode->left, clr = cl->right;
        parentNode->left = cl;

        if (clr == nullptr) {
            cl->right = cr;
        }

        while (clr->right != nullptr) {
            clr = clr->right;
        }

        clr->right = cr;
    }
}

CalcCenterData BinTree::find(long long id)
{
    return findNode(id)->data;
}

int BinTree::findIdWithSock(SOCKET socket)
{
    if (!root) {
        throw std::invalid_argument("BinTree is empty");
    }
    return __findIdWithSock(root, socket);
}

int BinTree::__findIdWithSock(std::shared_ptr<Node> curNode, SOCKET socket)
{
    if (!curNode) {
        return -1;
    }

    if (curNode->data.socket == socket) {
        return curNode->id;
    }

    int leftId = __findIdWithSock(curNode->left, socket);
    int rightId = __findIdWithSock(curNode->right, socket);

    if (leftId != -1 && rightId != -1) {
        std::cerr << "Warning: multiple enties of socket in BinTree" << std::endl;
    }

    if (leftId != -1) {
        return leftId;
    }
    if (rightId != -1) {
        return rightId;
    }

    throw std::invalid_argument("socket: Not found tree not with given socket");
}

void BinTree::closeProcesses(std::shared_ptr<Node> fromNode)
{
    if (!fromNode) {
        return;
    }
    
    closeProcesses(fromNode->right);
    closeProcesses(fromNode->left);

    closeProcess(*fromNode->data.pi);
    remove(fromNode->id);
}

BinTree::~BinTree()
{
    closeProcesses(root);
}

void BinTree::update(SOCKET socket)
{
    std::shared_ptr<Node> lastNode = findNode(lastId);
    lastNode->data.socket = socket;
}

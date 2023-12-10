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
    lastId = id;
    if (!root) {
        root = std::make_shared<Node>(id, data);
        return;
    }

    std::shared_ptr<Node> currentNode = root;
    while (true) {

        if (id == currentNode->id) {
            lastId = 0;
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

CalcCenterData BinTree::find(long long id)
{
    return findNode(id)->data;
}

long long BinTree::findIdWithSock(SOCKET socket)
{
    if (!root) {
        throw std::invalid_argument("BinTree is empty");
    }
    return __findIdWithSock(root, socket);
}

long long BinTree::__findIdWithSock(std::shared_ptr<Node> curNode, SOCKET socket)
{
    if (!curNode) {
        return -1;
    }

    if (curNode->data.socket == socket) {
        return curNode->id;
    }

    long long leftId = __findIdWithSock(curNode->left, socket);
    long long rightId = __findIdWithSock(curNode->right, socket);

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

    CloseHandle(fromNode->data.pi->hProcess);
    closeProcess(*fromNode->data.pi);
    remove(fromNode->id);
}

BinTree::~BinTree()
{
    closeProcesses(root);
}

void BinTree::update(ObserverData data)
{
    std::shared_ptr<Node> lastNode = findNode(lastId);
    lastNode->data.socket = data.socket;

    data.id = lastNode->id;
    notify_all(data);

    lastId = 0;
}

void BinTree::subscribe(ISockSubscriber* subscriber) {
    subscribers.push_back(subscriber);
}

void BinTree::notify_all(ObserverData data) {
    for (ISockSubscriber* subscriber : subscribers) {
        subscriber->update(data);
    }
}

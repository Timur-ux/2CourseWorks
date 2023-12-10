#ifndef BIN_TREE_H_
#define BIN_TREE_H_

#include <memory>
#include <stdexcept>
#include <Windows.h>
#include <vector>

#include "Observer.hpp"

struct CalcCenterData {
    SOCKET socket;
    PROCESS_INFORMATION *pi;
};

bool closeProcess(PROCESS_INFORMATION pi);

class BinTree : public ISockSubscriber, public ISockObserver {
private:
    struct Node {
        long long id;
        CalcCenterData data;
        std::shared_ptr<Node> right;
        std::shared_ptr<Node> left;

        Node(int _id, CalcCenterData _data) : id(_id), data(_data), right(nullptr), left(nullptr) {}
    };

    long long int lastId = 0;
    std::shared_ptr<Node>root{ nullptr };

    std::shared_ptr<Node> findNode(long long id);

    long long __findIdWithSock(std::shared_ptr<Node> curNode, SOCKET socket);
    void closeProcesses(std::shared_ptr<Node> fromNode);

    std::vector<ISockSubscriber*> subscribers;
public:
    BinTree() = default;
    ~BinTree();

    void add(long long id, CalcCenterData data);
    void remove(long long id);
    CalcCenterData find(long long id);
    long long findIdWithSock(SOCKET socket);
    void update(ObserverData data) override;

    void subscribe(ISockSubscriber* subscriber) override;
    void notify_all(ObserverData data) override;
};

#endif
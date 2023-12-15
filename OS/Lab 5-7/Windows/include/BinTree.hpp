#ifndef BIN_TREE_H_
#define BIN_TREE_H_

#include <memory>
#include <stdexcept>
#include <Windows.h>
#include <vector>

struct CalcCenterData {
    PROCESS_INFORMATION * pi;
};

bool closeProcess(PROCESS_INFORMATION pi);

class BinTree {
private:
    struct Node {
        long long id;
        CalcCenterData data;
        std::shared_ptr<Node> right;
        std::shared_ptr<Node> left;

        Node(int _id, CalcCenterData _data) : id(_id), data(_data), right(nullptr), left(nullptr) {}
    };

    std::shared_ptr<Node>root{ nullptr };

    std::shared_ptr<Node> findNode(long long id);

    void closeAllProcesses(std::shared_ptr<Node> fromNode);
public:
    BinTree() = default;
    ~BinTree();

    void add(long long id, CalcCenterData data);
    void remove(long long id);
    CalcCenterData find(long long id);
};

#endif
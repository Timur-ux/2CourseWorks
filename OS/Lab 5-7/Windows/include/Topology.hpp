#ifndef TOPOLOGY_H_
#define TOPOLOGY_H_
#include <map>
#include <memory>
#include <stdexcept>

namespace Topology {
	template <class TData>
	class BinTree {
		enum class Direction {
			unset,
			left,
			right
		};

		struct Node {
			int id;
			Node* parent = nullptr;
			Node* right = nullptr;
			Node* left = nullptr;

			std::shared_ptr<TData> data;

			Node(std::shared_ptr<TData> _data, Node * _parent = nullptr, int _id = -1) : data(_data), parent(_parent), id(_id) {}
		};

		Node* root;
		long long int freeId = 0;
	public:
		BinTree();
		void add(std::shared_ptr<TData> data, int id = -1);
		void remove(int id);
		std::shared_ptr<TData> get(int id);
	};

	template<class TData>
	inline BinTree<TData>::BinTree()
	{
		root = new Node(std::shared_ptr<TData>{nullptr}, nullptr);
	}

	template<class TData>
	inline void BinTree<TData>::add(std::shared_ptr<TData> data, int id)
	{
		Node* curNode = root, parentNode = root->parent;
		Direction direction = Direction::unset;
		while (curNode != nullptr) {
			parentNode = curNode;
			if (id == curNode->id) {
				throw std::invalid_argument("Already exists");
			}
			else if (id > curNode->id) {
				curNode = curNode->right;
				direction = Direction::right;
			}
			else {
				curNode = curNode->left;
				direction = Direction::left;
			}
		}
		curNode = new Node(data, parentNode, id);
		if (direction == Direction::left) {
			parent->left = curNode;
		}
		else if (direction == Direction::right) {
			parent->right = curNode;
		}
		else {
			throw std::runtime_error("Undefined Tree::add behavior");
		}
	}

	template<class TData>
	inline void BinTree<TData>::remove(int id)
	{
		Node* curNode = root, parentNode = root->parent;
		Direction direction = Direction::unset;
		while (curNode->id != id) {
			parentNode = curNode;
			if (id > curNode->id) {
				curNode = curNode->right;
				direction = Direction::right;
			}
			else {
				curNode = curNode->left;
				direction = Direction::left;
			}
			if (curNode == nullptr) {
				throw std::invalid_argument("id: Not found");
			}
		}
		if (direction == Direction::right) {
			Node* cr = current->right, cl = current->left, crl = cr->left;
			parentNode->right = cr;
			while (crl->left != nullptr) {
				crl = crl->left;
			}
			crl->left = cl;
			delete currentNode;
		}
		else if (direction == Direction::left) {
			Node* cl = current->left, cr = current->right, clr = cl->right;
			parentNode->left = cl;
			while (clr->right != nullptr) {
				clr = clr->right;
			}
			clr->right = cr;
			delete currentNode;
		}
		else {
			throw std::runtime_error("Undefined Tree::remove behavior");
		}
	}
	template<class TData>
	inline std::shared_ptr<TData> BinTree<TData>::get(int id)
	{
		Node* currentNode = root;
		while (currentNode->id != id) {
			if (currentNode->id > id) {
				if (currentNode->left == nullptr) {
					throw std::invalid_argument("id: Not found");
				}
				currentNode = currentNode->left;
			}
			else {
				if (currentNode->right == nullptr) {
					throw std::invalid_argument("id: Not found");
				}
				currentNode = currentNode->right;
			}
		}
		return currentNode->data;
	}
}
#endif // !TOPOLOGY_H_

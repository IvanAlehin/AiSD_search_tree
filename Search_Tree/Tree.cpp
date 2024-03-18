#pragma once

#include <vector>
#include <iostream>
#include <stdexcept> 
#include <random>
#include <exception>
#include <ctime>

using namespace std;	

class Node {
public:
	int value;
	Node* left;
	Node* right;

	Node(int _value) : value(_value), left(nullptr), right(nullptr) {};
};


class MyTree {
private:
	Node* root;

	Node* copy(Node* ptr) {
		if (!ptr) {
			return nullptr;
		}
		auto tmp = new Node(ptr->value);
		tmp->left = copy(ptr->left);
		tmp->right = copy(ptr->right);
		return tmp;
	}

	void delete_tree(Node* ptr) {
		if (!ptr) {
			return;
		}
		delete_tree(ptr->left);
		delete_tree(ptr->right);
		delete ptr;
	}

	int height(Node* ptr) {
		if (!ptr) {
			return 0;
		}
		return std::max(height(ptr->left), height(ptr->right)) + 1;
	}

	int ratio(Node* ptr) {
		if (!ptr) {
			return 0;
		}
		return (height(ptr->left) - height(ptr->right));
	}

	Node* rotate_left(Node* ptr) {//
		auto tmp = ptr->right;
		ptr->right = tmp->left;
		tmp->left = ptr;
		return tmp;
	}

	Node* rotate_right(Node* ptr) {//
		auto tmp = ptr->left;
		ptr->left = tmp->right;
		tmp->right = ptr;
		return tmp;
	}

	Node* balance(Node* ptr) {//

		auto x = ratio(ptr);
		if (x > 1) {
			if (ratio(ptr->left) >= 0) {
				return rotate_right(ptr);
			}
			else {
				ptr->left = rotate_left(ptr->left);
				return rotate_right(ptr);
			}
		}
		if (x < -1) {
			if (ratio(ptr->right) <= 0) {
				return rotate_left(ptr);
			}
			else {
				ptr->right = rotate_right(ptr->right);
				return rotate_left(ptr);
			}
		}
		return ptr;
	}

	Node* min(Node* ptr) {
		while (ptr->left) {
			ptr = ptr->left;
		}
		return ptr;
	}

	Node* max(Node* ptr) {
		while (ptr->right) {
			ptr = ptr->right;
		}
		return ptr;
	}

	Node* erase(Node* ptr, const int value) {
		if (!ptr) {
			return nullptr;
		}
		if (value < ptr->value) {
			ptr->left = erase(ptr->left, value);
		}
		else if (value > ptr->value) {
			ptr->right = erase(ptr->right, value);
		}
		else {
			if (ptr->left == nullptr || ptr->right == nullptr) {
				Node* tmp;
				if (ptr->left != nullptr) {
					tmp = ptr->left;
				}
				else {
					tmp = ptr->right;
				}
				if (tmp == nullptr) {
					tmp = ptr;
					ptr = nullptr;
				}
				else {
					*ptr = *tmp;
				}
				delete tmp;
			}
			else {
				auto tmp = min(ptr->right);
				ptr->value = tmp->value;
				ptr->right = erase(ptr->right, tmp->value);
			}

		}
		return balance(ptr);
	}

	Node* insert(Node* ptr, const int value) {
		if (!ptr) {
			return new Node(value);
		}
		if (value < ptr->value) {
			ptr->left = insert(ptr->left, value);
		}
		else if (value > ptr->value) {
			ptr->right = insert(ptr->right, value);
		}
		else {
			return ptr;
		}
		return balance(ptr);
	}

	void print(Node* ptr) {
		if (ptr) {
			cout << ptr->value << " ";
			this->print(ptr->left);
			this->print(ptr->right);
		}
		else {
			cout << "- ";
		}
	}

	bool contains(Node* ptr, const int value) {
		if (ptr == nullptr) {
			return false;
		}
		if (ptr->value != value) {
			return true;
		}
		if (value > ptr->value) {
			return contains(ptr->right, value);
		}
		else {
			return contains(ptr->right, value);
		}
	}

public:
	MyTree() : root(nullptr) {};
	MyTree(MyTree& other) {
		root = copy(other.root);
	}
	~MyTree() {
		delete_tree(root);
		root = nullptr;

	}

	MyTree& operator=(const MyTree& other) {
		if (this == &other) {
			return *this;
		}

		delete_tree(root);
		root = copy(other.root);
		return *this;
	}
	int min() {
		return min(root)->value;
	}
	int max() {
		return max(root)->value;
	}
	void clear() {
		delete_tree(root);
		root = nullptr;
	}

	bool insert(const int value) {
		if (contains(value)) {
			return false;
		}
		else {
			root = insert(root, value);
			return true;
		}
	}

	void print() {
		print(root);
		cout << endl;
	}
	bool contains(const int value) {
		if (!contains(root, value)) {
			return false;
		}
		return true;
	}
	bool erase(const int value) {
		if (!contains(value)) {
			return false;
		}
		else {
			root = erase(root, value);
			return true;
		}
	}
	
	void unionTree(MyTree& MyTree2, MyTree& result) {
		unionTreeNode(root, MyTree2.root, result);
	}

	void unionTreeNode(Node* node1, Node* node2, MyTree& result) {
		if (node1 != nullptr) {
			unionTreeNode(node1->left, nullptr);
			result.insert(node1->value);
			unionTreeNode(node1->value, nullptr);
		}
		if (node2 != nullptr) {
			unionTreeNode(nullptr, node2->left);
			result.insert(node2->value);
			unionTreeNode(nullptr, node2->right);
		}
	}

	void symmetricDifference(MyTree& MyTree2, MyTree& result) {
		symmetricDifferenceNode(root, MyTree2.root, result);
	}

	void symmetricDifferenceNode(Node* node1, Node* node2, MyTree& result) {
		if (node1 == nullptr && node2 == nullptr) {
			return;
		}

		if (node1 != nullptr && node2 != nullptr) {
			if (node1->value < node2->value) {
				symmetricDifferenceNode(node1->left, node2);
				result.insert(node1->value);
				symmetricDifferenceNode(node1->right, node2);
			}
			else if (node1->value > node2->value) {
				symmetricDifferenceNode(node1, node2->left); 
				result.insert(node2->value);
				symmetricDifferenceNode(node1, node2->right);
			}
			else {
				symmetricDifferenceNode(node1->left, node2->left);
				symmetricDifferenceNode(node1->right, node2->right);
			}
		}
		else if (node1 != nullptr) {
			result.insert(node1->value);
			symmetricDifferenceNode(node1->left, nullptr);
			symmetricDifferenceNode(node1->right, nullptr);
		}
		else if (node2 != nullptr) {
			result.insert(node2->value);
			symmetricDifferenceNode(nullptr, node2->left);
			symmetricDifferenceNode(nullptr, node2->right);
		}
	}

};

size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

template<class T>
MyTree<T> unification(const MyTree<T>& MyTree1, const MyTree<T>& MyTree2)
{
	MyTree <T> NewTree();
	MyTree1.unionTree(MyTree2, NewTree);
	return(NewTree);
}

template<class T>
MyTree<T> symmetricDifference(const MyTree<T>& MyTree1, const MyTree<T>& MyTree2)
{
	MyTree <T> NewTree();
	MyTree1.symmetricDifference(MyTree2, NewTree);
	return(NewTree);
}


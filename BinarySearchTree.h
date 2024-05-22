#pragma once
#include <iostream>
#include <utility>
using namespace std;

template<typename Comparable>
class BinarySearchTree
{
public:
	BinarySearchTree() : root{ nullptr } {}
	BinarySearchTree(const BinarySearchTree& rhs) : root{rhs}
	{
		root = clone(rhs.root);
	}
	BinarySearchTree(const BinarySearchTree&& rhs) : root{ rhs.root }
	{
		rhs.root = nullptr;
	}
	~BinarySearchTree()
	{
		makeEmpty();
	}

	const Comparable& findMin() const
	{
		return (findMin(root))->element;
	}
	const Comparable& findMax() const
	{
		return (findMax(root))->element;
	}
	bool contains(const Comparable& x)  const
	{
		return contains(x, root);
	}
	bool isEmpty() const { return root == nullptr; }
	void printTree(ostream& out = cout) const
	{
		if (!isEmpty())
		{
			printTree(root, out);
		}
	}

	void makeEmpty()
	{
		makeEmpty(root);
	}
	void insert(const Comparable& x)
	{
		insert(x, root);
	}
	void insert(const Comparable&& x)
	{
		insert(move(x), root);
	}
	void remove(const Comparable& x)
	{
		remove(x, root);
	}

	BinarySearchTree& operator=(const BinarySearchTree& rhs)
	{
		if (this != &rhs)
		{
			makeEmpty();
			root = clone(rhs.root);
		}
		return *this;
	}
	BinarySearchTree& operator=(BinarySearchTree&& rhs)
	{
		if (this != &rhs)
		{
			makeEmpty();
			root = rhs.root;	
			rhs.root = nullptr;
		}
		return *this;
	}

private:
	struct BinaryNode
	{
		Comparable element;
		BinaryNode* left;
		BinaryNode* right;

		BinaryNode(const Comparable& theElement, BinaryNode* lt, BinaryNode* rt)
			:element{ theElement }, left{ lt }, right{ rt } {}

		BinaryNode(Comparable&& theElement, BinaryNode* lt, BinaryNode* rt)
			:element{ move(theElement) }, left{ lt }, right{ rt } {}
	};

	BinaryNode* root;

	void insert(const Comparable& x, BinaryNode*& t)
	{
		if (t == nullptr)
		{
			t = new BinaryNode(x,nullptr,nullptr);
		}
		else if (x < t->element)
		{
			return insert(x, t->left);
		}
		else if (x > t->element)
		{
			return insert(x, t->right);
		}
		else {
			;
		}
	}
	void insert(const Comparable&& x, BinaryNode*& t)
	{
		if (t == nullptr)
		{
			t = new BinaryNode(move(x), nullptr, nullptr);
		}
		else if (x < t->element)
		{
			return insert(move(x), t->left);
		}
		else if (x > t->element)
		{
			return insert(move(x), t->right);
		}
		else {
			;
		}
	}
	void remove(const Comparable& x, BinaryNode*& t)
	{
		if (t == nullptr)
			return;
		if (x < t->element)
			remove(x, t->left);
		else if (t->element < x)
			remove(x, t->right);
		else if (t->left != nullptr && t->right != nullptr)
		{
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else
		{
			BinaryNode* oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete oldNode;
		}
	}

	BinaryNode* findMin(BinaryNode* t) const
	{
		if (t == nullptr)
		{
			return nullptr;
		}
		if (t->left == nullptr)
		{
			return t;
		}
		else
		{
			return findMin(t->left);
		}
	}
	BinaryNode* findMax(BinaryNode* t)const
	{
		if (t != nullptr)
		{
			while (t->right != nullptr)
			{
				t = t->right;
			}
		}
		return t;
	}
	bool contains(const Comparable& x, BinaryNode* t) const
	{
		if (t == nullptr)
		{
			return false;
		}
		else if (x < t->element)
		{
			return contains(x, t->left);
		}
		else if (x > t->element)
		{
			return contains(x, t->right);
		}
		else
		{
			return true;
		}

	}
	void makeEmpty(BinaryNode*& t)
	{
		if (t != nullptr)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}
	void printTree(BinaryNode* t, ostream& out)const
	{
		if (t != nullptr)
		{
			printTree(t->left,out);
			out << t->element << " ";
			printTree(t->right, out);
		}
	}

	BinaryNode* clone(BinaryNode* t) const
	{
		if (t == nullptr)
		{
			return nullptr;
		}
		else
			return new BinaryNode(t->element, clone(t->left), clone(t->right));
	}

};


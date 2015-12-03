#include <iostream>
#include <fstream>
using namespace std;

template<typename T>
class AVLTree 
{
public:
	AVLTree(): root(nullptr){}
	~AVLTree()
	{
		makeEmpty(root);
	}

	void insert(const T & e)
	{
		insert(e, root);
	}

	void remove(const T e)
	{
		remove(e, root);
	}

	void print(ostream & os)
	{
		print(root, os);
		os << endl;
	}




private:
	struct AVLNode
	{
		T element;
		int	height;
		AVLNode* left;
		AVLNode* right;

		AVLNode(const T & e, AVLNode* l, AVLNode* r, int h = 0)
		: element(e), left(l), right(r), height(h) {}
		AVLNode(T && e, AVLNode* l, AVLNode* r, int h = 0)
		: element(std::move(e)), left(l), right(r), height(h) {}	
	};

	AVLNode* root;
	static const int IMBALANCE;

	int height(const AVLNode * t) const
	{
		return (t == nullptr) ? -1 : t->height;
	}

	AVLNode* findMin(AVLNode * t)
	{
		while (t-left != nullptr)
			t = t->left;
		return t;
	}
	void insert(const T & e, AVLNode * & t)
	{
		if (t == nullptr)
		{
			t = new AVLNode(e, nullptr, nullptr);
		}
		else if (e < t->element)
			insert(e, t->left);
		else if (e > t->element)
			insert(e, t->right);

		balance(t);
	}

	void remove(const T & e, AVLNode * & t)
	{
		if (t == nullptr)
			return;
		if (e < t->element)
			remove(e, t->left);
		else if (e > t->element)
			remove(e, t->right);
		else if (t->left != nullptr && t->right != nullptr)
		{
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else
		{
			AVLNode* old = t;
			t = (t->left == nullptr) ? t->right : t->left;
			delete old;
		}
		balance(t);
	}

	void print(AVLNode * t, ostream & os)
	{
		if (t != nullptr)
		{
			print(t->left, os);
			os << t->element << ' ';
			print(t->right, os);
		}
	}

	void balance(AVLNode * & t)
	{
		if (t == nullptr)
			return;
		if (height(t->left) - height(t->right) > IMBALANCE)
		{

			if (height(t->left->left) >= height(t->left->right))
				rotateWithLeft(t);
			else
				doubleWithLeft(t);
		}
		else if (height(t->right) - height(t->left) > IMBALANCE)
		{
			//cout << root->element << ' '<< t->element << endl;

			if (height(t->right->right) >= height(t->right->left))
				rotateWithRight(t);
			else
				doubleWithRight(t);
		}

		updateHeight(t);
	}

	void makeEmpty(AVLNode * t)
	{
		if (t == nullptr)
			return;
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}

	void updateHeight(AVLNode * t)
	{
		t->height = std::max(height(t->left), height(t->right)) + 1;
	}
	void rotateWithLeft(AVLNode * & t)
	{
		AVLNode * newRoot = t->left;
		t->left = newRoot->right;
		newRoot->right = t;

		updateHeight(t);
		updateHeight(newRoot);

		t = newRoot;
	}
	void rotateWithRight(AVLNode * & t)
	{
		AVLNode * newRoot = t->right;
		t->right = newRoot->left;
		newRoot->left = t;
		updateHeight(t);
		updateHeight(newRoot);

		t = newRoot;
	}
	void doubleWithLeft(AVLNode * & t)
	{
		rotateWithRight(t->left);
		rotateWithLeft(t);
	}
	void doubleWithRight(AVLNode * & t)
	{
		rotateWithLeft(t->right);
		rotateWithRight(t);
	}

};

template<typename T>
const int AVLTree<T>::IMBALANCE = 1;



int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	AVLTree<int> tree;
	int num;
	while (fin >> num)
		tree.insert(num);
	tree.print(fout);

	fin.close();
	fout.close();
}
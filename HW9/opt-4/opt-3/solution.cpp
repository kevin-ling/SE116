#include <iostream>
#include <fstream>
using namespace std;

template<typename T>
class RBTree
{
public:
	RBTree()
	{
		NIL = new RBNode(0, nullptr, nullptr, nullptr, Black);
		root = NIL;
	}
	~RBTree()
	{}

	void insert(const T & e)
	{
		RBNode* y = NIL;
		RBNode* x = root;
		while (x != NIL)
		{
			y = x;
			if (e < x->element)
				x = x->left;
			else if (e > x->element)
				x = x->right;
			else
				return;
		}
		RBNode* z = new RBNode(e, NIL, NIL, y, Red);
		if (y == NIL)
			root = z;
		else if (e < y->element)
			y->left = z;
		else
			y->right = z;
		insert_fixup(z);
	}

	void remove(const T e)
	{
		RBNode* z = search(root, e);
		RBNode* x;
		if (z == NIL)
			return;
		Color original_color = z->color;
		if (z->left == NIL)
		{
			x = z->right;
			transplant(z, x);
		}
		else if (z->right == NIL)
		{
			x = z->left;
			transplant(z, x);
		}
		else
		{
			RBNode* succ = findMin(z->right);
			original_color = succ->color;
			x = succ->right;
			if (succ->parent == z)
				x->parent = succ;
			else
			{
				transplant(succ, succ->right);
				succ->right = z->right;
				succ->right->parent = succ;
			}
			transplant(z, succ);
			succ->left = z->left;
			succ->left->parent = succ;
			succ->color = z->color;
		}
		if (original_color == Black)
			remove_fixup(x);
		delete z;
	}


	void print(ostream & os)
	{
		print(root, os);
		os << endl;
	}



private:
	enum Color {Red, Black};
	struct RBNode
	{
		T element;
		RBNode* left;
		RBNode* right;
		RBNode* parent;

		Color color;

		RBNode(const T & ele)
		: element(ele), left(nullptr), right(nullptr), parent(nullptr), color(Red)
		{}
		RBNode(const T & ele, RBNode* l, RBNode* r, RBNode* p, Color c = Red)
		: element(ele), left(l), right(r), parent(p), color(c)
		{}
		RBNode(const T && ele, RBNode* l, RBNode* r, RBNode* p, Color c = Red)
		: element(std::move(ele)), left(l), right(r), parent(p), color(c)
		{}		
	};

	RBNode* root;
	RBNode* NIL;

	RBNode* search(RBNode* t,const T & e)
	{
		while( t != NIL && e != t->element)
		{
			if (e < t->element)
				t = t->left;
			else
				t = t->right;
		}
		return t;
	}
	RBNode* findMin(RBNode* t)
	{
		while (t != NIL && t->left != NIL)
			t = t->left;
		return t;
	}
	void leftRotate(RBNode* x)
	{
		RBNode* y = x->right;			//set y
		x->right = y->left;				// left y's left child be x's right child
		if (y->left != NIL)				// if y's left child is not the NIL
			y->left->parent = x;
		y->parent = x->parent;			// set y's parent to x's parent
		if (x->parent == NIL)			// if x is the root
			root = y;
		else if (x == x->parent->left)		// x is the left child
			x->parent->left = y;
		else
			x->parent->right = y;
		y->left = x;					// put x on y's left
		x->parent = y;			
	}

	void rightRotate(RBNode* x)
	{
		RBNode* y = x->left;
		x->left = y->right;
		if (y->right != NIL)
			y->right->parent = x;
		y->parent = x->parent;
		if (x->parent == NIL)
			root = y;
		else if ( x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
		y->right = x;
		x->parent = y;
	}

	void insert_fixup(RBNode* z)
	{
		while (z->parent->color == Red)
		{
			if (z->parent == z->parent->parent->left)
			{
				RBNode* y = z->parent->parent->right;
				if (y->color == Red)
				{
					z->parent->color = Black;
					y->color = Black;
					z->parent->parent->color = Red;
					z = z->parent->parent;
				}
				else
				{
					if (z == z->parent->right)
					{
						z = z->parent;
						leftRotate(z);
					}
					z->parent->color = Black;
					z->parent->parent->color = Red;
					rightRotate(z->parent->parent);
				}
			}
			else
			{
				if (z->parent == z->parent->parent->right)
				{
					RBNode* y = z->parent->parent->left;
					if (y->color == Red)
					{
						z->parent->color = Black;
						y->color = Black;
						z->parent->parent->color = Red;
						z = z->parent->parent;
					}
					else
					{
						if (z == z->parent->left)
						{
							z = z->parent;
							rightRotate(z);
						}
						z->parent->color = Black;
						z->parent->parent->color = Red;
						leftRotate(z->parent->parent);
					}
				}				
			}
		}
		root->color = Black;
	}

	void remove_fixup(RBNode* x)			// x denotes the node with an extra Black
	{
		while (x != root && x->color == Black)
		{
			if (x == x->parent->left)
			{
				RBNode* w = x->parent->right;   // x's sibling
				if (w->color == Red)			// case 1
				{
					w->color = Black;
					x->parent->color = Red;
					leftRotate(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == Black && w->right->color == Black)
				{
					w->color = Red;
					x = x->parent;
				}
				else 
				{
					if (w->right->color == Black)
					{
						w->left->color = Black;
						w->color = Red;
						rightRotate(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					w->right->color = Black;
					x->parent->color = Black;
					leftRotate(x->parent);
					x = root;   // terminate
				}
			}
			else
			{
				RBNode* w = x->parent->left;   // x's sibling
				if (w->color == Red)			// case 1
				{
					w->color = Black;
					x->parent->color = Red;
					rightRotate(x->parent);
					w = x->parent->left;
				}
				if (w->left->color == Black && w->right->color == Black)
				{
					w->color = Red;
					x = x->parent;
				}
				else 
				{
					if (w->left->color == Black)
					{
						w->right->color = Black;
						w->color = Red;
						leftRotate(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					w->left->color = Black;
					x->parent->color = Black;
					rightRotate(x->parent);
					x = root;   // terminate
				}
			}
		}
		x->color = Black;
	}

	void transplant(RBNode* subroot1, RBNode* subroot2)
	{
		if (subroot1->parent == NIL)
			root = subroot2;
		else if (subroot1 == subroot1->parent->left)
			subroot1->parent->left = subroot2;
		else
			subroot1->parent->right = subroot2;
		subroot2->parent = subroot1->parent;
	}

	void print(RBNode * t, ostream & os)
	{
		if (t != NIL)
		{
			print(t->left, os);
			os << t->element << ' ';
			print(t->right, os);
		}
	}

};


int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	RBTree<int> tree;
	int num;
	while (fin >> num)
		tree.insert(num);
	tree.print(fout);
	
	fin.close();
	fout.close();

}
/*
 * Student No.: 5140219295
 * Name: 凌康伟
 */

// headers
#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int val;
    Node *left, *right, *next;
    Node(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

// help functions, do not change them!
Node* readTree(istream& is);
void drawTree(ostream& os, Node* node, int depth=0, string prefix="");
void printResult(ostream& os, Node* root);


class Solution {
public:

    void connect(Node* root){
        if (root == nullptr)
            return;
        //root->next = nullptr;
        Node* host = root;
        Node* curr = new Node(0);
        Node* start = curr;
        Node* first_not_null = nullptr;
        while (host)
        {
            first_not_null = nullptr;
            while (host)
            {
                if (host->left)
                {
                    curr->next = host->left;
                    curr = curr->next;
                    if (first_not_null == nullptr)
                        first_not_null = curr;
                }
                if (host->right)
                {
                    curr->next = host->right;
                    curr = curr->next;
                    if (first_not_null == nullptr)
                        first_not_null = curr;                
                }
                host = host->next;
            }
            curr = start;
            host = first_not_null;
        }
    delete start;
    }

};

int main(int argc, char* argv[]){

    Solution sol;

    Node* tree = readTree(cin);

    // uncomment it to draw the tree 
    drawTree(cout, tree);

    sol.connect(tree);

    printResult(cout, tree);
}
Node* readTree(istream& is) {
	Node* node;
	int val = 0;

	if (!(is >> val)) {
		return nullptr;
	}
	if (val == 0) {
		return nullptr;
	}
	else {
		node = new Node(val);
		node->left = readTree(is);
		node->right = readTree(is);
	}
	return node;
}

void drawTree(ostream& os, Node* node, int depth, string prefix) {
	if (!node)
		return;
	for (int i = 0; i < depth; i++) {
		if (i == depth - 1) {
			os << prefix;
			break;
		}
		os << "  ";
	}
	os << node->val << endl;
	drawTree(os, node->left, depth + 1, "|-");
	drawTree(os, node->right, depth + 1, "`-");
}

void printResult(ostream& os, Node* root) {
	char del = ';';
	Node* start = root;
	while (start != nullptr) {
		Node* curr = start;
		start = nullptr;
		while (curr) {
			os << ' ' << curr->val;
			start = !start ? (curr->left ? curr->left : curr->right) : start;
			curr = curr->next;
		}
		os << del;
	}
	os << endl;
}

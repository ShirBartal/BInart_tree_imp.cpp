#include <iostream>
#include <string>
#include <cassert>
using namespace std;

typedef string ItemType; //string

struct WordNode {
	ItemType m_data;
	WordNode *m_left;
	WordNode *m_right;
	int count;
	WordNode(ItemType data, WordNode* left, WordNode* right, int count) :m_data(data), m_left(left), m_right(right), count(count) {};
	// You may add additional data members and member functions in WordNode
};

class WordTree {

private:
	WordNode * root;
	//helper functions
	void deleteTree(WordNode* node);
	void addNumber(WordNode*&root, ItemType v); //helping function add
	void deep_copy(WordNode* originalRoot, WordNode*& newRoot); //"magic" function" 
	int helpDistinct(WordNode*root)const;															//for the copy constructor
	ostream& helpOperator(WordNode*node, ostream &out)const;
	int totalWordsHelp(WordNode*root, int count)const;
public:
	// default constructor            
	WordTree() : root(nullptr) { };

	// copy constructor
	WordTree(const WordTree& rhs);

	// assignment operator
	const WordTree& operator=(const WordTree& rhs);

	// Inserts v into the WordTree    
	void add(ItemType v);

	//Returns the number of distinct words / nodes   
	int distinctWords() const;

	// Returns the total number of words inserted, including duplicate
	// values    
	int totalWords() const;

	// Prints the Tree
	friend ostream& operator<<(ostream &out, const WordTree& rhs);

	// Destroys all the dynamically allocated memory
	// in the tree.
	~WordTree();

};

WordTree::WordTree(const WordTree& rhs) {
	//copy constructor, deep copy
	deep_copy(rhs.root, root); //&root
}

void WordTree::deep_copy(WordNode* originalRoot, WordNode*& newRoot) {//**{ //problem. we did
	//not connect the nodes of the tree
	/*if (originalRoot == nullptr)
	{
		newRoot = nullptr;
		return;
	}
	*newRoot = new WordNode(originalRoot->m_data, nullptr, nullptr, originalRoot->count);
	deep_copy(originalRoot->m_left, &(*newRoot)->m_left);
	deep_copy(originalRoot->m_right, &(*newRoot)->m_right);*/

	//we didn't have the & before

	if (originalRoot == nullptr)
	{
		newRoot = nullptr;
		return;
	}
	newRoot = new WordNode(originalRoot->m_data, nullptr, nullptr, originalRoot->count); //changed line
	deep_copy(originalRoot->m_left, newRoot->m_left); //&newRoot
	deep_copy(originalRoot->m_right, newRoot->m_right); //&newRoot


}
WordTree::~WordTree() {
	deleteTree(root);
}

void WordTree::deleteTree(WordNode* root) {
	if (root == nullptr) {
		return;
	}
	deleteTree(root->m_left);
	deleteTree(root->m_right);
	delete root;
}

int WordTree::distinctWords() const {
	return helpDistinct(root);

}

int WordTree::helpDistinct(WordNode*root) const {
	if (root == nullptr)
		return 0;
	return 1 + helpDistinct(root->m_left) + helpDistinct(root->m_right);
}

const WordTree& WordTree::operator=(const WordTree& rhs) {
	if (&rhs == this)
		return rhs;
	if (this != nullptr) {
		deleteTree(root);
	}
	deep_copy(rhs.root, root); //&root
	return *this;
}

void WordTree::add(ItemType v) {
	addNumber(root, v);
}

void WordTree::addNumber(WordNode*&root, ItemType v) {
	if (root == nullptr) {
		root = new WordNode(v, nullptr, nullptr, 1);
		return;
	}
	if (root->m_data == v) {
		root->count++;
		return;
	}
	if (v > root->m_data)
		addNumber(root->m_right, v);
	else
		addNumber(root->m_left, v);
}

ostream& operator<<(ostream &out, const WordTree& rhs) {
	return rhs.helpOperator(rhs.root, out);
}
ostream& WordTree::helpOperator(WordNode*root, ostream &out)const {
	if (root == nullptr)
		return out;
	if (root->m_left != nullptr)
		helpOperator(root->m_left, out);
	out << root->m_data << " " << root->count;
	out << endl;
	helpOperator(root->m_right, out);
}

int WordTree::totalWords() const {
	int count1 = 0;
	return totalWordsHelp(root, count1);
}

int WordTree::totalWordsHelp(WordNode*root, int count1) const {
	if (root == nullptr)
		return 0;
	return root->count + totalWordsHelp(root->m_left, root->count) + totalWordsHelp(root->m_right, root->count);
}

//The add function enables a client to insert elements into the WordTree.If an element has already been added, repeated calls to add will not add a new WordNode.Instead the count of the occurrences of that word will increase.
int main() {
	WordTree t;

	t.add("Skyler");
	t.add("Walter");
	t.add("Walter");
	t.add("Walter");

	cout << t;

	assert(t.distinctWords() == 2);
	assert(t.totalWords() == 4);
	WordTree z;

	z.add("Skyler");
	z.add("Walter");
	z.add("Walter");
	z.add("Hank");
	z.add("Gus");
	z.add("Walter");
	z.add("Gus");

	cout << z;

	{
		WordTree tree;
		tree.add("");
		tree.add("");

		assert(tree.distinctWords() == 1);
		assert(tree.totalWords() == 2);
	}

	{

	}
}
//The output operator << enables a client to print elements of a WordTree.The key and the number of occurrences of the key are printed.The output should be sorted according to the key.

/*	WordTree t;*/

//t.add("Skyler");
//t.add("Walter");
//t.add("Walter");
//t.add("Hank");
//t.add("Gus");
//t.add("Walter");
//t.add("Gus");

//cout << t;
//}
/*
Gus 2
Hank 1
Skyler 1
Walter 3
*/

//
// Created by xSnailu on 13.03.2019.
//

#ifndef TREENODE_H
#define TREENODE_H

#include <string>
#include <vector>
using namespace std;

class TreeNode {
public:
	int letter;
	int number;

	TreeNode* nast_elem_listy;
	TreeNode* parent;
	TreeNode* leftchild;
	TreeNode* rightchild;
	TreeNode();
	~TreeNode() {};
	TreeNode(TreeNode* lewy, TreeNode* prawy);

	void setparent(TreeNode* rodzic);
	void setchilds(TreeNode* lewy, TreeNode* prawy);
	void setvalues(int litera, int numer);
	void showvaules();
	friend void swapvaluesofnode(TreeNode* first, TreeNode* second);
	friend void sortarrayoftreenodes(TreeNode* array, int size);
};

TreeNode* addparent(TreeNode* lewy, TreeNode* prawy);

#endif //TREENODE_H

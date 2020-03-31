//
// Created by xSnailu on 13.03.2019.
//
#include "TreeNode.h"
#include <string>
#include <vector>
#include <iostream>


TreeNode::TreeNode()
{
	nast_elem_listy = nullptr;

    letter='\0';
    number=NULL;

    parent=NULL;
    leftchild=NULL;
    rightchild=NULL;
}



TreeNode::TreeNode(TreeNode *lewy, TreeNode *prawy)
{
    this->setchilds(lewy,prawy);
}

void TreeNode::setparent(TreeNode *rodzic)
{
    this->parent=rodzic;
}

void TreeNode::setchilds(TreeNode *lewy, TreeNode *prawy)
{
    this->leftchild = lewy;
    this->rightchild = prawy;
    this->letter = 666;
}

void TreeNode::setvalues(int litera, int numer)
{
    letter=litera;
    number=numer;
}

void TreeNode::showvaules()
{
    cout<<"Letter: "<<letter<<" Number: "<<number<<endl;
}


TreeNode* addparent(TreeNode *lewy, TreeNode *prawy)
{
    TreeNode* nowy = new TreeNode(lewy,prawy);
    lewy->setparent(nowy);
    prawy->setparent(nowy);
 	nowy->number = lewy->number + prawy->number;
    return nowy;
}

void swapvaluesofnode(TreeNode* first, TreeNode* second)
{
 swap(first->number,second->number);
 swap(first->letter,second->letter);
}

void sortarrayoftreenodes(TreeNode * array, int size)
{
    for (int i=0; i<size-1; i++)
        for (int j=0; j<size-1; j++)
            if ((array+j)->number<(array+j+1)->number)
                swapvaluesofnode((array+j), (array+j+1));
}
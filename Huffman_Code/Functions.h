//
// Created by lians on 3/15/19.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>
#include "TreeNode.h"
#include <iostream>
#include <string>

void make_dictionary(TreeNode* begin, string* tab);
void show_tree(TreeNode* begin);
TreeNode* Huffman_Coding(TreeNode* deep_lvl, int count);

struct model
{
	int litera;
	int ilosc;
};

model* make_model_array(const int a);

struct list
{
	int litera;
	int ilosc;
	TreeNode* next;
};

TreeNode* depp_lvl_to_list(TreeNode* deep_lvl, int count);
void showlist(TreeNode* list_begin);
TreeNode* Make_Huffman_Tree(TreeNode* list_begin, int ile_roznych_znakow);
TreeNode* dodawanie_do_listy(TreeNode* list_begin, TreeNode* element_do_dodania, int ile_elem);
#endif //FUNCTIONS_H
#pragma once

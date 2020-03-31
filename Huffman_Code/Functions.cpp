//
// Created by lians on 3/15/19.
//

#include "functions.h"
#include "TreeNode.h"
#include <string>
#include <vector>
#include <iostream>


void make_dictionary(TreeNode* begin, string* tab)
{

	static string kod;
	string bufor_kodu = kod;
	if (begin->letter != 666)
	{
		if (kod.empty())
			kod += '0';
		*(tab + begin->letter) = kod;
	}

	if (begin->leftchild != NULL)
	{
		kod = kod + '0';

		make_dictionary(begin->leftchild, tab);
	}

	kod = bufor_kodu;

	if (begin->rightchild != NULL)
	{
		kod = kod + '1';

		make_dictionary(begin->rightchild, tab);
	}

}
void show_tree(TreeNode* begin)
{

	if (begin->leftchild != NULL)
	{
		begin->leftchild->showvaules();
		show_tree(begin->leftchild);
	}


	if (begin->rightchild != NULL)
	{
		begin->rightchild->showvaules();
		show_tree(begin->rightchild);
	}
}

void file_array_with_zeroes(int* tab, int size)
{
	for (int i = 0; i < size; i++)
		* (tab + i) = 0;
}

void file_array_with_number_of_chars(int* tab, int* tablica, int size)
{

	for (int i = 0; i < size; i++)
		if ((char)tablica[i] == '\0')
			break;
		else
			tab[tablica[i]]++;

}

int count_how_many_different_chars_is_in_array(int* tab, int size)
{
	int count = 0;
	for (int i = 0; i < size; i++)
		if (tab[i] != 0)
		{
			count++;
		}
	return count;
}

int give_string_of_chars_used_in_words(int* tab, int* tab_wyj, int size)
{
	int a = 0;
	for (int i = 0; i < size; i++)
		if (tab[i] != 0)
		{
			if ((char)tab[i] == '\0')
				return 0;
			else
			{
				tab_wyj[a] = tab[i];
				a++;
			}

		}
	return 0;
}

TreeNode* depp_lvl_to_list(TreeNode* deep_lvl, int count)
{
	TreeNode* list_begin = new TreeNode;
	TreeNode* list_buffor = new TreeNode;
	TreeNode* deep_lvl_bufor = (deep_lvl+count-1);
	int ile = count;

	list_buffor = list_begin;
	while (ile  > 0)
	{

		list_buffor->number = deep_lvl_bufor->number;
		list_buffor->letter = deep_lvl_bufor->letter;
		list_buffor->nast_elem_listy = new TreeNode;
		list_buffor = list_buffor->nast_elem_listy;
		ile--;
		deep_lvl_bufor = (deep_lvl + ile - 1);
		
	}
	
	list_buffor = nullptr;
	return list_begin;
}

void showlist(TreeNode* list_begin)
{
	TreeNode* bufor = list_begin;
	while (bufor->nast_elem_listy != nullptr)
	{
		bufor->showvaules();
		bufor = bufor->nast_elem_listy;
	}
}

TreeNode* Make_Huffman_Tree(TreeNode* list_begin, int ile_roznych_znakow)
{
	
	while (ile_roznych_znakow > 2)
	{
		
		TreeNode* nowo_dodany_rodzic = addparent((list_begin), list_begin->nast_elem_listy);
		
		list_begin = ((list_begin->nast_elem_listy));
		list_begin = ((list_begin->nast_elem_listy));
		list_begin->showvaules();
		ile_roznych_znakow--;
		list_begin = dodawanie_do_listy(list_begin, nowo_dodany_rodzic, ile_roznych_znakow);
		
	}

	TreeNode * nowo_dodany_rodzic = addparent((list_begin), list_begin->nast_elem_listy);



	return nowo_dodany_rodzic;

}

TreeNode* dodawanie_do_listy(TreeNode* list_begin, TreeNode* element_do_dodania, int ile_elem)
{

	TreeNode* list_bufor_poprzedni = nullptr;
	TreeNode* bufor = list_begin;

	while (bufor->number < element_do_dodania->number)
	{
		if (bufor->nast_elem_listy == nullptr || bufor->nast_elem_listy == NULL)
		{
			break;
		}
		else
		{
			list_bufor_poprzedni = bufor;
			bufor = bufor->nast_elem_listy;
		}
	}

	element_do_dodania->nast_elem_listy = bufor;
	if (list_bufor_poprzedni != nullptr || list_bufor_poprzedni != NULL)
	{
		list_bufor_poprzedni->nast_elem_listy = element_do_dodania;
	}
	
	if (list_bufor_poprzedni == nullptr || list_bufor_poprzedni == NULL)
		return element_do_dodania;
	else
		return list_begin;


	/*if (ile_elem == 2)
	{
		if (list_begin->number < element_do_dodania->number)
		{
			list_begin->nast_elem_listy = element_do_dodania;
			return list_begin;
		}
		else
		{
			element_do_dodania->nast_elem_listy = list_begin;
			list_begin->nast_elem_listy = nullptr;
			return element_do_dodania;
		}

	}

	int wartosc_elem_do_dodania = element_do_dodania->number;
	while (bufor != nullptr && wartosc_elem_do_dodania > bufor->number)
	{
		list_bufor_poprzedni = bufor;
		bufor = bufor->nast_elem_listy;
		ile_elem--;
	}

	if(list_bufor_poprzedni!=nullptr)
	list_bufor_poprzedni->nast_elem_listy = element_do_dodania;
	element_do_dodania->nast_elem_listy = bufor;
	if (list_bufor_poprzedni == nullptr)
		return element_do_dodania;
	else
		return list_begin;*/
}
TreeNode* Huffman_Coding(TreeNode* deep_lvl, int count)
{
	if (count < 2)
		return deep_lvl;

	int left_left_bufor_index = count - 3;
	int left_bufor_index = count - 2;
	int right_bufor_index = count - 1;
	TreeNode* left_bufor = (deep_lvl + left_bufor_index);
	TreeNode* right_bufor = (deep_lvl + right_bufor_index);
	TreeNode* left_left_bufor = (deep_lvl + left_left_bufor_index);
	TreeNode* bufor;
	int numer_buforowy = right_bufor->number + left_bufor->number;
	right_bufor = addparent(left_bufor, right_bufor);
	left_bufor_index--;
	left_left_bufor_index--;

	left_left_bufor = (deep_lvl + left_left_bufor_index);
	left_bufor = (deep_lvl + left_bufor_index);

	while (left_bufor_index > 0)
	{
		if (left_left_bufor->number + left_bufor->number < right_bufor->number)
		{
			numer_buforowy = left_left_bufor->number + left_bufor->number;
			bufor = addparent(left_left_bufor, left_bufor);
			bufor->number = numer_buforowy;


			cout << endl;
			bufor->showvaules();
			left_bufor->showvaules();
			left_left_bufor->showvaules();

			left_bufor_index--;
			left_left_bufor_index--;
			numer_buforowy = bufor->number + right_bufor->number;
			right_bufor = addparent(bufor, right_bufor);
			
			cout << endl;
			right_bufor->showvaules();
			left_bufor->showvaules();
			left_left_bufor->showvaules();

		 left_bufor = (deep_lvl + left_bufor_index);
			
		 left_left_bufor = (deep_lvl + left_left_bufor_index);

		}
		else
		{
			numer_buforowy = right_bufor->number + left_bufor->number;
			right_bufor = addparent(left_bufor, right_bufor);
			right_bufor->number = numer_buforowy;
			left_bufor_index--;
			left_left_bufor_index--;

			cout << endl;
			right_bufor->showvaules();
			left_bufor->showvaules();
			left_left_bufor->showvaules();

			left_bufor = (deep_lvl + left_bufor_index);

			left_left_bufor = (deep_lvl + left_left_bufor_index);
		}

	}
	return right_bufor;
}

	/*int left_left_bufor_index = count - 3;
	int left_bufor_index = count - 2;
	int right_bufor_index = count - 1;
	TreeNode* left_bufor = (deep_lvl + left_bufor_index);
	TreeNode* right_bufor = (deep_lvl + right_bufor_index);
	TreeNode* left_left_bufor = (deep_lvl + left_left_bufor_index);
	right_bufor->showvaules();
	left_bufor->showvaules();
	left_left_bufor->showvaules();
	int numer_buforowy = right_bufor->number + left_bufor->number;
	right_bufor = addparent(left_bufor, right_bufor);
	right_bufor->number = numer_buforowy;
	left_bufor_index--;
	left_left_bufor_index--;
	left_left_bufor = (deep_lvl + left_left_bufor_index);
	left_bufor = (deep_lvl + left_bufor_index);
	right_bufor->showvaules();
	left_bufor->showvaules();
	left_left_bufor->showvaules();
	bool wyjatek = 0;

	while (left_bufor_index > 0)
	{
		wyjatek = 0;
		
		if (left_left_bufor_index >= 0) {
			if ((right_bufor->number + left_bufor->number) > (left_bufor->number + left_left_bufor->number))
			{
				wyjatek = 1;
				cout << "Dzieje sie ten wyjatek:" << endl;
				int numer_buforowy = left_left_bufor->number + left_bufor->number;
				TreeNode* wezel_pomocniczy = addparent(left_left_bufor, left_bufor);
				wezel_pomocniczy->number = numer_buforowy;
				numer_buforowy = wezel_pomocniczy->number + right_bufor->number;
				right_bufor = addparent(wezel_pomocniczy, right_bufor);
				right_bufor->number = numer_buforowy;

				left_bufor_index = left_bufor_index - 2;
				left_left_bufor_index = left_left_bufor_index - 2;

				left_left_bufor = (deep_lvl + left_left_bufor_index);
				left_bufor = (deep_lvl + left_bufor_index);
				right_bufor->showvaules();
				left_bufor->showvaules();
				left_left_bufor->showvaules();

			}
			else {
				int numer_buforowy = right_bufor->number + left_bufor->number;
				right_bufor = addparent(left_bufor, right_bufor);
				right_bufor->number = numer_buforowy;
				left_bufor_index--;
				left_left_bufor_index--;
				left_left_bufor = (deep_lvl + left_left_bufor_index);
				left_bufor = (deep_lvl + left_bufor_index);
				right_bufor->showvaules();
				left_bufor->showvaules();
				left_left_bufor->showvaules();

			}


		}
		else {
			int numer_buforowy = right_bufor->number + left_bufor->number;
			right_bufor = addparent(left_bufor, right_bufor);
			right_bufor->number = numer_buforowy;
			left_bufor_index--;
			left_left_bufor_index--;
			left_left_bufor = (deep_lvl + left_left_bufor_index);
			left_bufor = (deep_lvl + left_bufor_index);
			right_bufor->showvaules();
			left_bufor->showvaules();
			left_left_bufor->showvaules();

		}
	}
	if (left_bufor->number != 0)
		if (!wyjatek || count > 2) {
			numer_buforowy = right_bufor->number + left_bufor->number;
			right_bufor = addparent(left_bufor, right_bufor);
			right_bufor->number = numer_buforowy;
			left_bufor_index--;
			left_left_bufor_index--;
			left_left_bufor = (deep_lvl + left_left_bufor_index);
			left_bufor = (deep_lvl + left_bufor_index);
			right_bufor->showvaules();
			left_bufor->showvaules();
			left_left_bufor->showvaules();
		}
	cout << endl;
	cout << right_bufor->leftchild->number;
	return right_bufor;
}*/

model* make_model_array(const int a)
{
	model* tablica_modeli = new model[a];
	return tablica_modeli;
}

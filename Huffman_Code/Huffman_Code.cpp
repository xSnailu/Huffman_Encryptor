#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include "TreeNode.h"
#include "functions.h"
#include <math.h>
#include <algorithm>
#include <iostream>
#include <list>

using namespace std;

int main() {
	//jak dekoduje plik jpg to w trzeba wylaczyc dodawanie ostatniego node w functions.cpp
	ifstream plik_odczyt;
	ofstream plik_zapis;
	string nazwa_pliku_wejsciowego = "C:/Users/xsnailu/Desktop/Huffman/Huffman_Code/Shield.png";
	string nazwa_pliku_zapisanego_binarnie = "C:/Users/xsnailu/Desktop/Huffman/Huffman_Code/plik_zapisany_binarnie.txt";
	string nazwa_pliku_zakodowanego = "C:/Users/xsnailu/Desktop/Huffman/Huffman_Code/plik_zakodowany.txt";
	string nazwa_pliku_odkodowanego = "C:/Users/xsnailu/Desktop/Huffman/Huffman_Code/plik_odkodowany.png";
	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str(), ios::binary);

	if (!(plik_odczyt.is_open()))
	{
		cout << "Blad otwierania pliku wejsciowego" << endl;
		return -1;
	}

	int tablica_wystapien[256];
	for (int i = 0; i < 256; i++)
		tablica_wystapien[i] = 0;

	int znak;
	while (!plik_odczyt.eof()) {
		znak = plik_odczyt.get();
		//cout<<znak<<" ";
		if (znak >= 0)
			tablica_wystapien[znak] += 1;
	}

	cout << endl;
	int ile_roznych_znakow = 0;


	for (int i = 0; i < 256; i++)
		if (tablica_wystapien[i] != 0)
			ile_roznych_znakow++;


	model* tablica_modeli = new model[ile_roznych_znakow];
	int n = 0;
	for (int i = 0; i < 256; i++)
		if (tablica_wystapien[i] != 0)
		{
			(tablica_modeli + n)->ilosc = tablica_wystapien[i];
			(tablica_modeli + n)->litera = i;
			n++;
		}


	/////////////////////////////////////////////////////////////////////////
	TreeNode* deep_lvl = new TreeNode[ile_roznych_znakow];
	for (int i = 0; i < ile_roznych_znakow; i++)
		(deep_lvl + i)->setvalues((tablica_modeli + i)->litera, (tablica_modeli + i)->ilosc);

	for (int i = 0; i < ile_roznych_znakow; i++)
		(deep_lvl + i)->showvaules();

	cout << "______________________________________________________" << endl;
	//cout<<"sortowanie:"<<endl;
	sortarrayoftreenodes(deep_lvl, ile_roznych_znakow);
	for (int i = 0; i < ile_roznych_znakow; i++)
		(deep_lvl + i)->showvaules();
	
	cout << "wyswietalnie listy%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	TreeNode* list_begin = depp_lvl_to_list(deep_lvl,ile_roznych_znakow);
	showlist(list_begin);

	cout << "______________________________________________________" << endl;
	//TreeNode* begin = Huffman_Coding(deep_lvl, ile_roznych_znakow);
	TreeNode* begin = Make_Huffman_Tree(list_begin, ile_roznych_znakow);
	cout << "______________________________________________________" << endl;
	string slownik[256];
	show_tree(begin);
	make_dictionary(begin, slownik);
	//cout<<"slownik: "<<endl;
	for (int i = 0; i < 256; i++)
		cout << i << ":" << slownik[i] << endl;
	cout << "______________________________________________________" << endl;

	//zapis pliku binarnego
	plik_odczyt.close();
	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str(), ios::binary);
	if (!(plik_odczyt.is_open()))
	{
		cout << "Blad drugiego otwierania pliku wejsciowego " << endl;
		return -2;
	}

	ofstream plik_zakodowany;
	plik_zakodowany.open(nazwa_pliku_zakodowanego.c_str(), ios::binary);
	if (!(plik_zakodowany.is_open()))
	{
		cout << "Blad otwierania pliku zakodowanego" << endl;
		return -3;
	}

	cout << "______________________________________________________" << endl;
	string ciag_zero_jedynowy;

	while (!plik_odczyt.eof())
	{
		znak = plik_odczyt.get();
		if (znak >= 0)
			ciag_zero_jedynowy += slownik[znak];
	}
	//cout<<ciag_zero_jedynowy;
	cout << endl;
	unsigned long dlugosc_ciagu = ciag_zero_jedynowy.length();
	//cout<<dlugosc_ciagu<<endl;

	for (int i = 0; i < dlugosc_ciagu; i = i + 8)
	{
		int liczba_wyznaczona_przez_ciag = 0;
		for (int k = i; k < i + 8; k++)
		{
			if (k + 1 > dlugosc_ciagu)
				break;
			if (ciag_zero_jedynowy[k] == '1')
				liczba_wyznaczona_przez_ciag += (int)pow(2, 7 - k % 8);
		}
		cout << liczba_wyznaczona_przez_ciag << " ";
		//cout<<liczba_wyznaczona_przez_ciag<<" ";
		plik_zakodowany << (char)liczba_wyznaczona_przez_ciag;
	}
	int ilosc_zer_na_koncu = 8 - dlugosc_ciagu % 8;
	plik_zakodowany.close();
	plik_odczyt.close();
	cout << endl;
	//dekodowanie
	ifstream odczyt_pliku_zakodowanego;
	odczyt_pliku_zakodowanego.open(nazwa_pliku_zakodowanego.c_str(), ios::binary);
	if (!(odczyt_pliku_zakodowanego.is_open()))
	{
		cout << "Blad otwierania pliku zakodowanego po raz drugi" << endl;
		return -4;
	}
	cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	string kod;
	int numer;
	string bufor_konwertujacy;
	string konwert = "00000000";
	string zdekodowany;
	while (!odczyt_pliku_zakodowanego.eof())
	{
		numer = odczyt_pliku_zakodowanego.get();
		// cout<<numer<<" ";
		while (numer > 0)
		{
			if (numer % 2 == 1)
				bufor_konwertujacy += '1';
			else
				bufor_konwertujacy += '0';
			numer = numer / 2;
		}
		for (int j = 0; j < bufor_konwertujacy.length(); j++)
		{
			konwert[8 - bufor_konwertujacy.length() + j] = bufor_konwertujacy[bufor_konwertujacy.length() - 1 - j];
		}
		zdekodowany = zdekodowany + konwert;
		bufor_konwertujacy = "\0";
		konwert = "00000000";



	}

	zdekodowany.erase(zdekodowany.end() - ilosc_zer_na_koncu*2, zdekodowany.end());
	cout << zdekodowany << endl;
	odczyt_pliku_zakodowanego.close();
	//cout<<zdekodowany;
	//for (int j = 0; j < ilosc_zer_na_koncu; j++)
		//zdekodowany[zdekodowany.length() - 1 - j] = '#';

	//cout<<zdekodowany;
	cout << endl;

	cout << "____________________________________________" << endl;

	ofstream plik_odkodowany;
	plik_odkodowany.open(nazwa_pliku_odkodowanego.c_str(), ios::binary);
	if (!(plik_odkodowany.is_open()))
	{
		cout << "Blad otwierania pliku z odkodowanymi danymi" << endl;
		return -5;
	}

	//dekoduje sie plik
	string kodek;
	char znaczek0;
	long int a = zdekodowany.length();
	for (int i = 0; i < zdekodowany.length(); i++) {
		znaczek0 = zdekodowany[i];
		kodek = kodek + znaczek0;
		for (int k = 0; k < 256; k++) {
			if (slownik[k] == kodek) {
				cout << (char)k << " ";
				plik_odkodowany << (unsigned char)k;
				kodek = "\0";
				break;
			}
		}


	}

	//wyswietlam wszystkie elementy:
	cout << "Znaki ktore wystepuja i ich liczby: " << endl;
	for (int i = 0; i < 256; i++)
		if (tablica_wystapien[i] != 0)
		{
			cout << "Znak o numerze: " << i << " wystepuje: " << tablica_wystapien[i] << " razy." << endl;

		}
	cout << "____________________________________________" << endl;
	//slownik
	cout << "Slowa kodowe: " << endl;
	for (int k = 0; k < 256; k++)
		if (!slownik[k].empty())
		{
			if (!slownik[k].empty())
				cout << k << " " << slownik[k] << endl;

		}






	return 0;
}
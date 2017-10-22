#define _CRT_SECURE_NO_WARNINGS

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>
#include <cstring>
#include <fstream>
#include <conio.h>
#include <iomanip>

using namespace std;

class Hash_Table {
	struct Node
	{
		char *x;
		int count;
		Node *next;
	};

private:
	int table_size;
	Node* T;


public:

	Hash_Table(int size) {
		table_size = size;
		Initialization();
	}
	int count_collizion = 0;


	void Initialization() {

		T = new Node[table_size];

		for (int i = 0; i<table_size; i++) {

			T[i].count = 0;
			T[i].x = new char[20];
			T[i].x = "#";
			T[i].next = NULL;

		}
	}

	void print() {
		for (int i = 0; i < table_size; i++) {
			if (T[i].count > 0) {
				cout << T[i].x << " ";

				Node *tmp = T[i].next;
				while (tmp) {
					cout << tmp->x << " ";
					tmp = tmp->next;
				}
				cout << endl;
			}
		}
		cout <<"(количество коллизий: "<<count_collizion<<")"<<endl<<endl;
		

	}


	void addelem(char dat[], int menu) {

		int i = Hash(dat, menu);

		//cout << dat<<" "<<i<<" ";
		if ((strcmp(T[i].x, dat) == 0) || T[i].count == 0)
		{
			T[i].count++;
			T[i].x = dat;
		}
		else
		{
			if (T[i].next == NULL)
			{
				T[i].next = new Node;
				T[i].next->x = dat;
				T[i].next->count = 1;
				T[i].next->next = NULL;
				count_collizion++;
			}
			else
			{
				Node *tmp = T[i].next;
				while ((strcmp(tmp->x, dat) != 0) && tmp->next)
				{
					tmp = tmp->next;
				}
				if (strcmp(tmp->x, dat) != 0)
				{
					count_collizion++;
					tmp->next = new Node;
					tmp = tmp->next;
					tmp->next = NULL;
					tmp->count = 1;
					tmp->x = dat;
				}
				else tmp->count++;
			}
		}

	}

	int hash1(char key[]){

		int h = 0;
		for (int i = 0; key[i] != NULL; i++)
			h += key[i];

		return h % table_size;
	}

	int hash2(char key[]){

		int h = 0;
		for (int i = 0; key[i] != NULL; i++)
			h = 31 * h + (unsigned char)key[i];

		return h % table_size;
	}

	int hash3(char key[]){

		int h = 0;
		for (int i = 0; key[i] != NULL; i++)
			h = 13 * h + (unsigned char)key[i];

		return h % table_size;
	}

	int Hash( char dat[], int menu )
	{
		int i;
		switch (menu)
		{
		case 1: {i = hash1(dat); break; }
		case 2: {i = hash2(dat); break; }
		case 3: {i = hash3(dat); break; }
		default:break;
		}
		return i;
	}	

};
int main()
{
	setlocale(LC_ALL, "Russian");

	int size = 11;
	Hash_Table A(size);
	Hash_Table B(size);
	Hash_Table C(size);

	char str[500] = "";
	char str1[50];
	ifstream fin("text.txt");
	
	while (!fin.eof())
	{
		fin.getline(str1, 50);
		strcat(str, " ");
		strcat(str, str1); 
	}
	char * pch = strtok(str, " ,.-:;!?()/\\n");
	while (pch != NULL)
	{
		pch[0] = (char)tolower(pch[0]);
		A.addelem(pch,1);
		B.addelem(pch,2);
		C.addelem(pch,3);
		pch = strtok(NULL, " ,.-:;!?()/\n");
	}
	fin.close();

	int count1 = A.count_collizion, count2=B.count_collizion, count3=C.count_collizion;

	cout <<"Хэш-таблица 1: "<< endl;
		A.print();
	
	cout <<"Хэш-таблица 2: " << endl;
		B.print();

	cout << "Хэш-таблица 3: " << endl;
		C.print();
	
		cout << endl << "Среднее количество коллизий:" << ((count1 + count2 + count3) / 3)<<endl;
	_getch();
	system("pause");
	return 0;
}

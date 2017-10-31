#include <iostream>
#include <fstream>

using namespace std;

int** Init_Graph(int N) {
	int **a = new int*[N];
	for (int i = 0; i < N; i++)
		a[i] = new int[N];
	return a;
}

void Show(int **a, int N) {

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << a[i][j] << "  ";
		cout << endl;
	}
}

int* Init_arrVertexes(int N, int Vertex) {

	int *accessVertexes = new int[N];

	for (int i = 0; i < N; i++)
		accessVertexes[i] = 0;
	accessVertexes[Vertex - 1] = 1;

	return accessVertexes;
}

 void AccessibleVertex(int **a, int *accessVertexes, int vertex, int N) {
	 for (int i = 0; i < N; i++)
		 if (a[vertex][i] == 1 && accessVertexes[i] == 0) {
			accessVertexes[i] = 1;
			 AccessibleVertex(a,accessVertexes, i,N);
		 }
 }

 int** RemovalVertexes(int** a,int *accessVertexes,int &N) {

	 int newCount = 0;

	 for (int i = 0; i < N; i++)
		 if (accessVertexes[i] == 1)
			 newCount++;

	 int **newGraph = new int*[newCount];
	 for (int i = 0; i < newCount; i++)
		 newGraph[i] = new int[newCount];

	 int m = 0;
	 for (int i = 0; i < N; i++) {
		 if (accessVertexes[i] != 0) {
			 int n = 0;
			 for (int j = 0; j < N; j++)
				 if (accessVertexes[j] != 0) {
					 newGraph[m][n] = a[i][j];
					 n++;
				 }
			 m++;
		 }
	 }
	 N = newCount;
	 return newGraph;
 }


void main() {
	setlocale(LC_ALL, "RUSSIAN");

	ifstream fin("input3.txt");
	if (fin) {
		int N;
		fin >> N;

		int**graph = Init_Graph(N);

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				fin >> graph[i][j];

		cout << "Матрица смежности:" << endl;
		Show(graph, N);
		int Vertex;
		cout << "Введите номер одной из вершин, недостижимые из которой будут удалены: ";
		cin >> Vertex;

		int *arrVertexes = Init_arrVertexes(N, Vertex);
		AccessibleVertex(graph, arrVertexes, Vertex - 1, N);
		
		int k = 0;
		for (int i = 0; i < N; i++) 
			if (arrVertexes[i] == 0) 
				k++;
			
		
		if (k == 0) 
			cout<<endl<<"Недостижимых вершин нет."<<endl;
		else {
			cout << endl << "Номер вершин, недостижимых из заданной: ";
			for (int i = 0; i < N; i++) {
				if (arrVertexes[i] == 0) {
					cout << i + 1 << " ";
				}
			}

			cout << endl;
			cout << endl;
			cout << "Граф, кторый состоит только из достижимых веришин: " << endl;
			graph = RemovalVertexes(graph, arrVertexes, N);
			Show(graph, N);
		}
		fin.close();
	}
	else
		cout << "Ошибка при открытии файла" << endl;
	system("PAUSE");
}

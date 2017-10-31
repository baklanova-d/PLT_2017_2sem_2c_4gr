#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

int** Init_Graph(int N) {
	int **a = new int*[N];
	for (int i = 0; i < N; i++)
		a[i] = new int[N];
	return a;
}


int* Init_arrVertexes(int N)
{
	int *arrVertexes = new int[N];
	for (int i = 0; i < N; i++)
		arrVertexes[i] = 0;
	return arrVertexes;
}

void Show(int **a, int N) {

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << a[i][j] << "  ";
		cout << endl;
	}
}
bool BFS(queue<int> Queue, int *arrVertex, int **graph, int N, int vertex, int k)
{
	int node = vertex;

	if (arrVertex[node] < 2)
	{   
		Queue.pop();
		arrVertex[node] = 2;

		for (int j = 0; j < N; j++)
		{
			if ((graph[node][j] == 1) && (arrVertex[j] < 2))
			{
				Queue.push(j);
				k++;
			}
		}		
	}

	else
	{
		cout << "НЕТ" << endl << endl;
		return 0;
	}

	if (!Queue.empty())
		BFS(Queue, arrVertex, graph, N, Queue.front(), k);

	else {

		if (k == N - 1)
		{
			cout << "ДА" << endl << endl;
			return 1;
		}
		else
		{
			cout << "НЕТ" << endl << endl;
			return 0;
		}
	}

}

void main()
{
	setlocale(LC_ALL, "RUSSIAN");
	queue<int> Queue;
	bool result;

	ifstream fin("input4.txt");
	if (fin) {
		int N;
		fin >> N;

		int**graph = Init_Graph(N);


		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				fin >> graph[i][j];

		int* arrVertex = Init_arrVertexes(N);
		Queue.push(0);

		cout << "Количество вершин в графе = " << N << endl;
		cout << endl << "Матрица смежности вершин:" << endl;
		Show(graph, N);

		cout << endl << "Является ли граф деревом?  ";
		result = BFS(Queue, arrVertex, graph, N, 0, 0);
	
		fin.close();		
	}
	else
		cout << "Ошибка при открытии файла" << endl;
	system("PAUSE");
}

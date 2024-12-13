#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>

using namespace std;

int** create_adjacency_matrix(int v);
int cout_matrix(int** G, int v);

void BFSD(int** G, int v, int start, int* distance);

void main()
{
	int size = 0;
	cout << "input first graph size: ";
	cin >> size;
	cout << endl;

	int** M = create_adjacency_matrix(size);
	cout_matrix(M, size);

	int start;
	cout << "Enter the start vertex for BFS: ";
	cin >> start;

	int* distance = new int[size];
	for (int i = 0; i < size; i++)
	{
		distance[i] = -1;
	}

	BFSD(M, size, start, distance);

	cout << endl << endl << "  Depth of vertexes: " << endl;
	cout << "vertex		distance" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "  " << i << "		  " << distance[i] << endl;
	}

	delete[] distance;
	for (int i = 0; i < size; i++)
	{
		delete[] M[i];
	}
	delete[] M;

	return;
}

int** create_adjacency_matrix(int v)
{
	srand(time(NULL));
	int** G = new int* [v];

	for (int i = 0; i < v; i++)
	{
		G[i] = new int[v];
	}

	for (int i = 0; i < v; i++)
	{
		for (int j = 0; j < v; j++)
		{
			if (i == j)
			{
				G[i][j] = 0;
			}
			else if (j < i)
			{
				G[i][j] = G[j][i];
			}
			else
			{
				G[i][j] = (rand() % 10 + 1);
			}
		}
	}

	return G;
}

int cout_matrix(int** g, int v)
{
	cout << "	";
	for (int i = 0; i < v; i++)
	{
		cout << i << "	";
	}
	cout << endl << endl;
	for (int i = 0; i < v; i++)
	{
		cout << i << "	";
		for (int j = 0; j < v; j++)
		{
			cout << g[i][j] << "	";
		}
		cout << endl;
	}
	return 1;
}

void BFSD(int** G, int v, int start, int* distance)
{
	queue<int> q;
	q.push(start);
	distance[start] = 0;

	while (!q.empty())
	{
		int current = q.front();
		q.pop();
		cout << "Visiting vertex " << current << endl;

		for (int i = 0; i < v; i++)
		{
			if (G[current][i] > 0 && distance[i] == -1)
			{
				q.push(i);
				distance[i] = distance[current] + G[current][i];
			}
		}
	}
}
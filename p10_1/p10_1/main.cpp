#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int** create_adjacency_matrix(int v);
int cout_matrix(int** G, int v);

void BFSD(int** g, int v, int size, bool* vis, int* dis);

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
	bool* visited = new bool[size];
	for (int i = 0; i < size; i++)
	{
		visited[i] = 0;
		distance[i] = 0;
	}

	BFSD(M, start, size, visited, distance);

	cout << endl << endl << "  Depth of vertexes: " << endl;
	cout << "vertex		distance" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "  " << i << "		  " << distance[i] << endl;
	}
	
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
				G[i][j] = (rand() % 10) + 1;
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

void BFSD(int** g, int v, int size, bool* vis, int* dis)
{
	queue<int> q;
	q.push(v);
	vis[v] = 1;
	dis[v] = 0;

	while (!q.empty())
	{
		v = q.front();
		q.pop();
		cout << v << " -> ";
		for (int i = 0; i < size; i++)
		{
			if (g[v][i] >= 1 && !vis[i])
			{
				dis[i] = dis[v] + g[v][i];
				vis[i] = 1;
				q.push(i);
			}
		}
	}
}
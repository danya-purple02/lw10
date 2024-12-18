#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int** create_adjacency_matrix(int v, int type);
int cout_matrix(int** G, int v);

void BFSD(int** g, int v, int size, int* dis);
int min_element(int* vec, int size);
int max_element(int* vec, int size);

int main(int argc, char* argv[])
{
	int size = 0, type_of_matrix = 0;
	if (argc < 0) 
	{
		cout << "Parameters error. Input parameters." << endl << endl;
		size = 0, type_of_matrix = 0;
		cout << "Input first graph size: "; cin >> size; cout << endl;
		cout << "Choose type of graph: " << endl << " 0 - Unweighted Undirected | 1 - Unweighted Directed " << endl << " 2 - Weighted Undirected | 3 - Weighted Directed " << endl;
		cin >> type_of_matrix;
		if (!(0 <= type_of_matrix <= 3))
		{
			cout << endl << "Error. Must type 0 to 3." << endl;
			return 0;
		}
	}
	else 
	{
		size = stoi(argv[1]);
		type_of_matrix = stoi(argv[2]);
	}
	
	int** M = create_adjacency_matrix(size, type_of_matrix);
	cout_matrix(M, size);

	int** distance = new int*[size];
	int* eccentricities = new int[size];
	for (int i = 0; i < size; i++)
	{
		eccentricities[i] = 0;
		distance[i] = new int[size];
		for (int j = 0; j < size; j++) 
		{
			distance[i][j] = INT_MAX;
		}
	}
	
	cout << endl << "distance: " << endl;
	cout << "	";
	for (int i = 0; i < size; i++) 
	{
		cout << i << "	";
	}
	cout << endl << endl;

	for (int i = 0; i < size; i++) 
	{
		BFSD(M, i, size, distance[i]);
		cout << i << "	";
		for (int j = 0; j < size; j++) 
		{
			cout << distance[i][j] << "	";
		}
		cout << endl;
		eccentricities[i] = max_element(distance[i], size);
	}

	int diameter = max_element(eccentricities, size), radius = min_element(eccentricities, size);

	cout << endl << "eccentricities: " << endl << "	";
	for (int i = 0; i < size; i++) 
	{
		cout << eccentricities[i] << "	";
	}
	cout << endl << "diameter = " << diameter << endl << "radius = " << radius << endl << endl;

	for (int i = 0; i < size; i++) {
		if (eccentricities[i] == diameter)
		{
			cout << i << " vertex is a peripheral vertex." << endl;
		}
		if (eccentricities[i] == radius)
		{
			cout << i << " vertex is a central vertex." << endl;
		}
	}

	for (int i = 0; i < size; i++)
	{
		delete[] M[i];
		delete[] distance[i];
	}
	delete[] M;
	delete[] distance;

	return 1;
}

int** create_adjacency_matrix(int v, int type)
{
	srand(time(NULL));
	int** G = new int* [v];

	for (int i = 0; i < v; i++)
	{
		G[i] = new int[v];
	}

	switch (type) 
	{
		case 0: // unweighted undirected
		{
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
						G[i][j] = rand() % 2;
					}
				}
			}
			break;
		}
		case 1: // unweighted directed
		{
			for (int i = 0; i < v; i++)
			{
				for (int j = 0; j < v; j++)
				{
					G[i][j] = (i == j) ? rand() % 2 : 0;
				}
			}
			break;
		}
		case 2: // weighted undirected
		{
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
			break;
		}
		case 3: // weighted directed
		{
			for (int i = 0; i < v; i++)
			{
				for (int j = 0; j < v; j++)
				{
					G[i][j] = (i == j) ? (rand() % 10) + 1 : 0;
				}
			}
			break;
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

void BFSD(int** g, int v, int size, int* dis)
{
	queue<int> q;
	q.push(v);
	dis[v] = 0;

	while (!q.empty())
	{
		v = q.front();
		q.pop();

		for (int i = 0; i < size; i++)
		{
			if (g[v][i] > 0 && dis[i] > dis[v] + g[v][i]) 
			{
				dis[i] = dis[v] + g[v][i];
				q.push(i);
			}
		}
	}
}

int min_element(int* vec, int size)
{
	int min_element = INT_MAX;
	for (int i = 0; i < size; i++)
	{
		if (min_element > vec[i])
		{
			min_element = vec[i];
		}
	}
	return min_element;
}

int max_element(int* vec, int size) 
{
	int max_element = INT_MIN;
	for (int i = 0; i < size; i++) 
	{
		if ((max_element < vec[i]) && (vec[i] != INT_MAX))
		{
			max_element = vec[i];
		}
	}
	return max_element;
}
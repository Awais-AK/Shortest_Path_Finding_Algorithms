#include <bits/stdc++.h>
using namespace std;
#define MAX 10000

// function to print the path from specified source to destination
void printpath(int source, int destination, int Next[][500])
{
    // If path doesn't exist from source to destination
    if (Next[source][destination] == -1)
    {
        cout << "PATH DOESN'T EXIST\n";
        return;
    }

    // When path exists from source to destination
    cout << "\nPATH :\t " << source << " (SOURCE) ";
    while (source != destination)
    {
        source = Next[source][destination];
        cout << "--> " << source << " ";
    }
    cout << "(DESTINATION)\n";

    return;
}

// funtion to print the matrix with size n * n
void validatematrix(int matrix[][500], int n)
{

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            if (i != j && matrix[i][j] == 0)
            {
                matrix[i][j] = MAX;
            }
    }
}

// funtion to print the matrix with size n * n
void printmatrix(int matrix[][500], int n)
{
    cout << "Matrix:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << matrix[i][j] << '\t';
        cout << "\n\n";
    }
}

// This is the Floyd-Warshall Function which calculates the distance of shortest path from every source node to every vertex of the graph
// Prints the path and path length(if exists) from source to destination
void floyd_warshall(int distance[][500], int V, int E, int source, int destination)
{

    int next[500][500]; // to get the shortest path from source to the destination

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
        {
            next[i][j] = j;
            if (distance[i][j] == MAX)
                next[i][j] = -1; // there is no edge between i and j
        }

    for (int i = 0; i < V; i++)         // Intermediate vertex
        for (int u = 0; u < V; u++)     // Start vertex
            for (int v = 0; v < V; v++) // End vertex
            {
                // Pass if edge doesn't exist
                if (distance[u][i] == MAX || distance[i][v] == MAX)
                    continue;

                // Update if shorter path exists via "i"
                if (distance[u][i] + distance[i][v] < distance[u][v])
                {
                    distance[u][v] = distance[u][i] + distance[i][v];
                    next[u][v] = next[u][i];
                }
            }
    // Shortest path found (if negative cost cycle doesn't exist)
    // Checking for negative cycle: if the distances change after one more iteration, then there is a negative cost cycle.
    for (int i = 0; i < V; i++)         // Intermediate vertex
        for (int u = 0; u < V; u++)     // Start vertex
            for (int v = 0; v < V; v++) // End vertex
            {
                // Pass if edge doesn't exist
                if (distance[u][i] == MAX || distance[i][v] == MAX)
                    continue;

                // Update if shorter path exists via "i"
                if (distance[u][i] + distance[i][v] < distance[u][v])
                {
                    cout << "\nThis graph contains negative edge cycle\nSo, the shortest path is not defined\n";
                    return;
                }
            }

    printpath(source, destination, next);

    if (distance[source][destination] != MAX)
        cout << "PATH LENGTH: " << distance[source][destination] << "\n";
}

void readfile(int argc, char *argv[], int &V, int &E, int distance[][500])
{
    if (argc <= 1)
    {
        cout << "No file name entered. Exiting...";
        return;
    }
    ifstream infile(argv[1]); // open the file
    // initialization
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            distance[i][j] = MAX;
            if (i == j)
                distance[i][j] = 0; // minimum path to start and end on same vertex is 0
        }
    }
    if (infile.is_open() && infile.good())
    {
        string line = "";
        int i = 0;
        while (getline(infile, line))
        {
            if (i == 0)
            {
                V = stoi(line);
            }
            else if (i == 1)
            {
                E = stoi(line);
            }
            else
            {
                int a, b, cost;
                a = line[0] - 48;
                b = line[2] - 48;
                cost = line[4] - 48;
                distance[a][b] = cost;
            }
            i++;
            cout << line << '\n';
        }
        validatematrix(distance, V);
    }
    else
    {
        cout << "Failed to open file..";
    }
}

int main(int argc, char *argv[])
{
    int source, destination;
    int distance[500][500];

    int V, E;
    cout << "The sample input is as follows: \n";
    readfile(argc, argv, V, E, distance);

    cout << "Enter the source and the destination " << endl;
    cout << "(Vertex numbers should be less than " << V << ")\n";
    cin >> source >> destination;
    // printmatrix(distance, V);

    floyd_warshall(distance, V, E, source, destination);

    return 0;
}
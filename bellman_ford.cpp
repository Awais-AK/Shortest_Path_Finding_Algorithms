// Bellman-Ford Algorithm for Shortest Path between given 2 nodes
#include <bits/stdc++.h>
using namespace std;
#define MAX 10000

typedef struct adjlist_node // Structure to store node values in Adjacency List
{
    int destination, cost;
    struct adjlist_node *next;
} adjlist_node;

typedef struct graph // Representation of Graph
{
    int num_vertices;
    struct adjlist_node **arr; // Nodes are stored in an Array of "size" = Number of Vertices
} graph;

adjlist_node *new_listnode(int destination, int cost) // Function To create new Node
{
    adjlist_node *new_node = (adjlist_node *)malloc(sizeof(adjlist_node));

    new_node->destination = destination;
    new_node->cost = cost;
    new_node->next = NULL;
    return new_node;
}

graph *create_graph(int num_vertices) // Function to create an empty Graph consisting of "num_vertices" Vertices
{
    graph *G = (graph *)malloc(sizeof(graph));
    G->num_vertices = num_vertices;
    G->arr = (adjlist_node **)malloc(num_vertices * sizeof(adjlist_node)); // Dynamically allocating space for array of size num_vertices

    for (int i = 0; i < num_vertices; i++)
        G->arr[i] = NULL; // Initializing with NULL
    return G;
}

void add_newedge(graph *G, int src, int dest, int cost) // Function to add a new directed edge in the graph
{
    adjlist_node *new_node = new_listnode(dest, cost);
    new_node->next = G->arr[src];
    G->arr[src] = new_node;
}

// funtion to print the arrays dist[] and prev[] containing information about shortest distance from source and previous vertex in the path respectively
void printArr(int dist[], int n, int prev[])
{
    cout << "Vertex   Distance from Source   Previous Node\n";
    for (int i = 0; i < n; i++)
        cout << " " << i << " \t\t " << dist[i] << " \t\t    " << prev[i] << "\n";
}

void printpath(int prev[], int source, int destination, int num_vertices) // Function to print the path from source to destination
{
    int i = 0, temp[num_vertices];

    temp[i] = destination;

    // BACKTRACKING USING PREV NODES
    while (temp[i] != source)
    {
        if (prev[temp[i]] == -1)
        {
            cout << "PATH DOESN'T EXIST\n";
            return;
        }
        temp[i + 1] = prev[temp[i]];
        i++;
    }

    // PRINTING IN STRAIGHT ORDER FROM SOURCE TO DESTINATION
    cout << temp[i--] << " (SOURCE) ";
    for (; i >= 0; i--)
        cout << "--> " << temp[i] << " ";
    cout << "(DESTINATION)\n";
}

// This is the BellmanFord Function which calculates the distance of shortest path from source node to every vertex of the graph
void bellman_ford(graph *G, int source, int destination)
{
    int num_vertices = G->num_vertices;

    // Distance array to store the shortest path length
    // Prev Array to store the previous node to the destination node
    int distance[num_vertices], prev[num_vertices];

    // Initializing the vertex distances to MAX
    for (int i = 0; i < num_vertices; i++)
    {
        distance[i] = MAX;
        prev[i] = -1;
    }

    // Distance of source from source is 0 so that it is picked first as a greedy step
    distance[source] = 0;

    // The shortest path of graph that contain V vertices, contain atmost "V-1" edges
    //  Doing "V-1" relaxations
    for (int i = 0; i < num_vertices - 1; i++)
    {
        // To check whether changes are occurring or not in a particular iteration
        // If there is no change, program can be terminated sooner (as in Bubble Sort)
        int change = 0;

        //"u" : start node
        for (int u = 0; u < num_vertices; u++)
        {
            adjlist_node *temp = G->arr[u];

            // Traversing through all the vertices and updating their distance
            while (temp)
            {
                int v = temp->destination;
                int cost = temp->cost;

                if (distance[v] > cost + distance[u])
                {
                    distance[v] = distance[u] + temp->cost;
                    prev[v] = u; // saving prev node of v as u
                    change = 1;
                }
                temp = temp->next;
            }
        }

        // Terminate the loop earlier if the shortest paths are found before (num_vertices-1)th iteration
        // Also, negative cost cycle cannot exist in this case
        if (change == 0)
            goto print;
    }

    // Shortest path found (if negative cost cycle doesn't exist)
    // Checking for negative cycle: if the distances change after one more iteration, then there is a negative cost cycle.
    for (int u = 0; u < num_vertices; u++)
    {
        adjlist_node *temp = G->arr[u];

        // Traversing through all the vertices and updating their distance
        while (temp)
        {
            int v = temp->destination;
            int cost = temp->cost;

            if (distance[v] > cost + distance[u])
            {
                cout << "\nThis graph contains negative edge cycle\nSo, the shortest path is not defined\n";
                return;
            }
            temp = temp->next;
        }
    }

print:

    // printArr(distance, num_vertices, prev);

    cout << "\nPATH:\t";
    printpath(prev, source, destination, num_vertices);
    if (distance[destination] != MAX)
        cout << "PATH LENGTH: " << distance[destination] << "\n";

    return;
}

// Function to read the file provided and generate a graph using that
graph *readfile_to_graph(int V, int E, int distance[][3])
{

    graph *G = create_graph(V);

    for (int i = 0; i < E; i++)
    {
        int source, destination, cost;
        source = distance[i][0];
        destination = distance[i][1];
        cost = distance[i][2];
        add_newedge(G, source, destination, cost);
    }
    return G;
}

void readfile(int argc, char *argv[], int &V, int &E, int distance[][3])
{
    if (argc <= 1)
    {
        cout << "No file name entered. Exiting...";
        return;
    }
    ifstream infile(argv[1]); // open the file

    if (infile.is_open() && infile.good())
    {
        string line = "";
        int i = 0;
        int ind = 0;
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
                distance[ind][0] = a;
                distance[ind][1] = b;
                distance[ind][2] = cost;
                ind++;
            }
            i++;
            cout << line << '\n';
        }
    }
    else
    {
        cout << "Failed to open file..";
    }
}

int main(int argc, char *argv[])
{
    int source, destination;
    int distance[1000][3];

    int V, E;
    cout << "The sample input is as follows: \n";
    readfile(argc, argv, V, E, distance);
    cout << "Enter the source and the destination " << endl;
    cout << "(Vertex numbers should be less than " << V << ")\n";
    cin >> source >> destination;

    graph *G = readfile_to_graph(V, E, distance);
    bellman_ford(G, source, destination);

    return 0;
}
// storing and printing the path information as well alongside the cost of the shortest path to every vertex from a source vertex in the dijkstra's algorithm

// I have lifted the base code from class notes and modified it to store and print the path information as well
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#define V 9

int minDistance(int dist[], bool sptSet[])
{
  int min = INT_MAX, min_index;

  for (int v = 0; v < V; v++)
  {
    if (sptSet[v] == false && dist[v] <= min)
    {
      min = dist[v], min_index = v;
    }
  }

  return min_index;
}

// this function has been modified to print both the distance and the exact path from the source to each vertex
void printSolution(int dist[], int pred[]) // requesting the 'pred' array as well that stores the predecessor vertex number for each vertex in the shortest path
{
  printf("Vertex \t|\t Distance from Source \t|\t Path\n");
  printf("-----------------------------------------------------------------------\n");

  for (int i = 0; i < V; i++)
  {
    printf("%d \t|\t\t %d \t\t|\t", i, dist[i]);

    // prints the path beginning from destination to source
    int j = i;      // i is the destination vertex for the current shortest path from the source vertex to some other vertex
    while (j != -1) // 'j' becomes -1 when in the previous iteration of the loop j was at the source vertex and j = pred[j]; was executed, since there are no other vertices in the shortest path from the source vertex to itself the pred[src] is -1
    {
      // printing the current vertex
      if (j == i)
      {
        printf("%d ", j);
      }
      else
      {
        printf("<- %d ", j);
      }

      // moving on to the predecessor of the current vertex
      j = pred[j];
    }

    printf("\n");
  }
}

// to store the exact path information of the shortest path to every vertex I will keep track of the correct predecessors for each vertex, during each the execution of the Dijkstra's algorithm, using a 'pred' array
void dijkstra(int graph[V][V], int src)
{
  int dist[V];
  int pred[V]; // array to store the predecessor of each vertex
  bool sptSet[V];

  for (int i = 0; i < V; i++)
  {
    dist[i] = INT_MAX;
    sptSet[i] = false;
    pred[i] = -1; // initialize all predecessors to -1
  }

  dist[src] = 0;

  for (int count = 0; count < V - 1; count++)
  {
    int u = minDistance(dist, sptSet);
    sptSet[u] = true;

    for (int v = 0; v < V; v++)
    {
      // since there are no other vertices in the shortest path from the source vertex to itself, the pred[src] will always remain -1 which is its initial value, in line 76 sptSet[src] will be set to true always before this for loop triggers hence the following if condition will never be trigger for v = src, so the value of pred[v] when v = src, will never be modified and remain to be its initial value of -1
      if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
      {
        dist[v] = dist[u] + graph[u][v];
        pred[v] = u; // update the predecessor to current vertex 'v' according to the shortest path up until the current vertex calculated in the previous line
      }
    }
  }

  printSolution(dist, pred);
}

int main()
{
  int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                     {4, 0, 8, 0, 0, 0, 0, 11, 0},
                     {0, 8, 0, 7, 0, 4, 0, 0, 2},
                     {0, 0, 7, 0, 9, 14, 0, 0, 0},
                     {0, 0, 0, 9, 0, 10, 0, 0, 0},
                     {0, 0, 4, 14, 10, 0, 2, 0, 0},
                     {0, 0, 0, 0, 0, 2, 0, 1, 6},
                     {8, 11, 0, 0, 0, 0, 1, 0, 7},
                     {0, 0, 2, 0, 0, 0, 6, 7, 0}};

  dijkstra(graph, 0);

  return 0;
}

#include <iostream> 
#include <vector> 
#include <queue> 
#include <forward_list> 
#include <algorithm> 

using Vertex = std::size_t;
using Graph = std::vector<std::forward_list<std::size_t>>;


/// <summary> 
/// Printing graph represented as a vector of lists using BFS 
/// </summary> 
/// <param name="Graph">graph</param> 
/// <param name="Vertex">start</param> 
void printVecListBFS(const Graph& graph, Vertex start)
{
    std::vector<bool> isVertexVisited(graph.size(), false);
    isVertexVisited[start] = true;

    std::queue<Vertex> vertexQueue;
    vertexQueue.push(start);

    while (!vertexQueue.empty())
    {
        Vertex vertex = vertexQueue.front();
        vertexQueue.pop();

        std::cout << vertex << "\n";

        for (Vertex neighbour : graph[vertex])
        {
            if (!isVertexVisited[neighbour])
            {
                isVertexVisited[neighbour] = true;
                vertexQueue.push(neighbour);
            }
        }
    }
}

using MGraph = std::vector < std::vector < bool >>;

/// <summary> 
/// Printing graph represented as a Adjacency Matrix(2D Matrix) using BFS 
/// </summary> 
/// <param name="MGraph">mgraph</param> 
/// <param name="Vertex">start</param> 
void printMatrixBFS(const MGraph& mgraph, Vertex start)
{
    std::vector<bool> isVertexVisited(mgraph.size(), false);
    isVertexVisited[start] = true;

    std::queue<Vertex> vertexQueue;
    vertexQueue.push(start);

    while (!vertexQueue.empty())
    {
        Vertex vertex = vertexQueue.front();
        vertexQueue.pop();

        std::cout << vertex << "\n";


        for (Vertex neighbour = 0; neighbour < mgraph.size(); ++neighbour)
        {
            if (mgraph[vertex][neighbour] && !isVertexVisited[neighbour])
            {
                isVertexVisited[neighbour] = true;
                vertexQueue.push(neighbour);
            }
        }
    }

}

int main()
{
    Graph graph(5);
    graph[0] = { 1,3 };
    graph[1] = { 0 };
    graph[2] = { 4 };
    graph[4] = { 0, 3 };
    printVecListBFS(graph, 4);

    MGraph mgraph{
     {0,1,0,1,0},
     {1,0,0,0,0},
     {0,0,0,0,1},
     {0,0,0,0,0},
     {1,0,0,1,0}
    };
    printMatrixBFS(mgraph, 4);

}

#include <iostream>
#include <vector>
#include <forward_list>
#include <stack>

using Vertex = std::size_t;
using Graph = std::vector<std::forward_list<Vertex>>;

void addEdge(Graph& graph, Vertex from, Vertex to) {
    graph[from].push_front(to);
}

/// <summary>
/// /// Printing graph represented as a vector of lists using BFS 
/// </summary>
/// <param name="graph"></param>
/// <param name="startVertex"></param>
void printVecListDFS(const Graph& graph, Vertex startVertex) {
    size_t vertices = graph.size();
    std::vector<bool> visited(vertices, false);
    std::stack<Vertex> s;

    s.push(startVertex);
    visited[startVertex] = true;

    while (!s.empty()) {
        Vertex currentVertex = s.top();
        s.pop();
        std::cout << currentVertex << " ";

        for (Vertex neighbor : graph[currentVertex]) {
            if (!visited[neighbor]) {
                s.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
    std::cout << std::endl;
}

using MGraph = std::vector<std::vector<bool>>;

/// <summary>
/// Printing graph represented as a Adjacency Matrix(2D Matrix) using DFS 
/// </summary>
/// <param name="graph"></param>
/// <param name="startVertex"></param>
void printMatrixDFS(const MGraph& graph, Vertex startVertex) {
    size_t vertices = graph.size();
    std::vector<bool> visited(vertices, false);
    std::stack<Vertex> s;

    s.push(startVertex);
    visited[startVertex] = true;

    while (!s.empty()) {
        Vertex currentVertex = s.top();
        s.pop();
        std::cout << currentVertex << " ";

        for (Vertex i = 0; i < vertices; ++i) {
            if (graph[currentVertex][i] && !visited[i]) {
                s.push(i);
                visited[i] = true;
            }
        }
    }
    std::cout << std::endl;
}

int main() {
    Graph graph(5);
    graph[0] = { 1,3 };
    graph[1] = { 0 };
    graph[2] = { 4 };
    graph[4] = { 0, 3 };
    printVecListDFS(graph, 4);

    MGraph mGraph{
     {0,1,0,1,0},
     {1,0,0,0,0},
     {0,0,0,0,1},
     {0,0,0,0,0},
     {1,0,0,1,0}
    };
    printMatrixDFS(mGraph, 4);



    return 0;
}
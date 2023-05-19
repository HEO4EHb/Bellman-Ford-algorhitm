
#include <iostream>
using namespace std;

/*
* Для нахождения кратчайших путей от одной вершины до всех остальных, воспользуемся методом динамического программирования. 
Построим матрицу А;, элементы которой будут обозначать следующее: А, _ это длина
кратчайшего пути из з в і, содержащего не более і рёбер.
Путь, содержащий 0 рёбер, существует только до
вершины з. Таким образом, А; равно 0 при і = 5, и
то в противном случае.
Теперь рассмотрим все пути из з в і, содержащие ровно j ребер. Каждый такой путь есть путь из і - 1 ребра, к
которому добавлено последнее ребро. Если про пути длины j - 1 все данные уже подсчитаны, то определить j-й столбец матрицы не составляет труда.
*/

// вес ребра в графе
struct Edge {
    int src, dest, weight;
};

// связный направленный и взвешенный граф
struct Graph {
    // V-> количество вершин, E-> количество ребёр
    int V, E;

    // массив ребёр
    struct Edge* edge;
};

// граф с V вершинам и E рёбрами
struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}

// функция для вывода
void printArr(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

// функция для нахождения кратчайшего расстояния из начальной 
// в смежные вершины с помощью алгоритма беллмана форда  
// опеределяет отрицательный вес 
void BellmanFord(struct Graph* graph, int src)
{
    int V = graph->V;
    int E = graph->E;
    int *dist =new int [V];

    // все расстояния от начальной до других бесконечные 
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // Шаг 2: проходим все ребра  |V| - 1 раз. кратчайший путь из src к другим вершанм v |V| - 1 ребёр
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX
                && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    // Шаг 3: проверка на отрицательный вес . 
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX
            && dist[u] + weight < dist[v]) {
            printf("Graph contains negative weight cycle");
            return;
        }
    }

    printArr(dist, V);

    return;
}

// 
int main()
{
    
    int V = 5; 
    int E = 8; 
    struct Graph* graph = createGraph(V, E);

    // ребро 0-1 ( A-B )
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = -1;

    // ребро 0-2 ( A-C )
    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 4;

    // ребро 1-2 ( B-C )
    graph->edge[2].src = 1;
    graph->edge[2].dest = 2;
    graph->edge[2].weight = 3;

    // ребро 1-3 ( B-D )
    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 2;

    // ребро 1-4 ( B-E )
    graph->edge[4].src = 1;
    graph->edge[4].dest = 4;
    graph->edge[4].weight = 2;

    // ребро 3-2 ( D-C )
    graph->edge[5].src = 3;
    
    // ребро 3-1 ( D-B )
    graph->edge[6].src = 3;
    graph->edge[6].dest = 1;
    graph->edge[6].weight = 1;

    // ребро 4-3 ( E-D )
    graph->edge[7].src = 4;
    graph->edge[7].dest = 3;
    graph->edge[7].weight = -3;

    
    BellmanFord(graph, 0);

    return 0;
}
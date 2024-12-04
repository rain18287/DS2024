#include"D:\university\shujujiegou\DS2024\unite\Graph\Graph.h"
// 主函数和测试案例
int main() {
    // 创建更复杂的图
    Graph graph(8);

    // 添加边
    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 3, 6);
    graph.addEdge(1, 4, 2);
    graph.addEdge(2, 4, 4);
    graph.addEdge(3, 5, 1);
    graph.addEdge(4, 5, 7);
    graph.addEdge(4, 6, 8);
    graph.addEdge(5, 7, 2);
    graph.addEdge(6, 7, 3);

    // 显示图
    graph.displayGraph();

    // 测试 BFS
    BFS(graph, 0);

    // 测试 DFS
    DFS(graph, 0);

    // 测试 Dijkstra 算法
    Dijkstra(graph, 0);

    // 测试 Prim 算法
    Prim(graph);

    return 0;
}

//
// Created by 83923 on 2023/5/5.
//
#include <stdio.h>
#include <stdlib.h>

typedef char vextype[20];
# define max_dis 100000

typedef struct {
    int N, E;//N是顶点数，E是边数
    int** matrix;//储存邻接矩阵
    vextype* vertex;//存储节点的名字
} Graph;

Graph createGraph(int n) {
    int i, j;
    Graph g;
    g.N = n;
    g.matrix = (int**)malloc(sizeof(int*) * g.N);
    for (i = 0; i < n; i++) {
        g.matrix[i] = (int*)malloc(sizeof(int) * g.N);
    }
    for (i = 0; i < g.N; i++) {
        for (j = 0; j < g.N; j++) {
            g.matrix[i][j] = max_dis;
        }
    }
    for (i = 0; i < g.N; i++) {
        g.matrix[i][i] = 0;
    }
    g.vertex = (vextype*)malloc(sizeof(vextype) * g.N);
    return g;
}

Graph inputedges(Graph g, int edge_num){
    for (int i = 0; i < edge_num; i++) {
        int start_idx, end_idx, weight;
        scanf("%d %d %d", &start_idx, &end_idx, &weight);
        g.matrix[start_idx][end_idx] = weight;
        g.matrix[end_idx][start_idx] = weight;
    }
}
int findminkey(Graph graph, int key[], int inMST[]){
    //key的长度就是graph.N，蕴含的
    int min = max_dis;
    int minindex;
    for (int i = 0; i < graph.N; ++i) {
        if(!inMST[i] && key[i] < min){
            min = key[i];
            minindex = i;
        }
    }
    return minindex;
}

//返回MST中vertex这个顶点和其父节点间的边权重
int weightinMST(Graph graph, int parent[], int vertex){
    return graph.matrix[vertex][parent[vertex]];
}
int primMST(Graph graph){
    int key[graph.N];
    int parent[graph.N];
    int inMST[graph.N];
    for (int i = 0; i < graph.N; ++i) {
        key[i] = max_dis;
        parent[i] = -1;
        inMST[i] = 0;
    }

    key[0] = 0;

    for (int i = 0; i < graph.N ; ++i) {
        int u = findminkey(graph, key, inMST);
        inMST[u] = 1;
        //接下来更新所有key值
        for (int j = 0; j < graph.N; ++j) {
            if(!inMST[j] && graph.matrix[u][j] > 0 && graph.matrix[u][j] < key[j]){
                key[j] = graph.matrix[u][j];
                parent[j] = u;
            }
            //这边inMST的判断很重要才对！ 如果一个已经在MST里但是key值被改更小了，结果导致parent变了，就错了！
        }
    }

    int sum = 0;
    for (int i = 1; i < graph.N; ++i) {
        sum = sum + weightinMST(graph, parent, i);
    }
    return sum;

}
int main(){
    int node_num;
    int edge_num;

    scanf("%d %d", &node_num, &edge_num);
    Graph g = createGraph(node_num);
    for(int i = 0; i < node_num; i++) {
        sprintf(g.vertex[i], "%d", i);
    }

    inputedges(g, edge_num);
    printf("%d", primMST(g));



    return 0;
}
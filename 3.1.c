
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * 无向图带权
 * 矩阵存储图
 * 主函数里存边
 * 图以矩阵存储，矩阵元素表示两点的距离即边权重，全设max_dis表示没边，有边才改成权重，主对角线全0，
 */
# define max_dis 100000

typedef char vextype[20];

typedef struct {
    int N, E;//N是顶点数，E是边数
    int** matrix;//储存邻接矩阵
    vextype* vertex;//存储节点的名字
} Graph;

Graph createGraph(int n);
void nodeDegree(Graph g, int* node_degree);
double clusteringCoefficient(Graph g);


/**
 * 创建一个节点数为n的图
 * @param n 节点个数
 * @return 返回这个图
 */
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



/**
 * 计算每个点的度
 * @param g 图
 * @param node_degree 将每个点的度写到这个数组中
 */
void nodeDegree(Graph g, int *node_degree) {
    for (int i = 0; i < g.N; ++i) {
        node_degree[i] = 0;
        for (int j = 0; j < g.N; ++j) {
            if(g.matrix[i][j] > 0 && g.matrix[i][j] < max_dis)//说明存在边
                node_degree[i] ++;
        }
    }
}

/**
 * 计算图的聚类系数
 * @param g 图
 * @return 返回聚类系数
 */
double lcc(Graph g, int vertex){
    int isfriends[g.N];
    for (int i = 0; i < g.N; ++i) {
        if(g.matrix[vertex][i] > 0 && g.matrix[vertex][i] < max_dis){
            isfriends[i] = 1;
        }
        else{
            isfriends[i] = 0;
        }
    }
    //isfriends 储存每个节点是不是vertex的邻居

    int count = 0;
    for (int i = 0; i < g.N; ++i) {
        if(isfriends[i]){
            count++;
        }
    }
    //做一个计数，count 记录了vertex的邻居有几个
    int pairofriends = count * (count - 1) / 2;
    //这个pof就是lcc的分母

    //接下来数vertex的邻居间有几条边
    count = 0;
    for (int i = 0; i < g.N; ++i) {
        if(isfriends[i]){
            for (int j = 0; j < g.N; ++j) {
                if(isfriends[j] && g.matrix[i][j] > 0 && g.matrix[i][j] < max_dis){
                    count++;
                }
            }
        }
    }
    count /= 2;   //此时count存储的就是vertex的邻居间的边数
    double lccofv = 0;
    if(pairofriends != 0)
        lccofv = count * 1.0 / pairofriends;
    return lccofv;
}
double clusteringCoefficient(Graph g) {
    double cc = 0;
    double lcci;
    for (int i = 0; i < g.N; ++i) {
        lcci = lcc(g, i);
        cc = cc + lcci;
    }
    cc = cc / g.N;
    return cc;
}



int main() {
    int node_num;
    int edge_num;

    scanf("%d %d", &node_num, &edge_num);

    Graph g = createGraph(node_num);
    for(int i = 0; i < node_num; i++) {
        sprintf(g.vertex[i], "%d", i);
    }

    for (int i = 0; i < edge_num; i++) {
        int start_idx, end_idx, weight;
        scanf("%d %d %d", &start_idx, &end_idx, &weight);
        g.matrix[start_idx][end_idx] = weight;
        g.matrix[end_idx][start_idx] = weight;
    }

    int *degree = (int *)malloc(sizeof(int) * g.N);
    nodeDegree(g, degree);
    printf("degree distribution:\n");
    for(int i=0; i<g.N; i++)
    {
        printf("node%s:%d,", g.vertex[i], degree[i]);
    }
    printf("\n");
    double c = clusteringCoefficient(g);
    printf("clustering coefficient:%f\n", c);

    return 0;
}
//
// Created by 83923 on 2023/5/5.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define max_dis 100000

typedef char vextype[20];

typedef struct {
    int N, E;//N是顶点数，E是边数
    int** matrix;//储存邻接矩阵
    vextype* vertex;//存储节点的名字
} Graph;

Graph createGraph(int n);
int isConnected(Graph g);
int Diameter(Graph g);
int Radius(Graph g);
int dijkstra(Graph g, int start, int end, int* path);
void printPath(int d, int* diameter_path, Graph g);

void DFS(Graph g, int i, int* visited, int* count);
int DFSTraverse(Graph g);
void floyd(Graph g, int** dist, int** path);


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
 * 根据距离d和路径数组path输出路径，这样就不需要路径的节点数也能正确输出路径
 * @param d 路径长度
 * @param diameter_path 储存路径的数组
 * @param g 图
 */
void printPath(int d, int *diameter_path, Graph g)
{
    int k = 0;
    int path_length = 0;
    printf("Path: ");
    do {
        printf("%s->", g.vertex[diameter_path[k]]);
        path_length += g.matrix[diameter_path[k]][diameter_path[k + 1]];
        k++;
    } while (path_length < d);
    printf("%s\n", g.vertex[diameter_path[k]]);
}

/**
 * 判断图是否连通
 * @param g 图
 * @return 连通返回1，否则返回0
 */
void dfss(Graph g, int visited[], int vertex){
    visited[vertex] = 1;
    for (int i = 0; i < g.N; ++i) {
        if(g.matrix[vertex][i] > 0 && g.matrix[vertex][i] < max_dis && !visited[i]){
            dfss(g, visited, i);
        }
    }
}
int dfssingle(Graph g, int start){
    int visited[g.N];
    for (int i = 0; i < g.N; ++i) {
        visited[i] = 0;
    }
    //准备好visited数组
    dfss(g, visited, start);   //调用dfss做一次遍历，dfss只能遍历一个联通分支
    int allvisited = 1;
    for (int i = 0; i < g.N; ++i) {
        if(!visited[i])
            allvisited = 0;
    }
    return allvisited;
}
int isConnected(Graph g) {
    return dfssingle(g, 0);
}


/**
 * 使用dijkstra算法计算单源最短路径
 * @param g 图
 * @param start 起点
 * @param end 终点
 * @param path 从start到end的路径, [start,...,end]
 * @return 路径长度
 */
int dijkstra(Graph g, int start, int end, int *path)
{
    int inpath[g.N];
    int dist[g.N];
    int prev[g.N];
    for (int i = 0; i < g.N; ++i) {
        dist[i] = max_dis;
        inpath[i] = 0;  //所有点都不在path中
        prev[i] = -1;
    }
    //准备好dist数组,表示每个点到已生成路径的最小距离

    dist[start] = 0;
    //inpath[start] = 1;  //让start点进入！ 循环里面再进入
    for (int i = 0; i < g.N; ++i) {

        int min = max_dis, nearest;
        for (int j = 0; j < g.N; ++j) {
            if(!inpath[j] && dist[j] < min){
                min = dist[j];
                nearest = j;
            }
        }
        //nearest 就确定好了，下一个被加入到path中

        inpath[nearest] = 1;     //把nearest这个点放到path里面

        int new = nearest;   // 新加入点new就是nearest，同一个点
        //下面更新所有点的信息
        for (int j = 0; j < g.N; ++j) {
            if(!inpath[j] && g.matrix[new][j] > 0 && g.matrix[new][j] + dist[new] < dist[j]){
                dist[j] = g.matrix[new][j] + dist[new];
                prev[j] = new;
            }
        }
        //这样就完成了所有点到path距离的更新，可以下一次迭代
    }
    int stack[g.N];
    int top = -1;
    int cur = end;
    while(cur != -1){
        stack[++top] = cur;
        cur = prev[cur];
    }
    int cnt = 0;
    while(top > -1){

        path[cnt++] = stack[top--];
    }

    return dist[end];
}
int dijkstraB(Graph g, int start, int end)
{
    int inpath[g.N];
    int dist[g.N];
    int prev[g.N];
    for (int i = 0; i < g.N; ++i) {
        dist[i] = max_dis;
        inpath[i] = 0;  //所有点都不在path中
        prev[i] = -1;
    }
    //准备好dist数组,表示每个点到已生成路径的最小距离

    dist[start] = 0;
    //inpath[start] = 1;  //让start点进入！ 循环里面再进入
    for (int i = 0; i < g.N; ++i) {
        int min = max_dis, nearest;
        for (int j = 0; j < g.N; ++j) {
            if(!inpath[j] && dist[j] < min){
                min = dist[j];
                nearest = j;
            }
        }
        //nearest 就确定好了，下一个被加入到path中

        inpath[nearest] = 1;     //把nearest这个点放到path里面

        int new = nearest;   // 新加入点new就是nearest，同一个点
        //下面更新所有点的信息
        for (int j = 0; j < g.N; ++j) {
            if(!inpath[j] && g.matrix[new][j] > 0 && g.matrix[new][j] + dist[new] < dist[j]){
                dist[j] = g.matrix[new][j] + dist[new];
                prev[j] = new;
            }
        }
        //这样就完成了所有点到path距离的更新，可以下一次迭代
    }

    return dist[end];
}

/**
 * 计算图的直径。提示：Floyd算法
 * @param g 图
 * @return 直径的长度
 */
int Diameter(Graph g) {
    int distmatr[g.N][g.N];
    for (int i = 0; i < g.N; ++i) {
        for (int j = 0; j < g.N; ++j) {
            distmatr[i][j] = dijkstraB(g, i, j);
        }
    }
    int max = 0;
    for (int i = 0; i < g.N; ++i) {
        for (int j = 0; j < g.N; ++j) {
            if(i != j && distmatr[i][j] > max){
                max = distmatr[i][j];
            }
        }
    }
    return max;
}


/**
 * 计算图的半径
 * @param g 图
 * @return 半径长度
 */
int Radius(Graph g) {
    int distmatr[g.N][g.N];
    for (int i = 0; i < g.N; ++i) {
        for (int j = 0; j < g.N; ++j) {
            distmatr[i][j] = dijkstraB(g, i, j);
        }
    }
    int ecc[g.N];
    for (int i = 0; i < g.N; ++i) {
        int max = 0;
        for (int j = 0; j < g.N; ++j) {
            if(i != j && distmatr[i][j] > max){
                max = distmatr[i][j];
            }
        }
        ecc[i] = max;
    }
    int radius= max_dis;
    for (int i = 0; i < g.N; ++i) {
        if(ecc[i] < radius){
            radius = ecc[i];
        }
    }
    return radius;
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
    printf("connected: %d\n", isConnected(g));

    if (isConnected(g))
    {
        int* short_path = (int*)malloc(sizeof(int) * g.N);
        int dis = dijkstra(g, 1, 3, short_path);
        printf("the minimum fare between 1 and 3: %d\n", dis);
        printPath(dis, short_path, g);
        free(short_path);
        int d = Diameter(g);
        printf("diameter:%d\n", d);

        int r = Radius(g);
        printf("radius:%d\n", r);
    }

    return 0;
}
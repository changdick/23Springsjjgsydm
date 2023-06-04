//
// Created by 83923 on 2023/5/4.
//
#include "adjlist.h"
#include "MST.h"
#include "matrix.h"
int main(){

/*
    //下面代码说明完成了图的矩阵存储
    graphmat  * graphB = createMatgraph(8);
    addedgeMat(graphB,0,1);
    addedgeMat(graphB,1,3);
    addedgeMat(graphB,4,1);
    addedgeMat(graphB,3,7);
    addedgeMat(graphB,7,4);
    addedgeMat(graphB,0,2);
    addedgeMat(graphB,5,2);
    addedgeMat(graphB,5,6);
    addedgeMat(graphB,2,6);
    //printmatrix(graphB);
    //BFSmat(graphB);
    graphmat * graphBdfsst = dfsspantreemat(graphB);
    printmatrix(graphBdfsst);
*/
//下面代码试一下自己写的MST
/*
    graphweightmat * graphC = createweightMatgraph(7);
    addweightedgeMat(graphC,0,1,18);
    addweightedgeMat(graphC,0,4,23);
    addweightedgeMat(graphC,0,5,4);
    addweightedgeMat(graphC,0,6,7);
    addweightedgeMat(graphC,2,1,5);
    addweightedgeMat(graphC,2,3,10);
    addweightedgeMat(graphC,1,3,8);
    addweightedgeMat(graphC,4,3,15);
    addweightedgeMat(graphC,4,1,12);
    addweightedgeMat(graphC,4,5,25);
    addweightedgeMat(graphC,6,5,7);
    addweightedgeMat(graphC,3,5,20);
    primMSTmat(graphC);
*/
//下面代码演示的是迪杰斯特拉最短路径算法

    graphweightmat * graphD = createweightMatgraph(6);
    addweightdirectionaledgeMat(graphD, 0, 2, 10);
    addweightdirectionaledgeMat(graphD, 0, 5, 100);
    addweightdirectionaledgeMat(graphD, 0, 4, 30);
    addweightdirectionaledgeMat(graphD, 1, 2, 5);
    addweightdirectionaledgeMat(graphD, 2, 3, 50);
    addweightdirectionaledgeMat(graphD, 3, 5, 10);
    addweightdirectionaledgeMat(graphD, 4, 3, 20);
    addweightdirectionaledgeMat(graphD, 4, 5, 60);
    dijkstramat(graphD, 0,5);
    printf("\n");
    floydmat(graphD,0,5);

//下面代码是拓扑排序
/*
    graphmat* graphTopoA = createMatgraph(10);
    adddirectedgeMat(graphTopoA, 8, 7);
    adddirectedgeMat(graphTopoA, 8, 5);
    adddirectedgeMat(graphTopoA, 7, 0);
    adddirectedgeMat(graphTopoA, 0, 9);
    adddirectedgeMat(graphTopoA, 5, 6);
    adddirectedgeMat(graphTopoA, 5, 4);
    adddirectedgeMat(graphTopoA, 4, 1);
    adddirectedgeMat(graphTopoA, 4, 2);
    adddirectedgeMat(graphTopoA, 3, 2);
    adddirectedgeMat(graphTopoA, 3, 4);
    adddirectedgeMat(graphTopoA, 3, 1);
    toposequence(graphTopoA);
    printf("\n");
    toposequenceII(graphTopoA);
    printf("\n");
    DFSIImat(graphTopoA);

    graphadj * graphTopoB = graphinit(10);
    directedge(graphTopoB, 8, 7);
    directedge(graphTopoB, 8, 5);
    directedge(graphTopoB, 7, 0);
    directedge(graphTopoB, 0, 9);
    directedge(graphTopoB, 5, 6);
    directedge(graphTopoB, 5, 4);
    directedge(graphTopoB, 4, 1);
    directedge(graphTopoB, 4, 2);
    directedge(graphTopoB, 3, 2);
    directedge(graphTopoB, 3, 4);
    directedge(graphTopoB, 3, 1);
    printf("\n");
    toposequenceIII(graphTopoB);
    printf("\n");
    deathfirstsearchB(graphTopoB);
    //上面这一段代码用三个不同函数完成的拓扑排序。
    printf("\n");
    graphmat * graphtopoC = createMatgraph(8);
    adddirectedgeMat(graphtopoC, 0 ,2);
    adddirectedgeMat(graphtopoC, 2 ,4);
    adddirectedgeMat(graphtopoC, 1 ,3);
    adddirectedgeMat(graphtopoC, 1 ,5);
    adddirectedgeMat(graphtopoC, 3 ,5);
    adddirectedgeMat(graphtopoC, 3 ,4);
    adddirectedgeMat(graphtopoC, 4 ,6);
    adddirectedgeMat(graphtopoC, 6 ,7);
    adddirectedgeMat(graphtopoC, 5 ,7);
    DFSIImat(graphtopoC);
    */
//下面代码用拓扑排序来判断有无环路
/*
    graphmat * graphtopoC = createMatgraph(5);
    adddirectedgeMat(graphtopoC,0,1);
    adddirectedgeMat(graphtopoC,0,2);
    adddirectedgeMat(graphtopoC,1,3);
    adddirectedgeMat(graphtopoC,2,3);
    adddirectedgeMat(graphtopoC,3,4);
    adddirectedgeMat(graphtopoC,4,1);
    printf("%d",topojudgecirclemat(graphtopoC));
*/
    //下面代码说明完成了图的邻接表存储
    //利用这个做广度优先生成树
/*
    graphadj * graphA = graphinit(8);
    addedge(graphA,0,2);
    addedge(graphA,4,1);
    addedge(graphA,0,1);
    addedge(graphA,1,3);
    addedge(graphA,2,5);
    addedge(graphA,2,6);
    addedge(graphA,7,3);
    addedge(graphA,7,4);
    addedge(graphA,6,5);
    //printadjlist(graphA);
    //deathfirstsearch(graphA);
    //printf("\n");
    bfs(graphA,0);
    printf("\n");
    bfsspantree(graphA, 0);
   */
   /*
    int graph[V][V] = {
            {0, 2, 0, 6, 0},
            {2, 0, 3, 8, 5},
            {0, 3, 0, 0, 7},
            {6, 8, 0, 0, 9},
            {0, 5, 7, 9, 0},
    };
    primMST(graph);
     */
   //下面代码打印关键路径
   /*
    graphadj * graphE = graphinit(9);
    directweightedge(graphE, 0, 1, 6);
    directweightedge(graphE, 0, 2, 4);
    directweightedge(graphE, 0, 3, 5);
    directweightedge(graphE, 1, 4, 1);
    directweightedge(graphE, 2, 4, 1);
    directweightedge(graphE, 3, 5, 2);
    directweightedge(graphE, 4, 6, 9);
    directweightedge(graphE, 4, 8, 7);
    directweightedge(graphE, 5, 8, 4);
    directweightedge(graphE, 6, 7, 2);
    directweightedge(graphE, 8, 7, 4);
    craticalpathadj(graphE);
*/
}
//
// Created by 83923 on 2023/5/4.
//

#ifndef GRAPH_ADJLIST_H
#define GRAPH_ADJLIST_H
#include <stdio.h>
#include <stdlib.h>


/*
 * 自己手打邻接表表示的
 */

/*
 * 一、图的实现
 *      邻接表表示图，邻接表是一个数组，链表的数组，图有几个结点，数组就有几个元素。每一个元素都是一条
 *      链表，我们只需要他的头指针head。也就是说，邻接表就是head指针的数组。链表的单元是该节点的邻居节点
 *      我们不必设置头结点，没必要。我们插入新结点，就用头插法就好了。至于这个head指针，作为图，我们可以用
 *      struct包装一下。
 */

//邻接表中链表的单元
typedef struct edge{
    int dest;
    int weight;
    struct edge* next;
}edge;
//edge就是链表单元，其头指针edge* head 就是邻接表的单元

//邻接表的数据类型(为了好看，不要让邻接表直接就是edge head[num_Vertix]，当然它就是)
typedef struct adjlistunit{
    edge* head;
}adjlistunit;

//图就是以邻接表的形式存在的，所以我们定义一下图
typedef struct graphINadj{
    int num_nodes;
    adjlistunit* adjlist;
}graphadj;

//初始化有n个结点的图，不带边
graphadj* graphinit(int n){
    graphadj * graph = (graphadj*)malloc(sizeof (graphadj));
    graph->num_nodes = n;
    adjlistunit * adjlist = (adjlistunit*)malloc(n*sizeof (adjlistunit));
    graph->adjlist = adjlist;
    for (int i = 0; i < n; ++i) {
        graph->adjlist[i].head = NULL;  //初始化全部没有边
    }

    return graph;
}
//添加边
void addedge(graphadj* graph, int src, int dest){
    edge* newedge = (edge*)malloc(sizeof(edge));
    newedge->dest = dest;
    newedge->next = graph->adjlist[src].head;
    graph->adjlist[src].head = newedge;
    //如果是无向图要再加一条对称边
    newedge = (edge*)malloc(sizeof(edge));
    newedge->dest = src;
    newedge->next = graph->adjlist[dest].head;
    graph->adjlist[dest].head = newedge;
}
//添加一条有向边
void directedge(graphadj* graph, int src, int dest){
    edge* newedge = (edge*)malloc(sizeof(edge));
    newedge->dest = dest;
    newedge->next = graph->adjlist[src].head;
    graph->adjlist[src].head = newedge;
}
//添加一条有向的有权重边
void directweightedge(graphadj* graph, int src, int dest, int weight){
    edge* newedge = (edge*)malloc(sizeof(edge));
    newedge->dest = dest;
    newedge->weight = weight;
    newedge->next = graph->adjlist[src].head;
    graph->adjlist[src].head = newedge;

}
void printadjlist(graphadj* graph){
    for (int i = 0; i < graph->num_nodes; ++i) {
        printf("%d\t",i);
        for(edge * p = graph->adjlist[i].head; p != NULL; p = p->next){
            printf("%d ",p->dest);
        }
        printf("\n");
    }
}
//接下来实现dfs，dfs是一种递归的调用，而且需要我们准备vitsited数组。我们采用函数套函数的方法
//其中dfs函数是实现对一个连通分支的遍历，但多个连通分支要轮换节点，下面那个函数就通过for循环轮换节点实现多个分支遍历
void DFS(graphadj * graph, int start, int visited[]){
    visited[start] = 1;
    printf("  %d", start);
    for(edge* p = graph->adjlist[start].head; p != NULL; p = p->next){
        if(!visited[p->dest]){
            DFS(graph, p->dest, visited);
        }
    }
}
void deathfirstsearch(graphadj* graph){
    //这一部分是准备visited数组
    int visited[graph->num_nodes];
    for (int i = 0; i < graph->num_nodes; ++i) {
        visited[i] = 0;
    }
    //初始化成0，visited数组就准备好了
    for (int i = 0; i < graph->num_nodes; ++i) {
        if(!visited[i]){
            DFS(graph, i, visited);
        }
    }
    //我们这样实现的话，dfs函数始终传graph这个参数。但是如果我们定义图的邻接表全局变量时候，就不用传这个参数
}

void bfs(graphadj * graph, int start){
    //准备一个队列
    int queue[graph->num_nodes];
    int front = 0;
    int rear = 0;
    //
    //准备visited数组
    int visited[graph->num_nodes];
    for (int i = 0; i < graph->num_nodes; ++i) {
        visited[i] = 0;
    }

    queue[rear++] = start;  //第一个遍历的进队列

    while(front != rear){
        int current = queue[front++]; //出队列，访问这一个
        if(!visited[current]){
            visited[current] = 1;
            printf("  %d", current);
            for(edge* p = graph->adjlist[current].head; p != NULL; p = p->next){
                if(!visited[p->dest])  //这句很关键，检查没访问过的才能进队列
                    queue[rear++] = p->dest;
            }
        }
    }
}
//上面这个bfs检查和标记visited的时间不合适，会多次进队列，不好
//这个bfs也是单连通分支的，如果我们要全部遍历，还得向dfs那样处理
//广度优先生成树
/*
 * 邻接表形式下的广度优先生成树需要记录一个树边的集合，但函数就是把bfs稍微改一下就可以了
 * 记录树边可以用邻接表再弄一个图返回，也可以用矩阵表示方法
 * 还有广度优先编号
 */
void bfsspantree(graphadj * graph, int start){
    //准备一个队列
    int queue[graph->num_nodes];
    int front = 0;
    int rear = 0;
    //
    //准备visited数组
    int visited[graph->num_nodes];
    for (int i = 0; i < graph->num_nodes; ++i) {
        visited[i] = 0;
    }
    graphadj * spantree = graphinit(graph->num_nodes);
    queue[rear++] = start;  //第一个遍历的进队列
    visited[start] = 1;
    while(front != rear){
        int current = queue[front++]; //出队列，访问这一个


            for(edge* p = graph->adjlist[current].head; p != NULL; p = p->next){
                if(!visited[p->dest]) {  //这句很关键，检查没访问过的才能进队列
                    queue[rear++] = p->dest;
                    addedge(spantree, current, p->dest);
                    visited[p->dest] = 1;
                }
            }
    }
    printadjlist(spantree);
}

/*
// *  下面是拓扑排序算法
// *  拓扑排序算法的适用对象：有向无环图
// *  作用的效果：给有向无环图生成对应的拓扑序列
// *  算法：每次输出入度为0的边并且把它删掉，直至全部输出
// *  具体实现思路：为了检测入度，得先做一个入度计算，有一个入度数组存储每个结点的入度。同时要使用栈或者队列来存储每轮新增的0入度结点。
// *  第一次要对全部的入度做一个计算并存在一个数组，之后循环里每一轮只需把删去的那个顶点会邻接到的顶点入度减掉1，再检查是否为0即可
// *
// */
//为了实现拓扑排序，先得实现计算入度操作，这个函数两个参数为图和一个准备好的数组，数组长度应为图的顶点数
void makeindegreeAdj(graphadj * graph, int indegree[]){
    for (int i = 0; i < graph->num_nodes; ++i) {
        indegree[i] = 0;
    }
    for (int i = 0; i < graph->num_nodes; ++i) {
        adjlistunit p = graph->adjlist[i];
        while(p.head){
            indegree[p.head->dest]++;
            p.head = p.head->next;
        }
    }
}
//拓扑排序算法直接用indegree上的链栈来做
void toposequenceIII(graphadj* graph){
    //Step1 计算好入度
    int indegree[graph->num_nodes];
    makeindegreeAdj(graph, indegree);

    //不另外设置栈，直接用indegree数组上实现链栈
    int top = -1;     //top=-1来表示空栈
    //Step2 找0入度顶点,并将其入栈
    for (int i = 0; i < graph->num_nodes; ++i) {
        if(indegree[i] == 0){
            indegree[i] = top;
            top = i;
        }
    }
    //Step3 循环输出
    while(top != -1){
        //第一步 出栈
        int current = top;
        top = indegree[top];

        //第二步 输出
        printf(" %d", current);

        //第三步 (删current)根据它的值调整indegree,把相应点入度减1
        edge * p= graph->adjlist[current].head;
        while(p){
            indegree[p->dest]--;
            //第四步 每次减1后，检查一下是否等于0.是的话入栈
            if(indegree[p->dest] == 0){
                indegree[p->dest] = top;
                top = p->dest;
            }
            p = p->next;
        }
    }

}
//其实链栈的这一个优化仅仅是特殊的操作方式记一下就行
/*
 * 入栈    indegree[i] = top;  top = i;
 * 出栈    current = top;    top = indegree[top];
 */

//拓扑排序和dfs的关系
//改动：dfs的改到递归语句的后面，即本来是“先访问当前节点，再对当前节点邻接到的结点依次做深度优先输出”
//改成了“先对当前节点的邻接到的结点依次做完深度优先搜索，再访问当前的结点”
void DFSB(graphadj * graph, int start, int visited[]){
    visited[start] = 1;

    for(edge* p = graph->adjlist[start].head; p != NULL; p = p->next){
        if(!visited[p->dest]){
            DFSB(graph, p->dest, visited);
        }
    }
    printf(" %d", start);
}
void deathfirstsearchB(graphadj* graph){
    //这一部分是准备visited数组
    int visited[graph->num_nodes];
    for (int i = 0; i < graph->num_nodes; ++i) {
        visited[i] = 0;
    }
    //初始化成0，visited数组就准备好了
    for (int i = 0; i < graph->num_nodes; ++i) {
        if(!visited[i]){
            DFSB(graph, i, visited);
        }
    }
}
//这个dfsB算法只不过改了深度优先搜索的输出顺序，为什么就直接实现了拓扑排序？
/*
 * 看拓扑排序的定义：如果a可达b，那么a在b前面。
 * 这句话在有向无环图中是这个意思：1、a肯定在b的后面 2、a可达b，b绝对不可达a,因为无环路
 * 所以我们做拓扑序列，保证的事情就是在这个节点输出之前，它后面可达的都应已经搜索
 * 那么就是  ”当前顶点邻接到的顶点都做深度优先搜索的逆序输出“
 *          ”输出当前顶点“
 * 这两句就可以完成拓扑排序(逆输出),他从语句含义上是与拓扑排序的含义高度吻合、高度形象的
 * (关注含义，不要去管递归里面发生了什么！！！)
 *
 * 所以逆向的深度优先搜索在逆向递归调用的时候，就是拓扑排序的定义了。如果a邻接到b，那么b搜索完才能输出a，拓扑顺序不就有了吗？
 */
void craticalpathadj(graphadj * graph){
    //Step1 准备拓扑排序，准备两个时间数组
    int early[graph->num_nodes], late[graph->num_nodes];
    for (int i = 0; i < graph->num_nodes; ++i) {
        early[i] = 0;      //对最早时间初始化
    }
    //计算好入度
    int indegree[graph->num_nodes];
    makeindegreeAdj(graph, indegree);

    //两个栈
    int stackfortopo[graph->num_nodes], topI = -1;
    int stackforlate[graph->num_nodes], topII = -1;

    //Step2 拓扑排序和计算最早时间
    //找0入度顶点,并将其入栈
    for (int i = 0; i < graph->num_nodes; ++i) {
        if(indegree[i] == 0){
            stackfortopo[++topI] = i;
        }
    }
    while(topI != -1){
        //第一步 出栈
        int current = stackfortopo[topI--];
        //第二步 把当前节点存进逆序用的栈
        stackforlate[++topII] = current;
        //第三步 修改当前节点的邻接结点的入度与最早发生时间
        edge * p = graph->adjlist[current].head;
        while(p){
            indegree[p->dest]--;
            if(early[current] + p->weight > early[p->dest]){
                early[p->dest] = early[current] + p->weight;
            }
            if(indegree[p->dest] == 0){
                stackfortopo[++topI] = p->dest;
            }
            p = p->next;
        }
    }
    //至此，拓扑排序和计算事件最早发生时间的过程就完成了，下面计算最迟发生时间
    //先把汇点退出来，它的最早发生时间也是整个工程的工期，也是最迟发生时间初始化的值
    int lastnode = stackforlate[topII--];
    for (int i = 0; i < graph->num_nodes; ++i) {
        late[i] = early[lastnode];
    }
    while(topII != -1){
        //第一步 先退栈取出结点
        int current = stackforlate[topII--];
        //第二步 算该事件最晚发生事件
        edge* edgefromcurrent = graph->adjlist[current].head;
        while(edgefromcurrent){
            if(late[current] > late[edgefromcurrent->dest] - edgefromcurrent->weight){
                late[current] = late[edgefromcurrent->dest] - edgefromcurrent->weight;
            }
            edgefromcurrent = edgefromcurrent->next;
        }
    }
    //当上面循环结束，至此完成了所有事件最早、最迟发生时间的计算
    //下面输出关键活动
    for (int i = 0; i < graph->num_nodes; ++i) {
        edge* edgefromcurrent = graph->adjlist[i].head;
        //对每一个节点，检查它所有边的最早开始时间和最迟开始时间，相等就输出这个边
        while(edgefromcurrent){
            if(early[i] == late[edgefromcurrent->dest] - edgefromcurrent->weight){
                printf("%d - %d     %d\n", i, edgefromcurrent->dest, edgefromcurrent->weight);
            }
            edgefromcurrent = edgefromcurrent->next;
        }
    }
}
#endif //GRAPH_ADJLIST_H

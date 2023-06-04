//
// Created by 83923 on 2023/5/9.
//

#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H
#include <stdio.h>
#include <stdlib.h>
#define Infinit 1000
//邻接矩阵存储图
typedef struct matrixgraph{
    int vertex;
    int ** matrix;
}graphmat,graphweightmat;

//返回一个没有边的不带权图
graphmat * createMatgraph(int nodes){
    graphmat * graph = (graphmat*)malloc(sizeof(graphmat));
    graph->vertex = nodes;
    //下面几行构建矩阵
    graph->matrix = (int**) malloc(sizeof (int *) * nodes);
    for (int i = 0; i < nodes; ++i) {
        graph->matrix[i] = (int*) malloc(sizeof(int) * nodes);
    }
    //矩阵置0
    for (int i = 0; i < nodes; ++i) {
        for (int j = 0; j < nodes; ++j) {
            graph->matrix[i][j] = 0;
        }
    }
    return graph;
}
//添加一条无向不带权边
void addedgeMat(graphmat * graph, int src, int dest){
    graph->matrix[src][dest] = 1;
    graph->matrix[dest][src] = 1;
}
//添加一条有向边不带权
void adddirectedgeMat(graphmat * graph, int src, int dest){
    graph->matrix[src][dest] = 1;
}
graphmat * createweightMatgraph(int nodes){
    graphmat * graph = (graphmat*)malloc(sizeof(graphmat));
    graph->vertex = nodes;
    //下面几行构建矩阵
    graph->matrix = (int**) malloc(sizeof (int *) * nodes);
    for (int i = 0; i < nodes; ++i) {
        graph->matrix[i] = (int*) malloc(sizeof(int) * nodes);
    }
    //矩阵置0
    for (int i = 0; i < nodes; ++i) {
        for (int j = 0; j < nodes; ++j) {
            if(i == j)  graph->matrix[i][j] = 0;
            else    graph->matrix[i][j] = Infinit;
        }
    }
    return graph;
}
//添加带权边
void addweightedgeMat(graphmat * graph, int src, int dest, int weight){
    graph->matrix[src][dest] = weight;
    graph->matrix[dest][src] = weight;
}void addweightdirectionaledgeMat(graphmat * graph, int src, int dest, int weight){
    graph->matrix[src][dest] = weight;
}
// 打印邻接矩阵
void printmatrix(graphmat * graph){
    for (int i = 0; i < graph->vertex; ++i) {
        for (int j = 0; j < graph->vertex; ++j) {
            printf("  %d",graph->matrix[i][j]);
        }
        printf("\n");
    }
}
//图的搜索算法
//1 深度优先搜索
/*
 * 递归实现，每遍历一个节点后从它下一个点开始继续遍历，避免重复，应该设置visit数组标记已访问
 * 遍历过程中，选择下一个起点应判断不是已经访问过的节点
 * 深度优先搜索算法由dfsearch函数递归调用来完成，但是递归过程中要传递visited数组，递归函数做不到这个，所以
 * 我们要设置一个对外的接口，因为dfsearch函数每次要选起点和visited数组两参数，所以设置对外接口，在大DFS函数里
 * 调用dfsearch函数，准备visited数组
 */
void singledfsearch(graphmat* graph, int start, int visited[]){
    visited[start] = 1;
    printf(" %d",start);
    for (int i = 0; i < graph->vertex; ++i) {
        if(graph->matrix[start][i] && !visited[i]){
            singledfsearch(graph, i, visited);
        }
    }
}
void DFSmat(graphmat* graph){
    //Step1 准备好visited数组
    int visited[graph->vertex];
    for (int i = 0; i < graph->vertex; ++i) {
        visited[i] = 0;
    }
    //Step2 调用核心算法
    singledfsearch(graph, 0, visited);
    //Step3 轮换起点继续
    /*
     * 说明：到上一句为止，下面的代码也就是Step3如果不写，那么是完成起点所在连通分支的深度搜索
     * 换言之，对于连通图而言，下面的代码有没有都不影响。可对于有多个连通分支的图而言，就会有差别。
     * 如果没有下面代码，非连通图只有一个连通分支被遍历；而有下面代码，非连通图所有结点都被遍历。
     *
     */
    //主要是为了演示不论换起点和轮换起点，不然Step2不用写，直接Step3循环起点i=0就行了
    for (int i = 1; i < graph->vertex; ++i) {
        if(!visited[i]){
            singledfsearch(graph, i, visited);
        }
    }
}
//至此完成了深度优先搜索
//dfs改装做拓扑排序
void singledfsearchII(graphmat* graph, int start, int visited[]){
    visited[start] = 1;

    for (int i = 0; i < graph->vertex; ++i) {
        if(graph->matrix[start][i] && !visited[i]){
            singledfsearchII(graph, i, visited);
        }
    }
    printf(" %d",start);
}
void DFSIImat(graphmat* graph){
    //Step1 准备好visited数组
    int visited[graph->vertex];
    for (int i = 0; i < graph->vertex; ++i) {
        visited[i] = 0;
    }

    for (int i = 0; i < graph->vertex; ++i) {
        if(!visited[i]){
            singledfsearchII(graph, i, visited);
        }
    }
}
//2 广度优先搜索
/*
 * 广度优先搜索借助队列而不是栈(递归实际上是系统帮忙调栈)
 * 广度优先搜索借助队列，同样需要设置visited数组，每次先起点进队列，此后启动循环，出队列访问的同时，让
 * 未访问顶点进队列即可,进队列即标记为访问过
 *
 */
/*
void BFSmat(graphmat* graph){
    //Step1 准备好visited数组和队列
    int visited[graph->vertex];
    for (int i = 0; i < graph->vertex; ++i) {
        visited[i] = 0;
    }
    int queue[graph->vertex];
    int front = 0, rear = 0;
    int start = 0;

    //Step2 起点入队列，启动循环
    queue[rear++]=start;
    visited[start] = 1;
    while(front != rear){
        int current = queue[front++];
        printf(" %d", current);
        for (int i = 0; i < graph->vertex; ++i) {
            if(graph->matrix[current][i] && !visited[i]){
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
    //到这一步就可以完成单个连通分支的情况。为了实现这个非连通图全顶点遍历，还需要轮换节点。
    //因此，我们可以把设队列、循环遍历的主体部分像dfs算法那样处理，单独抽出一个函数，再和visited一起包装成新函数来调用
    //还能实现选择起点
}
*/
/*
 * 注：vitsited数组改写的节点和visited检查的节点要对应。
 * 例如，如果在节点出队列的时候标记已访问，再节点进队列前检查visited，那就不对应，会造成一个节点多次进队列的情况
 * 如果要在进队列的时候检查未访问，那么就在进队列的时候标记
 * 进队列前检查是否访问是必要的，只让未访问的进队列，并且出队列的时候可以直接访问不再检查
 * 进队列前检查是否访问是必要的，原因是如果点反复进队列队列可能假溢出不够用
 * 所以最好进队列的时候，立即标记已经访问，和检查的时间节点对应上
 */

void bfsearch(graphmat* graph, int start, int visited[]){
    //Step1 准备好队列
    int queue[graph->vertex];
    int front = 0, rear = 0;
    //Step2 起点入队列，标记为已经遍历，开始循环
    queue[rear++]=start;
    visited[start] = 1;
    while(front != rear){
        int current = queue[front++];
        printf(" %d", current);
        for (int i = 0; i < graph->vertex; ++i) {
            if(graph->matrix[current][i] && !visited[i]){
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
}
void BFSmat(graphmat* graph) {
    //Step1 准备好visited数组和队列
    int visited[graph->vertex];
    for (int i = 0; i < graph->vertex; ++i) {
        visited[i] = 0;
    }
/*
    //Step2 调用核心成分(如果只遍历一个连通分支)
    bfsearch(graph, 0, visited);
*/
    //Step2 轮换地调用核心成分(如果要全部遍历完，用这个)
    for (int i = 0; i < graph->vertex; ++i) {
        if(!visited[i])
        bfsearch(graph, i, visited);
    }
}
//到这里完成了广度优先搜索

//生成树
//1 深度优先生成树
/*
 * 连通图深度优先搜索可以形成生成树，成为深度优先生成树，我们如何生成它呢？
 * 思路：生成树也是一个图，并且节点完全一样，就直接再用邻接矩阵表示法把它表示出来就行了
 * 非连通图会有一个生成森林，表示方法也一样。
 * 生成深度优先生成树，只需要对深度优先搜索做一点添加即可。要记录走过的边。
 */
void dfsst(graphmat* graph, int start, int visited[], graphmat* spantree){
    visited[start] = 1;
    for (int i = 0; i < graph->vertex; ++i) {
        if(graph->matrix[start][i] && !visited[i]){
            dfsst(graph, i, visited,spantree);
            addedgeMat(spantree, start, i);
        }
    }
}
graphmat * dfsspantreemat(graphmat* graph){
    graphmat * spantree = createMatgraph(graph->vertex);
    int visited[graph->vertex];
    for (int i = 0; i < graph->vertex; ++i) {
        visited[i] = 0;
    }
    dfsst(graph, 0, visited, spantree);
    return spantree;
}
// 最小生成树
/*
 * prim算法最小生成树
 * 算法：从一个起点开始，每轮选择当前可以看到的边中最小的一个，把这个边纳入到MST里面。逐步扩大MST
 * I 为了实现选择最小的边，需要记录在MST中的每个顶点所能看到的最小边，这个不好记录，不如让每个顶点去看到MST。
 * 每个顶点自己记录自己到MST的距离，看不到设无穷，如果已经与MST邻接，那就是最近的那个值。因为每次新的点加入MST后，让每个点自己检查，看key值是否
 * 需要更新成更小的。
 *
 * II 为了记录最小生成树的边，用一个邻接矩阵储存应该是可以的，但是也可以用数组来标记每个顶点是谁把它带进来的
 * 意思就是说弄一个parent[]数组，parent[i]存储i号顶点是因为谁而进入MST的，这样拿着i和parent[i]即可对应到MST一条边
 *
 * III 与选新顶点至关重要的，因为key[]是根据顶点的视野选的，但是顶点的"视野"中谁在不在MST内它自己不知道，我们得设置一个数组来管理。
 * 因此，设置一个inMST[]数组，记录每个点在不在里面
 * 所以算法分成三步：
 * 第一步：根据当前的MST，找到下一个应该纳入MST的顶点
 * 第二步：把选取的顶点加入到MST中
 * 第三步：MST的”视野“已经变了，因此要更新key
 *
 */
//下面是生成最小生成树的算法
void primMSTmat(graphweightmat * graph){
    //Step1 准备三个数组
    int inMST[graph->vertex];
    int key[graph->vertex];
    int parent[graph->vertex];
    for (int i = 0; i < graph->vertex; ++i) {
        inMST[i] = 0;
        key[i] = Infinit;
        parent[i] = -1;
    }
    //至此是准备好三个数组，完成初始化

    //Step2 弄一个起点进入MST，启动循环
    key[0] = 0;   //改了一个顶点key值，认为使得第一轮他会纳入mst中，启动循环
    //上面parent数组不初始化也没事，但这边得保证parent[0]=-1
    for (int i = 0; i < graph->vertex; ++i) {
        //循环内三大步骤
        //第一步：找到下一个进来的点
        int min = Infinit, minindex;
        for (int j = 0; j < graph->vertex; ++j) {
            if(!inMST[j] && key[j] < min){
                min = key[j];
                minindex = j;
            }
        }
        //第二步：把找到的点minindex纳入MST
        inMST[minindex] = 1;
        //第三步：更新key
        for (int j = 0; j < graph->vertex; ++j) {
            if(!inMST[j] && graph->matrix[minindex][j] < key[j] && graph->matrix[minindex][j]){
                key[j] = graph->matrix[minindex][j];
                parent[j] = minindex;
            }//这个if判断条件3个，其实2个和值无关：距离合法，不应在树中。一个点进入树后，不应再动它的parent值。

        }
    }
    //Step3 输出
    for (int i = 1; i < graph->vertex; ++i) {
        printf("%d - %d  weight: %d\n", i, parent[i], graph->matrix[i][parent[i]]);
    }
}
/*
 * 上面代码就是用prim算法做最小生成树。上面代码的核心部分就是step1和step2.
 *  循环外，是做准备工作，准备数组
 *  设置key[0]= 0 和 parent[0]=1 是启动循环。这样一来第一轮自动会把0号加入到mst中
 *  老师的ppt是专门把0号节点纳入树中并手动把key值都先更新一边，再循环vertex-1轮
 *  而我们是key[0]激活统一的循环操作，让它做vertex轮循环
 *
 *  循环外，是做准备工作，准备数组，设置key[0]= 0 和 parent[0]=1启动循环。
 *  循环内归纳起来是三大步：
 *  第一步： 找到下一个进来的
 *  第二步： 把点加入生成树
 *  第三步： 检查并更新点到树距离
 *
 *  这就是核心算法，后面可以是求权重和，也可以是打印输出。
 *  这个算法框架和迪杰斯特拉单源最短路径算法简直一样。
 */
//kruscal算法前，先讨论单源最短路径的dijkstra算法，因为和prim算法太像
/*
 * dijkstra算法解决的问题是有向网中找最短路径，也需要每步更新
 * I 要从某个结点到另外一个结点，采用路径逐渐扩大的方式。记录每个结点是否已经加入到了路径中
 * 需要设置一个数组inpath,(和inMST几乎一个意思)，每轮扩张路径一步，把一个新结点纳入路径。
 *
 * II 要记录某个顶点为起点到另一个顶点的最短路径，我们得有办法记录路径长，路径长就是这个点到源点的距离。
 * 想象路径扩展过来，如果还碰不到路径，也就是不在”视野“中，那就认为他到源点距离无穷大。每次新结点加到路径
 * 后，检查并更新新结点"视野"内每个结点到源点的距离。
 *
 * III 要记录每一个结点的最短路径，我们还得记录每一个顶点是因为哪个顶点被加入到路径中的，也就是它在路径中的上一个点是谁。
 * 这个方法和最小生成树中哪个parent[]数组是完全一样的
 * 大致框架：
 * 先准备数组distance[] 和 inpath 所有点到源点的距离设无穷大，都不在path里
 * 设置源点到他自己距里为0，即可启动循环
 * 循环内vertex次更新即可得到所有结点到源点距离。每次循环内容：
 * 1先获取下一个加入路径的点
 * 2把这个点加入路径
 * 3更新所有点的distance值
 * 注：distance值可能会更新几次，但是当他inpath后就不会再改变，就定下来了，但在inpath没有为真前，都不是确定的
 *
 */
int dijkstramat(graphweightmat* graph, int start, int destination){
    //Step1 准备辅助的数组
    int inpath[graph->vertex];
    int distance[graph->vertex];
    int previous[graph->vertex];
    for (int i = 0; i < graph->vertex; ++i) {
        inpath[i] = 0;
        distance[i] = Infinit;
    }
//    这样就把数组初始化好了

    //Step2 设置启动循环的路口，设置start的距离为0
    distance[start] = 0;
    previous[start] = -1;
    for (int i = 0; i < graph->vertex; ++i) {
        //循环内分三大步
        //第一步 找下一个进来的点
        int mindistance = Infinit, minindex;
        for (int j = 0; j < graph->vertex; ++j) {
            if(!inpath[j] && distance[j] < mindistance){
                mindistance = distance[j];
                minindex = j;
            }
        }
        //至此， minindex就是下一个被加入进来的点
        //第二步 把新点加到路径中
        inpath[minindex] = 1;
        //第三步 更新每个点到源点的距离（只需检查更新与minindex"视野内"的未确定路径长的点）
        for (int j = 0; j < graph->vertex; ++j) {
            if(!inpath[j] && distance[minindex] + graph->matrix[minindex][j] < distance[j]){
                distance[j] = distance[minindex] + graph->matrix[minindex][j];
                previous[j] = minindex;
            }
        }
        //这样就完成了顶点到源点距离的更新
        //顶点到源点的距离是表示为 顶点到上一个顶点的距离 + 上一个顶点到源点的距离
        //这也是为什么distance[start]要设置成0的一个原因
    }
    //至此，dijkstra算法写完了。distance数组已经储存了所有顶点到源点的距离，可以输出任意一个，也可以全输出
    //输出端：打印表
    for (int i = 0; i < graph->vertex; ++i) {
        printf("vertex %d    distance %d \n", i, distance[i]);
    }
    while(previous[destination] != -1){
        printf("%d <-", destination);
        destination = previous[destination];
    }
    printf("%d", destination);
}


/*
 *  下面是拓扑排序算法
 *  拓扑排序算法的适用对象：有向无环图
 *  作用的效果：给有向无环图生成对应的拓扑序列
 *  算法：每次输出入度为0的边并且把它删掉，直至全部输出
 *  具体实现思路：为了检测入度，得先做一个入度计算，有一个入度数组存储每个结点的入度。同时要使用栈或者队列来存储每轮新增的0入度结点。
 *  第一次要对全部的入度做一个计算并存在一个数组，之后循环里每一轮只需把删去的那个顶点会邻接到的顶点入度减掉1，再检查是否为0即可
 *
 */
//为了实现拓扑排序，先得实现计算入度操作，这个函数两个参数为图和一个准备好的数组，数组长度应为图的顶点数
void makeindegreeMat(graphmat * graph, int indegree[]){
    for (int i = 0; i < graph->vertex; ++i) {
        indegree[i] = 0;   //初始化数组
    }
    for (int i = 0; i < graph->vertex; ++i) {
        for (int j = 0; j < graph->vertex; ++j) {
            if(graph->matrix[i][j]){
                indegree[j]++;
            }
        }
    }
}
void toposequence(graphmat * graph){
    //Step1 计算好入度
    int indegree[graph->vertex];
    makeindegreeMat(graph, indegree);

    //Step2 准备一个栈
    int stack[graph->vertex];
    int top = -1;

    //Step3 找0入度顶点,并将其入栈
    for (int i = 0; i < graph->vertex; ++i) {
        if(indegree[i] == 0){
            stack[++top] = i;   //结点i入栈
        }
    }
    //Step4 启动循环,循环条件是栈不空
    //此后对入度表的更新只要跟新每次输出的那个顶点会影响到的点即可
    while(top != -1){
        //循环第一步： 退栈
        int current = stack[top--];
        //循环第二步： 输出当前顶点
        printf(" %d", current);
        //循环第三步： (相当于删除掉当前顶点)根据当前顶点，调整入度值
        for (int i = 0; i < graph->vertex; ++i) {
            if(graph->matrix[current][i]){
                indegree[i]--;
                //循环第四步： 每次入度减完1后，要检查一下这个顶点是否成为0入度，是则进栈
                if(indegree[i] == 0){
                    stack[++top] = i;
                }
            }
        }
    }
}
//toposequenceII 是使用队列来实现
void toposequenceII(graphmat * graph){
    //Step1 计算好入度
    int indegree[graph->vertex + 1];
    makeindegreeMat(graph, indegree);

    //Step2 准备一个队列
    int queue[graph->vertex];
    int front = 0, rear = 0;

    //Step3 找0入度顶点,并将其入栈
    for (int i = 0; i < graph->vertex; ++i) {
        if(indegree[i] == 0){
            queue[rear++] = i;   //结点i入栈
        }
    }
    //Step4 启动循环,循环条件是栈不空
    //此后对入度表的更新只要跟新每次输出的那个顶点会影响到的点即可
    while(front != rear){
        //循环第一步： 出队列
        int current = queue[front++];
        //循环第二步： 输出当前顶点
        printf(" %d", current);
        //循环第三步： (相当于删除掉当前顶点)根据当前顶点，调整入度值
        for (int i = 0; i < graph->vertex; ++i) {
            if(graph->matrix[current][i]){
                indegree[i]--;
                //循环第四步： 每次入度减完1后，要检查一下这个顶点是否成为0入度，是则进队列
                if(indegree[i] == 0){
                    queue[rear++] = i;
                }
            }
        }
    }
}
/*
 * 算法改进:由于indegree数组中，某个indegree[i]为0后完全不会再使用，所以可以直接再这个数组
 * 上的0值位置实现一个栈，不必再另外设一个栈。这是用到了静态链表的思想
 * 只需top来表示栈顶的位置，原来的indegree数组中已经不再表示度数的部分，即栈的一部分了，其内容用于指示栈的移动。
 * 这是静态链表的思想。indegree这个数组不再是存粹的度数表，而是度数表占一部分，栈占一部分。
 * 每次进栈时，比如i号进栈，我们在把栈顶“指针”top移过去前，现在indegree[i]存储此时的栈顶，也就是入栈后的次栈顶。
 * 于是indegree[top]总指示着次栈顶的位置，即indegree[top]总是告诉top退栈时该去哪里，退栈时先把top位置，也就是存在栈顶的顶点，交给current做后续操作
 * 然后只需top读取并更新成indegree[top]，到了新的栈顶 (刚才的次栈顶)，位置，从而完成了退栈
 *
 *  若i要进栈，则indegree[i] = top; top = i; 先用indegree保存次顶位（当前的栈顶，待会的次顶位），top再跟上来。
 *  退栈时，indegree[i],实际上是indegree[top],可以告诉top该去哪里。改变top前还需将栈顶元素取出，因此
 *  current = top;  top = indegree[top].
 *
 *  实际上栈是不存在的，是一个静态的链表。indegree的格子是指针域，真正的"数据域"恰恰是indegree的下标，即top的值，而indegree[top]访问到的是索引，是"指针"
 *  注意这个是静态的链栈，是用链串起来的，top直接的是元素，刚好元素可以对应一个'指针域'给top
 *
 *  但是我们这个矩阵实现不好做这个优化，这个适合邻接表类型的
 */
//用拓扑排序算法可以解决有向图判断环路问题，因为环的部分是不能被生成拓扑序列的，环每个结点的入度不可能出现0，循环不下去
//因此能够被输出到的结点数一定少于总结点数。我们每次退栈做一个计数，最后拿计数与结点数一比，就知道有没有环路
//算法只需改装一下打印型的拓扑排序。
int topojudgecirclemat(graphmat * graph){
    //Step1 计算好入度
    int indegree[graph->vertex];
    makeindegreeMat(graph, indegree);

    //Step2 准备一个栈
    int stack[graph->vertex];
    int top = -1;
    int count = 0;   //为了统计被出栈的个数
    //Step3 找0入度顶点,并将其入栈
    for (int i = 0; i < graph->vertex; ++i) {
        if(indegree[i] == 0){
            stack[++top] = i;   //结点i入栈
        }
    }
    //Step4 启动循环,循环条件是栈不空
    //此后对入度表的更新只要跟新每次输出的那个顶点会影响到的点即可
    while(top != -1){
        //循环第一步： 退栈
        int current = stack[top--];
        //循环第二步： 计数
        count++;
        //循环第三步： (相当于删除掉当前顶点)根据当前顶点，调整入度值
        for (int i = 0; i < graph->vertex; ++i) {
            if(graph->matrix[current][i]){
                indegree[i]--;
                //循环第四步： 每次入度减完1后，要检查一下这个顶点是否成为0入度，是则进栈
                if(indegree[i] == 0){
                    stack[++top] = i;
                }
            }
        }
    }
    return count < graph->vertex;
}
/*
 * 总结：拓扑排序算法
 * 作用的对象和功能：把有向无环路图输出对应的拓扑序列
 * 应用： 可以用来判断有向图是否有环路，因为有环路不能被拓扑排序输出
 *        具体就是环路点不可能出现0入度
 * 代码流程
 * 第一步 准备工作：  计算好入度，准备一个栈
 * 第二步 初始化：    做第一次的0度顶点入栈
 * 第三步 主体循环：  1. 每次出栈，2. 输出该顶点，3.然后将该顶点邻接到的顶点入度减去1
 *                 4.并且马上检查减完后是否入度为0，如果是，把它进栈
 *
 *  这就可以实现
 */
//下面是关键路径算法
/*
 * 关键路径算法是有向带权AOE网络(不仅要无环，还要求有唯一源点和汇点)中使用的算法
 * 作用的效果是求出关键路径，就是完成这个工程中不可以拖延、也没有办法提早的事件活动连起来的路径。
 * 关键路径是源点到汇点的最长路径
 * 关键路径虽然是最长，但是求解它并不是最短路径的反向求法，不能每次找个最大边就说找个最大路径。
 * 求关键路径的方法其实是找关键节点。关键节点表示的是这个工程中，关键的、不可以拖延的、没办法提早的事件。
 * 找关键结点的方法：求两个时间，最早发生时间和最迟发生时间。
 * 最早发生时间好理解，最迟发生时间就是这个事件可能可以拖延，但是最迟在某个时间必须得完成，否则会影响整个工程进度
 * 最早最迟发生时间一样的，就是关键事件。而最迟发生时间和最早发生时间不一样的，说明这事件拖延一下没关系，就是非关键的。
 * 统筹安排合理，整个工程的耗时就是关键路径的长度，因此对汇结点(标志工程完成)，其最早发生时间和最迟发生时间相等，都等于工程耗时。
 * 对源结点而言，最早发生时间和最迟发生时间也一样，都是0.
 *
 * 上面是该算法涉及到的概念，下面是算法内容
 *
 * 关键路径算法的基础是拓扑排序，我们是在拓扑排序探测图的过程中，计算了每个结点的最早发生时间。
 * 同时借助一个栈，在探测到底(探测到汇点)以后从汇点回退，在回退的过程中计算每个结点的最晚发生时间。
 * 完成这个往返探测后，就得到了所有结点的最早发生时间 和最晚发生时间， 两个一样的是关键结点，依次输出他们
 *
 * 具体的实现步骤：
 * 和拓扑排差不多的框架：
 * 1 准备拓扑排序用到的工具 此外再额外准备一个栈用来储存拓扑排序探测依次遇到的点,准备一个最早时间数组和最迟时间数组
 *   要对最早发生时间做一个初始化，全部初始化成0 (源点真的是0，其他点后续都会改)
 * 2 进行拓扑排序，每次过程中不必输出，而是将当前本该输出的点入栈
 *   再对它邻接到的点入度减1的同时，要检查并更新当前点邻接到的点的最早发生时间。
 *   邻接到的点最早发生时间就是 当前点的最早发生时间 + 当前点到邻接到的点的边的长度,如果比原来的大就更新
 *   即 if(earliest[current] + 边长(current, next) > earlist[next]) earlist[next] = earliest[current] + 边长(current, next)
 *
 *   以上步骤完成后，就完成了 拓扑排序过程 和 全部点最早发生时间的计算过程。
 *   且拓扑序列存在了栈里(退栈就是逆拓扑序列)，下面要做的就是回退计算最迟发生时间
 *
 * 3 最迟发生时间全部初始化成汇点的最迟发生时间，然后每次退栈，计算当前出栈的这个节点的最迟发生时间
 *   具体方法：每次退栈(直至栈空)，依次找他的每个邻接结点，其最迟发生时间 = 邻接到的结点的最迟发生时间 - 它们间的边长
 *   我们要检查他应该是最小值，即 if(latest[next] - 边长(current, next) < latest[current])  latest[current] = latest[next] - 边长(current, next)
 *
 * 4 此时，我们就得出了所有结点的最早发生时间和最迟发生时间。然后要转换成活动的最早开始时间和最迟发生时间。
 *   每个事件点挨个检查它出发的活动是不是关键活动，判断活动最早开始时间(即事件最早发生时间) 和活动最迟开始时间(邻接到的结点事件最迟发生时间 - 活动长度)
 *
 *
 *   总结：关键路径算法的核心在于最早发生时间和最迟发生时间的计算。这个计算依托于拓扑排序的过程和逆过程依次完成。
 *   关键路径的意义：所有关键的活动都必须在其规定时间完成，工程才不会拖延。
 *   人工找关键路径：人工先求两个数组，必须抓住两个数组的含义：某点最早发生时间是源点到该点最长路径，
 *                最迟发生时间是汇点的时间 - 该点到汇点的最长路径，
 *                但是真正计算用的公式是： min{下一个点的最迟发生时间 - 它们中间这个活动的持续时间}
 *   人工求法和机器的步骤一样，先顺着求过去，再倒着求回来。要抓住其字面含义来做。
 *
 *   AOE网络中的 事件 与 活动
 *   事件：事件表示为点。  事件的发生标志着从他出发的活动的开始。
 *   活动：活动表示为边。  活动的开始时间就看它从哪个事件的点出发，这个事件的最早开始时间对应的是活动的最早开始时间。
 *        但是活动的最迟开始时间是活动终点事件的最迟开始时间减去活动的持续时间
 *   关键活动：关键路径上的边，即最早开始时间和最迟开始时间一样的活动。
 *   事件的最早发生事件VE 和事件的最迟发生时间VL  活动的最早开始事件E 和活动的最迟开始时间L
 *   关键活动是重要的。输出的时候就考虑输出全部关键活动
 *   注：定义的概念只有 事件、活动、关键活动， 好像是没有定义关键事件的，两个事件如果是关键的，不一定中间的活动是关键的
 *
 */
//最短路径算法
/*
 * 最短路径算法分dijkstra算法和Floyd算法，dijkstra算法和prim算法高度相似已经说了
 * dijkstra算法解决的是单源最短路径，是选定一个点到其他所有点的最短路径，并且两点距离必须是正的
 * Floyd算法生成的是任意两点之间的最短路径，算法思想是尝试依次绕行每一个顶点，看能否走出更短的路径，如果有就更新上去
 * floyd算法很简单，三层循环，第一层k 第二三层ij，第一层是轮换中间点，i和j是起点终点
 *
 */
void showpath(int * mid, int i, int j, int n){
    int k = mid[i*n+j];
    if(k != -1){
        showpath(mid, i, k,n);
        printf(" %d",k);
        showpath(mid,k,j,n);
    }
}
void floydmat(graphmat* graph, int start, int dest){
    int distance[graph->vertex][graph->vertex];
    int mid[graph->vertex][graph->vertex];
    for (int i = 0; i < graph->vertex; ++i) {
        for (int j = 0; j < graph->vertex; ++j) {
            mid[i][j] = -1;
            distance[i][j] = graph->matrix[i][j];
        }
    }
    //接下来是核心算法
    for (int k = 0; k < graph->vertex; ++k) {
        for (int i = 0; i < graph->vertex; ++i) {
            for (int j = 0; j < graph->vertex; ++j) {
                if(distance[i][j] > distance[i][k] + distance[k][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                    //至此，三层循环四行语句，就把任意两节点的最短路径长保存在了distance中
                    //如果想要保存任意两点之间最短路径并输出，就在设置一个二维数组，保存每一个中间点
                    mid[i][j] = k;   //表示i到j的最短路径经过k
                }
            }
        }
    }
    //下面纯输出端
    printf(" %d",start);
    showpath(*mid, start, dest,graph->vertex);
    printf(" %d   %d\n", dest,distance[start][dest]);
}
#endif //GRAPH_MATRIX_H

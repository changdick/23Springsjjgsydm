//
// Created by 83923 on 2023/4/17.
//

#ifndef MAIN_C_HUFFMANTREE_H
#define MAIN_C_HUFFMANTREE_H
#include <stdio.h>
#include <stdlib.h>
//哈夫曼树用静态链表实现
typedef struct {
    char data;
    float weight;
    int parent;
    int leftchild;
    int rightchild;
}Huffmannode;
typedef struct{
    Huffmannode * HFMtree;
    int numberofbase;
}Huffmantree;
Huffmannode * huffmanbase(int n){
    Huffmannode * HFMtree = (Huffmannode*)malloc((2 * n - 1) * sizeof(Huffmannode));
    for(int i = 0; i < n ; i++){
        scanf("%c",&HFMtree[i].data);
        scanf("%f",&HFMtree[i].weight);
        getchar();
        HFMtree[i].parent = -1;
        HFMtree[i].leftchild = -1;
        HFMtree[i].rightchild = -1;
    }
    return HFMtree;
}
void selectmin(Huffmannode* HFMtree, int index, int* minI, int * minII){
    for (int i = 0; i < index; ++i) {
        if(HFMtree[i].parent == -1){
            *minI = i;
            break;
        }
    }
    for (int i = *minI + 1; i < index; ++i) {
        if(HFMtree[i].parent == -1){
            *minII = i;
            break;
        }
    }
    for (int i = 0; i < index; ++i) {
        if(HFMtree[i].parent == -1 && i != *minII && HFMtree[i].weight < HFMtree[*minI].weight)
            *minI = i;
    }
    for (int i = 0; i < index; ++i) {
        if(HFMtree[i].parent == -1 && i != *minI && HFMtree[i].weight < HFMtree[*minII].weight)
            *minII = i;
    }
    //确保左边选的比右边小
    if(HFMtree[*minI].weight > HFMtree[*minII].weight){
        int temp = *minI;
        *minI = *minII;
        *minII = temp;
    }
}
Huffmannode * createHFMtree(int n){
    Huffmannode * HFMtree = huffmanbase(n);
    int minI,minII;
    for(int i = n; i < 2 * n -1; i++){
        selectmin(HFMtree, i , &minI, &minII);

        HFMtree[i].weight = HFMtree[minI].weight + HFMtree[minII].weight;
        HFMtree[i].parent = -1;
        HFMtree[i].leftchild = minI;
        HFMtree[i].rightchild = minII;
        HFMtree[minI].parent = i;
        HFMtree[minII].parent = i;
        HFMtree[i].data = '#';
    }
    return HFMtree;
}
void printstaticlist(Huffmannode* treelist, int n){
    for (int i = 0; i < 2*n-1; ++i) {
        printf("%d %f %d %d %d\n",i,treelist[i].weight,treelist[i].parent
        ,treelist[i].leftchild,treelist[i].rightchild);
    }
}
Huffmantree Huffmancreate(int n){
    Huffmantree tree;
    tree.numberofbase = n;
    tree.HFMtree = createHFMtree(tree.numberofbase);
    return tree;
}
void Huffmantravel(Huffmantree tree, int root){
    int leftchild = tree.HFMtree[root].leftchild;
    int rightchild = tree.HFMtree[root].rightchild;
    if(leftchild == -1){
        int stack[2*tree.numberofbase];
        int top = -1;
        printf(" \n%c ",tree.HFMtree[root].data);
        while(tree.HFMtree[root].parent != -1){
            int parent = tree.HFMtree[root].parent;
            if(tree.HFMtree[parent].leftchild == root){
                stack[++top] = 0;
            }
            if(tree.HFMtree[parent].rightchild == root){
                stack[++top] = 1;
            }
            root = parent;
        }
        while(top>-1){
            printf("%d",stack[top--]);
        }
    }
    /*
     *
     * huffmantravel用的算法：
     * 1、递归遍历找到叶子，也就是带着数据的待编码对象
     * 2、从叶子起，一直往上找父亲，并判断是左孩子还是右孩子
     * 3、设置一个栈，如果是左孩子，让0进栈，如果是右孩子，让1进栈。随后向上更新
     * 4、找到顶层后，开始退栈输出
     * 5、栈的实现：stack[]和top(栈空为-1)，stack[++top] = 0 进栈，
     *      while(top != -1)   a = stack[top--] 表示退栈，退出的元素给a
     *
     * 根本不用从头开始探到底，本来算法是抓着头，遍历探到底再回溯记录，
     * 实际上，我们一开始就知道四个终点分别是下标0到n-1，直接从终点往头找就完了
     *
     */
    else{

        Huffmantravel(tree, leftchild);

        Huffmantravel(tree, rightchild);
    }
}
//Huffmancode 的算法比上面那个Huffmantravel做了改进
//不过还是有差别，huffmantravel的算法输出会按照少到多来输出,huffmancode按照我们输入顺序输出
void Huffmancode(Huffmantree tree){
    for (int i = 0; i < tree.numberofbase; ++i) {
        printf("\n%c ",tree.HFMtree[i].data);
        int stack[2*tree.numberofbase];
        int top = -1;
        int cur = i;
        while(tree.HFMtree[cur].parent != -1){
            if( cur == tree.HFMtree[tree.HFMtree[cur].parent].leftchild )   stack[++top] = 0;
            if( cur == tree.HFMtree[tree.HFMtree[cur].parent].rightchild )   stack[++top] = 1;
            cur = tree.HFMtree[cur].parent;
        }
        while(top != -1){
            printf("%d",stack[top--]);
        }
    }
}
#endif //MAIN_C_HUFFMANTREE_H

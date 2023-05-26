//
// Created by 83923 on 2023/4/16.
//

#ifndef MAIN_C_THREADBINARYTREE_H
#define MAIN_C_THREADBINARYTREE_H
#include <stdlib.h>
#include <stdio.h>
typedef struct treadbtreenode{
    char data;
    int lefttag;
    struct treadbtreenode* leftchild;
    int righttag;
    struct treadbtreenode* rightchild;
}Threadtree;
Threadtree * trnewnode(char dataval){
    Threadtree * node = (Threadtree *)malloc(sizeof (Threadtree));
    node->data = dataval;
    node->leftchild = NULL;
    node->lefttag = 1;
    node->righttag = 1;
    node->rightchild = NULL;
    return node;
}
Threadtree * createtrtree(){
    char ch;
    //fflush(stdin);
    scanf("%c",&ch);

    Threadtree * newtree = NULL;
    if(ch == '#'){
        newtree == NULL;
    }
    else{
        newtree = trnewnode(ch);
        newtree->leftchild = createtrtree();
        newtree->rightchild = createtrtree();
    }
    return newtree;
}
Threadtree *InTreading(Threadtree* current,Threadtree* pre){
    if(current){
        pre = InTreading(current->leftchild, pre);
        if (!current->leftchild){
            current->lefttag = 0;
            current->leftchild = pre;
        }
        if(!pre->rightchild){
            pre->righttag = 0;
            pre->rightchild = current;

        }
        pre = current;
        pre = InTreading(current->rightchild,pre);

    }
    return pre;
}
Threadtree* Treadingtree(Threadtree* tree){
    //先创造头结点并初始化头结点
    Threadtree * head = (Threadtree *)malloc(sizeof (Threadtree));
    head->righttag = 1;
    head->rightchild = head;
    head->leftchild = tree;
    head->lefttag = 1;

    Threadtree * pre = head;
    pre = InTreading(tree,pre);
    pre->rightchild = head;
    pre->righttag = 0;
    return head;
}
Threadtree * Inordernext(Threadtree* node){
    if(node->righttag == 0){
        return node->rightchild;
    }
    else{
        node = node->rightchild;
        while(node->lefttag){
            node = node->leftchild;

        }
        return node;
    }
}
Threadtree * createtreadtree(){
    Threadtree * tree = createtrtree();
    tree = Treadingtree(tree);
    return tree;
}
void treadinordertravel(Threadtree* trtree){
    Threadtree * temp = trtree;
    do {
        temp = Inordernext(temp);
        printf((" %c"), temp->data);

    }while(temp != trtree );
}


#endif //MAIN_C_THREADBINARYTREE_H

//
// Created by 83923 on 2023/4/13.
//

#ifndef TREE1_BINARYTREEA_H
#define TREE1_BINARYTREEA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct BTnode{
    char data;
    struct BTnode* leftchild;
    struct BTnode* rightchild;
}Binarytree;
Binarytree* newroot(){
    Binarytree * node = (Binarytree*)malloc(sizeof (Binarytree));
    node->leftchild = NULL;
    node->rightchild = NULL;
    return node;
}
Binarytree* newnode(char dataval){
    Binarytree * node = (Binarytree*)malloc(sizeof (Binarytree));
    node->data = dataval;
    node->leftchild = NULL;
    node->rightchild = NULL;
    return node;
}
Binarytree * createtree(){
    char ch;
    //fflush(stdin);
    scanf("%c",&ch);

    Binarytree * newtree = NULL;
    if(ch == '#'){
        newtree == NULL;
    }
    else{
        newtree = newnode(ch);
        newtree->leftchild = createtree();
        newtree->rightchild = createtree();
    }
    return newtree;
}
void pretravel(Binarytree* BTree){
    if(BTree) {
        printf(" %c", BTree->data);
        pretravel(BTree->leftchild);
        pretravel(BTree->rightchild);
    }
}
void intravel(Binarytree* BTree){
    if(BTree){
        intravel(BTree->leftchild);
        printf(" %c",BTree->data);
        intravel(BTree->rightchild);
    }
}
void posttravel(Binarytree* BTree){
    if(BTree){
        intravel(BTree->leftchild);
        intravel(BTree->rightchild);
        printf(" %c",BTree->data);
    }
}
int max(int a, int b){
    if(a>=b){
        return a;
    }
    else
        return b;
}
int depthBT(Binarytree* Btree){
    if(Btree == NULL){
        return 0;
    }
    else{
        return 1 + max(depthBT(Btree->leftchild), depthBT(Btree->rightchild));
    }

}
Binarytree * copyBT(Binarytree* source){
    Binarytree * copy = NULL;
    if(source){
        copy = newroot();
        copy->data = source->data;
        copy->leftchild = copyBT(source->leftchild);
        copy->rightchild = copyBT(source->rightchild);
    }
    return copy;
}
int equalBT(Binarytree* treeA, Binarytree* treeB){
    if(treeA == NULL && treeB == NULL){
        return 1;
    }
    if(treeA && treeB){
        return (treeA->data == treeB->data ) && equalBT(treeA->leftchild, treeB->leftchild) && equalBT(treeA->rightchild, treeB->rightchild);
    }
    else{
        return 0;
    }
}
//判断是不是叶子:叶子的深度（高）为1
int isleaf(Binarytree* tree){
    return depthBT(tree) == 1;
}
//这个函数是稍微修改过的intravel(),用于表达式中缀输出加一下括号
//为了区分根节点才多设了一个flag参数，不这样做也无所谓就是整个表达式外面多一对括号，不想要这对括号就穿非零参数给flag
void Inorderexpressionprint(Binarytree* expressiontree, int rootflag){
    if(expressiontree){
        if(!isleaf(expressiontree)&&!rootflag){
            printf("(");
        }
        Inorderexpressionprint(expressiontree->leftchild,0);

        printf(" %c",expressiontree->data);

        Inorderexpressionprint(expressiontree->rightchild, 0);
        if(!isleaf(expressiontree)&&!rootflag){
            printf(")");
        }
    }
}

#endif //TREE1_BINARYTREEA_H

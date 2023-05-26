#include <stdio.h>

#include "queue.h"
#include "huffmantree.h"
#include "threadbinarytree.h"
void cctravle(Binarytree* BTree){
    Queue  * queue = createnewqueue();
    enqueue(queue,BTree);
    while(!queueempty(queue)){
        Binarytree * current = dequeue(queue);
        printf(" %c",current->data);
        if(current->leftchild)    enqueue(queue,current->leftchild);
        if(current->rightchild) enqueue(queue,current->rightchild);
    }
}
int main() {

    //Binarytree * BTa = createtree();
    //pretravel(BTa);
  // printf("\n");
   // Inorderexpressionprint(BTa,1);
    //intravel(BTa);
  // printf("\n");
  //  posttravel(BTa);
    //printf("\n");
   // cctravle(BTa);
  // printf("\n");
    //fflush(stdin);
   // Threadtree * thtreea = createtreadtree();
    //treadinordertravel(thtreea);
    //printf("\n depth of tree is %d", depthBT(BTa));
    //Binarytree * BTb = copyBT(BTa);
    //intravel(BTb);
    //printf("\n%d", equalBT(BTa,BTb));


     //测试哈夫曼树用的代码
    Huffmantree HFMtree = Huffmancreate(8);
    printf("\n");
    //printstaticlist(HFMtree.HFMtree, HFMtree.numberofbase);
    //Huffmantravel(HFMtree, HFMtree.numberofbase * 2 - 2);
    Huffmancode(HFMtree);
    return 0;
}

//
// Created by 83923 on 2023/5/26.
//

#ifndef MAIN_C_KMP_H
#define MAIN_C_KMP_H
#include <stdio.h>
#include <stdlib.h>
int kmpcore(char* s, char*t, int next[]){
    int index = 0, i = 0, j = 0;  
    while(s[i]!='\0' && t[j]!='\0'){
        if(s[i] == t[j]){
            i++;
            j++;
        }
        else{
            if(next[j]==-1){
                i++;    
                j = 0;
                index = i;  
            }
            else{
                j = next[j];

                index = i - j;  
            }

        }

    }
    if(t[j] == '\0'){
        return index;  
    }
    else
        return -1;  
}
void getnextI(char * t, int next[]){
    int k = -1, j = 0;
    next[j] = -1; 
     while(t[j]!='\0'){
        if(k == -1 || t[j] == t[k]){
            j++;
            k++;
            next[j] = k;
        }
        else{
            k = next[k];
        }
     }
}
void getnextII(char * t, int next[]){
    int k = -1, j = 0;
    next[j] = -1; 
     while(t[j]!='\0'){
        if(k == -1 || t[j] == t[k]){
            j++;
            k++;
            if(t[j]!=t[k])
                next[j] = k;
            else
                next[j] = next[k];
        }
        else{
            k = next[k];
        }
     }
}
int kmp(char*s, char*t){
    char next[100];
    getnextI(t,next);   //或 getnextII(t, next);
    int ret = kmpcore(s,t,next);
    return ret;
}
#endif //MAIN_C_KMP_H

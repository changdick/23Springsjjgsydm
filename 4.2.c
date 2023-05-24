#include <stdio.h>
#include <stdlib.h>

typedef struct student{
    int Code;
    int Score[5];
    int jiaquanzongfen;
} Student;

typedef struct rank{
    int Rank;
    int Code;
}Rank;
/*
 * struct rank是学生的排名和学号，rank[i]存储第i个学生的信息
 * Student 是学生的学号和5科成绩 rank和Student 里的学号是一样的
 * 已经处理好的输入，我们会拿到一个输入好的Students数组，已经存好了每个学生的成绩和0到4共5科成绩
 * 两个整型数组Priority和Weight 是对应的存储0-4这五个科目的优先级和权重
 * 先比权重后比优先级
 *
 */
Student Students[50];
Rank 	Ranks[50];

int 	Priority[5];
double 	Weight[5];
int 	N;    //成绩数据条数
int xuekexuhaobasedonpriority[6];

void jisuanjiaquanzongfen(){
    for (int i = 0; i < N; ++i) {
        double sum = 0;
        for (int j = 0; j < 5; ++j) {
            sum = sum + Students[i].Score[j] * Weight[j];
            Students[i].jiaquanzongfen = sum;
        }
    }
}
void writexuekexuhaobasedonpriority(){
    for (int i = 1; i < 6; ++i) {
        for (int j = 0; j < 5; ++j) {
            if(Priority[j] == i){
                xuekexuhaobasedonpriority[i] = j;
            }
        }
    }
}
void sortarreyStudentsbyjiaquanzongfen(){
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N-1; ++j) {
            if(Students[j].jiaquanzongfen < Students[j+1].jiaquanzongfen){
                Student temp = Students[j];
                Students[j] = Students[j+1];
                Students[j+1] = temp;  //完成交换
            }
        }
    }
}
void sortarreyStudentsbasedonPriorityandcode(){

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N-1; ++j) {
            if(Students[j].jiaquanzongfen == Students[j+1].jiaquanzongfen){
                for (int k = 1; k <= 5; ++k) {
                    if(Students[j].Score[xuekexuhaobasedonpriority[k]] > Students[j+1].Score[xuekexuhaobasedonpriority[k]]){
                        break;
                    }
                    if(Students[j].Score[xuekexuhaobasedonpriority[k]] < Students[j+1].Score[xuekexuhaobasedonpriority[k]]){
                        Student temp = Students[j];
                        Students[j] = Students[j+1];
                        Students[j+1] = temp;  //完成交换
                        break;
                    }
                    if(Students[j].Score[xuekexuhaobasedonpriority[k]] == Students[j+1].Score[xuekexuhaobasedonpriority[k]] && k == 5){

                        if(Students[j].Code > Students[j+1].Code){
                            Student temp = Students[j];
                            Students[j] = Students[j+1];
                            Students[j+1] = temp;  //完成交换
                        }
                    }
                }
            }
        }
    }
}
void jianchapaimingshifouzhengfquebingiexiuzhengpaiming(){
    for (int i = 1; i < N ; ++i) {
        for (int j = 0; j < 5; ++j) {
            if(Students[i].Score[j] != Students[i-1].Score[j]) break;
            if(j == 4){
                Ranks[i].Rank = Ranks[i-1].Rank;
            }
        }
    }
}
void CalcAndWriteRanks(){
    jisuanjiaquanzongfen();
    sortarreyStudentsbyjiaquanzongfen();
    writexuekexuhaobasedonpriority();
    sortarreyStudentsbasedonPriorityandcode();
    for (int i = 0; i < N; ++i) {
        Ranks[i].Code = Students[i].Code;
        Ranks[i].Rank = i+1;
    }
    jianchapaimingshifouzhengfquebingiexiuzhengpaiming();
}

void PrintRanks(){
    for (int loop = 0; loop < N; loop++){
        printf("%d %d\n", Ranks[loop].Rank, Ranks[loop].Code);
    }
}

int main(int argc, char *argv[]) {
    // Input part, do not modify
    scanf("%d", &N);
    for (int loop = 0; loop < 5; loop++){
        scanf("%d", Priority + loop);
    }
    for (int loop = 0; loop < 5; loop++){
        scanf("%lf", Weight + loop);
    }

    for (int loop = 0; loop < N; loop++){
        scanf("%d", &Students[loop].Code);
        for (int j = 0; j < 5; j++){
            scanf("%d", Students[loop].Score + j);
        }
    }
    // Main process part
    CalcAndWriteRanks();
    // Output part, do not modify
    PrintRanks();
    return 0;
}
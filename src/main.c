#include "main.h"
#include "System.h"
#include "Scanner.h"
#include "Calculator.h"

import SYSTEM System;

#define OPERATOR(X) !(X - 3) ? '/' : !(X - 1) ? '-' : !(X - 2) ? '*' : '+'

typedef struct _Problem{
    double* nums;
    char op;
}Problem;

boolean start = false;
Problem problem;
uint8_t level = 0;
uint64_t score = 0;
double answer;
Scanner sc;
Calculator calculator;

unsigned _stdcall Theead_Timmer(void*);

void init(){
    sc = new_Scanner(System.in);
    calculator = new_Calculator();
    problem.nums = (double*)malloc(sizeof(double) * 2);
    srand(time(NULL));
    _beginthreadex(NULL, 0, Theead_Timmer, NULL, 0, NULL);
}

void getProblem(){
    problem.op = (char)OPERATOR(rand() % 5);
    problem.nums[0] = (double)(rand() % 10);
    problem.nums[1] = (double)(rand() % 10);
}

void startGame(){
}

int main(void){
    init();

    while(true){

    }
    System.out.print("%g %c %g = ", problem.nums[0], problem.op, problem.nums[1]);
    answer = sc.nextInt();

    if(answer == floor((calculator.calculate(problem.nums[0], problem.nums[1], problem.op) * 100) / 100))
        System.out.println("O");
    else
        System.out.println("X");


    free(problem.nums);
    return 0;
}

unsigned _stdcall Theead_Timmer(void* arg){
    while(true){
    
    }
}
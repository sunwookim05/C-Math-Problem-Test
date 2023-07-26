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

typedef struct _Time{
    uint8_t ms;
    uint8_t minute;
    uint8_t second;
}Time;

typedef struct _Pos{
    short x;
    short y;
}Pos;

int sts;
void** re;
boolean isStart = false;
Problem problem;
Time timer;
uint8_t level = 0;
int8_t score = 0;
double answer;
Scanner sc;
Calculator calculator;

unsigned _stdcall Theead_Timmer(void*);

void init(){
    sc = new_Scanner(System.in);
    calculator = new_Calculator();
    problem.nums = (double*)malloc(sizeof(double) * 2);
    srand(time(NULL));
    _beginthreadex(null, 0, Theead_Timmer, null, 0, &sts);
    system("cls");
}

void gotoxy(Pos po){
    COORD pos = {po.x, po.y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void getProblem(){
    problem.op = (char)OPERATOR(rand() % 5);
    problem.nums[0] = (double)(rand() % 10);
    problem.nums[1] = (double)(rand() % 10);
}

void lineClear(Pos po, int length){
    gotoxy(po);
    for(int i = 0; i < length; i++) System.out.print(" ");
}

void startGame(){
    System.out.println("This is a math game.");
    System.out.println("You can only express up to two decimal places.");
    System.out.println("If you want to start, press any key.");
    system("pause");
    isStart = true;
}

void gameOver(){
    isStart = false;
    Sleep(20);
    system("cls");
    System.out.println("Game Over");
    System.out.println("Your level is %d", level);
    System.out.println("Your time is %02d:%02d:%02d", timer.minute, timer.second, timer.ms);
    system("pause");
    system("cls");
}

int main(void){
    startGame();
    init();

    while(isStart){
        getProblem();
        lineClear((Pos){1, 0}, 80);
        lineClear((Pos){1, 1}, 80);
        gotoxy((Pos){1, 0});
        System.out.print("Score:%03d Level:%03d ", score, level);
        gotoxy((Pos){1, 1});
        System.out.print("%g %c %g = ", problem.nums[0], problem.op, problem.nums[1]);
        answer = sc.nextInt();
        if(answer == floor((calculator.calculate(problem.nums[0], problem.nums[1], problem.op) * 100) / 100)) score += 10;
        else score -= 5;
        if(score >= 100){
            level++;
            score -= 100;
        }
        if(score < 0) gameOver();
    }

    free(problem.nums);
    return 0;
}

unsigned _stdcall Theead_Timmer(void* arg){
    while(isStart){
        Sleep(10);
        timer.ms += 1;
        if(timer.ms == 100){
            timer.ms = 0;
            timer.second++;
            if(timer.second == 60){
                timer.second = 0;
                timer.minute++;
            }
        }
        gotoxy((Pos){21, 0});
        System.out.print("Time:%02d:%02d:%02d", timer.minute, timer.second, timer.ms);
        gotoxy((Pos){0, 0});
    }
}
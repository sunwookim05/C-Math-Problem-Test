#include "main.h"
#include "System.h"
#include "Scanner.h"
#include "Calculator.h"

import SYSTEM System;

#define OPERATOR(X) !(X - 3) ? '/' : !(X - 1) ? '-' : !(X - 2) ? '*' : '+'

typedef struct _Problem{
    double* nums;
    char op;
    String str;
}Problem;

typedef struct _Time{
    uint8_t ms;
    uint8_t minute;
    uint8_t second;
}Time;

boolean isStart = false;
Problem problem;
Time timer;
uint8_t level = 0;
int8_t score = 0;
double answer;
Scanner sc;
Calculator calculator;
String buf;

char c;
uint16_t i = 0;

unsigned _stdcall Timmer(void*);
unsigned _stdcall UserInterFace(void*);

void init(){
    sc = new_Scanner(System.in);
    calculator = new_Calculator();
    problem.nums = (double*)malloc(sizeof(double) * 2);
    problem.str = (String)calloc(0, sizeof(char) * 1);
    buf = (String)calloc(0, sizeof(char) * 5);
    srand(time(NULL));
    _beginthreadex(null, 0, Timmer, null, 0, null);
    _beginthreadex(null, 0, UserInterFace, null, 0, null);
    system("cls");
}

void gotoxy(COORD pos){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void getProblem(){
    problem.op = (char)OPERATOR(rand() % 5);
    problem.nums[0] = (double)(rand() % 10);
    problem.nums[1] = (double)(rand() % 10);
}

void lineClear(COORD pos, int length){
    gotoxy(pos);
    for(int i = 0; i < length; i++) System.out.print(" ");
}

void startGame(){
    System.out.println("This is a math game.");
    System.out.println("You can only express up to two decimal places.");
    System.out.println("If you want to start, press any key.");
    getchar();
    isStart = true;
}

void gameOver(){
    isStart = false;
    Sleep(20);
    system("cls");
    System.out.println("Game Over");
    System.out.println("Your level is %d", level);
    System.out.println("Your time is %02d:%02d:%02d", timer.minute, timer.second, timer.ms);
    System.out.println("If you want to out, press any key.");
    getchar();
    system("cls");
}

int main(void){
    startGame();
    init();

    while(isStart){
        i = 0;
        sprintf(buf, "\0\0\0\0\0");
        getProblem();
        while (i < 5 - 1 & (c = fgetc(stdin)) != EOF & c != '\n') {
            sprintf(buf, "%s%c",buf, c);
            problem.str[i++] = c;
            problem.str = (String)realloc(problem.str, sizeof(char) * (i + 1));
            problem.str[i] = '\0';
        }
        answer = atof(problem.str);
        if(answer == floor((calculator.calculate(problem.nums[0], problem.nums[1], problem.op) * 100) / 100)) score += 10;
        else score -= 5;
        if(score >= 100){
            level++;
            score -= 100;
        }
        if(score < 0) gameOver();
    }

    free(buf);
    free(problem.str);
    free(problem.nums);
    return 0;
}

unsigned _stdcall Timmer(void* arg){
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
    }
}

unsigned _stdcall UserInterFace(void* arg){
    while(isStart){
        Sleep(5);
        lineClear((COORD){0, 1}, 15);
        gotoxy((COORD){0, 0});
        System.out.print("Score:%03d Level:%03d ", score, level);
        gotoxy((COORD){21, 0});
        System.out.print("Time:%02d:%02d:%02d", timer.minute, timer.second, timer.ms);
        gotoxy((COORD){1, 1});
        System.out.print("%g %c %g = %s", problem.nums[0], problem.op, problem.nums[1], buf);
        gotoxy((COORD){9, 1});
    }
}
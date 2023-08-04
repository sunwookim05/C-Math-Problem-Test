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

boolean inPut = false;
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

void printlnXY(COORD pos, const String format, ...){
    va_list ap;
    char buffer[4096];
    va_start(ap, format);
    vsprintf(buffer, format, ap);
    va_end(ap);
    gotoxy(pos);
    System.out.println(buffer);
}

void getProblem(){
    problem.op = (char)OPERATOR(rand() % 4);
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
        memset(buf, 0, sizeof(char) * 5);
        getProblem();
        while (i < 5 - 1 & (c = fgetc(stdin)) != EOF & c != '\n') {
            inPut = true;
            buf[i++] = c;
            buf = (String)realloc(buf, sizeof(char) * (i + 1));
            buf[i] = '\0';
            inPut = false;
        }
        answer = atof(buf);
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
        problem.str = buf;
        lineClear((COORD){0, 1}, 15);
        printlnXY((COORD){1, 0}, "Score:%03d Level:%03d ", score, level);
        printlnXY((COORD){21, 0}, "Time:%02d:%02d:%02d", timer.minute, timer.second, timer.ms);
        printlnXY((COORD){1, 1}, "%g %c %g = %s", problem.nums[0], problem.op, problem.nums[1], problem.str);
        gotoxy((COORD){0, 1});
    }
}
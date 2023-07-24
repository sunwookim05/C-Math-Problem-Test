#include "main.h"
#include "Calculator.h"

void setUpPublic(Calculator *this){
    import double calculate(double, double, char);

    this->calculate = calculate;
}

void setUpPrivate(Calculator *this){
    import double plus(double, double);
    import double minus(double, double);
    import double multiply(double, double);
    import double divide(double, double);
    import double modd(double, double);
    import double poww(double, double);
    
    this->plus = plus;
    this->minus = minus;
    this->multiply = multiply;
    this->divide = divide;
    this->mod = modd;
    this->pow = poww;
}

double plus(double a, double b){
    return a + b;
}

double minus(double a, double b){
    return a - b;
}

double multiply(double a, double b){
    return a * b;
}

double divide(double a, double b){
    return a / b;
}

double modd(double a, double b){
    return ((int64_t)a) % ((int64_t)b);
}

double poww(double a, double b){
    double result = a; 
    if(b == 0) 
        return 1;
    else if(a == 0) 
        return 0; 
    else 
        for(int i = 0; i < (b - 1); i++) 
            result *= a; 
    return result;
}

double calculate(double a, double b, char op){
    Calculator this = new_Calculator();
    setUpPrivate(&this);
    switch(op){
        case '+': return this.plus(a, b);
        case '-': return this.minus(a, b);
        case '*': return this.multiply(a, b);
        case '/': return this.divide(a, b);
        case '%': return this.mod(a, b);
        case '^': return this.pow(a, b);
        default: return 0;
    }
}

Calculator new_Calculator(){
    Calculator this;
    setUpPublic(&this);
    return this;
}
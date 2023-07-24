#include "main.h"

#pragma once
#ifndef __CALCULATOR_H
#define __CALCULATOR_H

#pragma pack(push, 1)
/** 
 * @brief Calculator class
 */
typedef struct _Calculator{
    /**
     * @brief Calculate
     * @param a
     * @param b
     * @param op
     * @return result
     */
    double (*calculate)(double, double, char);
    /**
     * @brief Add
     * @param a
     * @param b
     * @return result
     */
    double (*plus)(double, double);
    /**
     * @brief Subtract
     * @param a
     * @param b
     * @return result
     */
    double (*minus)(double, double);
    /**
     * @brief Multiply
     * @param a
     * @param b
     * @return result
     */
    double (*multiply)(double, double);
    /**
     * @brief Divide
     * @param a
     * @param b
     * @return result
     */
    double (*divide)(double, double);
    /**
     * @brief Modulus
     * @param a
     * @param b
     * @return result
     */
    double (*mod)(double, double);
    /**
     * @brief Power
     * @param a
     * @param b
     * @return result
     */
    double (*pow)(double, double);
    struct _Calculator *this;
}Calculator;
#pragma pack(pop)

/**
 * @brief Create a new Calculator object
 * @return Calculator 
 */
Calculator new_Calculator();

#pragma warning(pop)
#endif
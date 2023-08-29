#include "calc_support.h"

int operatorCheck(funcType opType) {
    int res = 0;

    if (opType == plus_t || opType == minus_t || opType == div_tt ||
        opType == mult_t || opType == pow_t || opType == mod_t) {
        res = 1;
    }
    return res;
}

int functionCheck(funcType function) {
    int res = 0;

    if (function == cos_t || function == sin_t || function == tan_t ||
        function == atan_t || function == asin_t || function == acos_t ||
        function == sqrt_t || function == log_t || function == ln_t) {
        res = 1;
    }

    return res;
}

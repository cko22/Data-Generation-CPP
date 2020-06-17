//
// Created by Owner on 14/6/2020.
//

#include "trapezoidalMethod.hpp"
#include <vector>
double trapezoidalMethod(std::vector<double> x, std::vector<double> y) {
    double answer = 0.0;
    for (int i{1}; x.size() > i; ++i){
        answer += 0.5*(x[i]-x[i-1])*(y[i-1]+y[i]);
    }
    return answer;
}
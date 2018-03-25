#ifndef SECANT_H
#define SECANT_H

#include <iostream>
#include <string>
#include<cmath>
#include<vector>
#include "Functions.h"


double secant(const RealFunction& slice, double x1, double x2, int maxIter, double tol);


#endif

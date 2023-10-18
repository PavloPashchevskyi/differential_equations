#ifndef DIFFEQU_HPP
#define DIFFEQU_HPP

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef double (*FUNCNARGSPTR)(double, double,...);

class DiffEqu {
 private:
  double xBegin, xEnd, xStep;
  double (*equation)(double, double,...);
  unsigned derivativeOrder;
  double *initialConditions;
  const static double accuracy;
 public:
  DiffEqu(FUNCNARGSPTR equ, double *ic, double xb, double xe, double h = 0.1, unsigned derivativeOrder = 1) {
   if (h < DiffEqu::accuracy) {
    printf("Differential equation error: step must be non-zero\n");
    exit(-1);
   }
   xBegin = xb;
   if (xe < xBegin) {
    double t = xe;
    xe = xBegin;
    xBegin = xe;
   }
   xEnd = xe;
   if (h < 0) {
    h = fabs(h);
   }
   xStep = h;
   equation = equ;
   if (derivativeOrder < 1 || derivativeOrder > 5) {
    printf("Differential equation error: allowed derivative order is from 1 to 5\n");
    exit(-1);
   }
   this->derivativeOrder = derivativeOrder;
   unsigned icClausesQ = derivativeOrder + 1;
   initialConditions = new double [icClausesQ];
   for (unsigned i = 0; i < icClausesQ; i++) {
    initialConditions[i] = ic[i];
   }
  }
  DiffEqu(const DiffEqu &right) {
   this->xBegin = right.xBegin;
   this->xEnd = right.xEnd;
   this->xStep = right.xStep;
   this->equation = right.equation;
   this->derivativeOrder = right.derivativeOrder;
   unsigned icClausesQ = this->derivativeOrder + 1;
   this->initialConditions = new double [icClausesQ];
   for(unsigned i = 0; i < icClausesQ; i++) {
    this->initialConditions[i] = right.initialConditions[i];
   }
  }
  DiffEqu& operator =(const DiffEqu &right) {
   if (initialConditions != NULL) {
    delete [] initialConditions;
   }
   xBegin = right.xBegin;
   xEnd = right.xEnd;
   xStep = right.xStep;
   equation = right.equation;
   derivativeOrder = right.derivativeOrder;
   unsigned icClausesQ = this->derivativeOrder + 1;
   initialConditions = new double [icClausesQ];
   for(unsigned i = 0; i < icClausesQ; i++) {
    initialConditions[i] = right.initialConditions[i];
   }
   return *this;
  }
  double getXBegin() {
   return xBegin;
  }
  void setXBegin(double xb) {
   if (xb > xEnd) {
    double t = xb;
    xb = xEnd;
    xEnd = t;
   }
   xBegin = xb;
  }
  double getXEnd() {
   return xEnd;
  }
  void setXEnd(double xe) {
   if (xe < xBegin) {
    double t = xe;
    xe = xBegin;
    xBegin = t;
   }
   xEnd = xe;
  }
  double getXStep() {
   return xStep;
  }
  void setXStep(double step) {
   if (step < DiffEqu::accuracy) {
    printf("Differential equation error: step must be non-zero\n");
    exit(-1);
   }
   xStep = step;
  }
  double* getInitialConditions() {
   return initialConditions;
  }
  void getInitialCondition(unsigned i, double &x, double &y) {
   x = initialConditions[0];
   y = initialConditions[i + 1];
  }
  void setInitialConditions(double *ics) {
   for (unsigned i = 0; i < derivativeOrder + 1; i++) {
    initialConditions[i] = ics[i];
   }
  }
  void setInitialCondition(unsigned i, double x, double y) {
   if (i > 4) {
    printf("Differential equation error: initial condition %d is absent\n",i);
    exit(-1);
   }
   initialConditions[0] = x;
   initialConditions[i + 1] = y;
  }
  FUNCNARGSPTR getEquation() {
   return equation;
  }
  void setEquation(FUNCNARGSPTR equ) {
   equation = equ;
  }
  unsigned getDerivativeOrder() {
   return derivativeOrder;
  }
  void setDerivativeOrder(unsigned derivativeOrder) {
   if (derivativeOrder < 1 || derivativeOrder > 5) {
    printf("Differential equation error: allowed derivative order is from 1 to 5\n");
    exit(-1);
   }
   this->derivativeOrder = derivativeOrder;
  }
  ~DiffEqu() {
   delete [] initialConditions;
  }
};

const double DiffEqu::accuracy = 0.000001;

#endif
#ifndef DEMETHOD_HPP
#define DEMETHOD_HPP

#include <string.h>
#include <conio.h>

#include "DIFFEQU.HPP"

class DEMethod {
 protected:
  DiffEqu *differentialEquation;
  double *X, *Y, yStep;
  unsigned pointsQuantity;

  virtual double calculateDeltaY(unsigned i) = 0;

 public:
  DEMethod(DiffEqu *de) {
   differentialEquation = de;
   yStep = differentialEquation->getXStep();
  }
  DEMethod(const DEMethod &right) {
   this->differentialEquation = right.differentialEquation;
   this->yStep = right.yStep;
   this->pointsQuantity = right.pointsQuantity;
   this->X = new double [pointsQuantity];
   this->Y = new double [pointsQuantity];
   for (unsigned i = 0; i < pointsQuantity; i++) {
    this->X[i] = right.X[i];
    this->Y[i] = right.Y[i];
   }
  }
  DEMethod& operator =(const DEMethod &right) {
   if (differentialEquation != NULL) {
    delete differentialEquation;
   }
   if (X != NULL) {
    delete [] X;
   }
   if (Y != NULL) {
    delete [] Y;
   }
   this->differentialEquation = right.differentialEquation;
   this->yStep = right.yStep;
   this->pointsQuantity = right.pointsQuantity;
   this->X = new double [pointsQuantity];
   this->Y = new double [pointsQuantity];
   for (unsigned i = 0; i < pointsQuantity; i++) {
    this->X[i] = right.X[i];
    this->Y[i] = right.Y[i];
   }
   return *this;
  }
  void addPoint(double x, double y) {
   double *newXs = new double[pointsQuantity + 1];
   double *newYs = new double[pointsQuantity + 1];
   for (unsigned i = 0; i < pointsQuantity; i++) {
    newXs[i] = X[i];
    newYs[i] = Y[i];
   }
   if (X != NULL) {
    delete [] X;
   }
   if (Y != NULL) {
    delete [] Y;
   }
   newXs[pointsQuantity] = x;
   newYs[pointsQuantity] = y;
   X = newXs;
   Y = newYs;
   pointsQuantity++;
  }
  void slice(unsigned from, unsigned count, double **x, double **y) {
   *x = new double [count];
   *y = new double [count];
   for (unsigned i = 0; i < count; i++) {
    *(*x + i) = X[from + i];
    *(*y + i) = Y[from + i];
   }
  }
  char* output() {
   char *result, temp[50];
   strcpy(temp, "");
   result = new char[68 * pointsQuantity + 38];
   FUNCNARGSPTR f = differentialEquation->getEquation();
   strcpy(result, "");
   strcat(result, "i   X[i]      Y[i]     f(X[i], Y[i])\n");
   for (unsigned i = 0; i < pointsQuantity; i++) {
    sprintf(temp, "%d %f %f %f\n", i, X[i], Y[i], f(X[i], Y[i]));
    strcat(result, temp);
   }
   return result;
  }
  unsigned getPointsQuantity() {
   return pointsQuantity;
  }
  double* getX() {
   return X;
  }
  double* getY() {
   return Y;
  }
  double getYStep() {
   return yStep;
  }
  void setYStep(double step) {
   yStep = step;
  }
  virtual void resolve() = 0;
  virtual ~DEMethod() {
   delete differentialEquation;
  };
};

#endif
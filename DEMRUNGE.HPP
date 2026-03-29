#ifndef DEMRUNGE_HPP
#define DEMRUNGE_HPP

#include "DEMETHOD.HPP"

class DEMRunge : public DEMethod {
 private:
  double* calculateK(unsigned i) {
   double h = yStep;
   double (*f)(double, double,...) = differentialEquation->getEquation();
   double *K = new double [4];
   K[0] = h * f(X[i], Y[i]);
   K[1] = h * f(X[i] + h / 2., Y[i] + K[0] / 2.);
   K[2] = h * f(X[i] + h / 2., Y[i] + K[1] / 2.);
   K[3] = h * f(X[i] + h, Y[i] + K[2]);

   return K;
  }
  unsigned isErrorPermissible() {
   double *K = calculateK(1);
   double FI = fabs((K[1] - K[2]) / (K[0] - K[1]));
   delete [] K;

   return (FI < 0.026);
  }
 protected:
  double calculateDeltaY(unsigned i) {
   double h = yStep;
   double (*f)(double, double...) = differentialEquation->getEquation();
   double *K = calculateK(i);
   double deltaY = (K[0] + 2 * K[1] + 2 * K[2] + K[3]) / 6.;

   delete [] K;

   return deltaY;
  }
 public:
  DEMRunge(DiffEqu *de) : DEMethod(de) {
  }
  DEMRunge(const DEMethod &right) : DEMethod(right) {
  }
  DEMRunge& operator =(const DEMethod &right) {
   DEMethod::operator =(right);
   return *this;
  }
  void resolve() {
   double x, y;
   double FI;
   do {
    double h = differentialEquation->getXBegin();
    unsigned i = 0;
    while (h <= differentialEquation->getXEnd()) {
     h += differentialEquation->getXStep();
     i++;
    }
    pointsQuantity = i;
    X = new double [pointsQuantity];
    Y = new double [pointsQuantity];
    differentialEquation->getInitialCondition(0, x, y);
    X[0] = x;
    Y[0] = y;
    for (i = 1; i < pointsQuantity; i++) {
     X[i] = differentialEquation->getXBegin() + i * differentialEquation->getXStep();
     double deltaY = calculateDeltaY(i - 1);
     Y[i] = Y[i - 1] + deltaY;
    }
    if (!isErrorPermissible()) {
     differentialEquation->setXStep(differentialEquation->getXStep() / 2.);
     yStep = differentialEquation->getXStep();
     delete [] Y;
     delete [] X;
    }
   } while (!isErrorPermissible());
  }
  ~DEMRunge() {
  }
};

#endif
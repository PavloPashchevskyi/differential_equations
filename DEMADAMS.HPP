#ifndef DEMADAMA_HPP
#define DEMADAMS_HPP

#include "DEMETHOD.HPP"

class DEMAdams : public DEMethod {
 private:
  static const unsigned prevPointsQuantity;
 protected:
  double calculateDeltaY(unsigned i) {
   if (i < 3) {
    printf("Minimum 3 pre-solutions are required for Adams method.\n");
    exit(-1);
   }
   double h = yStep;
   double (*f)(double, double,...) = differentialEquation->getEquation();
   return (h / 24.) * (55 * f(X[i], Y[i]) - 59 * f(X[i - 1], Y[i - 1]) + 37 * f(X[i - 2], Y[i - 2]) - 9 * f(X[i - 3], Y[i - 3]));
  }
  double correctDeltaY(unsigned i, double assumedX, double assumedY) {
   if (i < 2) {
    printf("Minimum 2 pre-solutions are required to correct Adams method.\n");
    exit(-1);
   }
   double h = yStep;
   double (*f)(double, double,...) = differentialEquation->getEquation();
   return (h / 24.) * (9 * f(assumedX, assumedY) + 19 * f(X[i], Y[i]) - 5 * f(X[i - 1], Y[i - 1]) + f(X[i - 2], Y[i - 2]));
  }
 public:
  DEMAdams(DiffEqu *de, double *preX, double *preY) : DEMethod(de) {
   pointsQuantity = DEMAdams::prevPointsQuantity;
   if (X != NULL) {
    delete [] X;
   }
   if (Y != NULL) {
    delete [] Y;
   }
   X = new double [pointsQuantity];
   Y = new double [pointsQuantity];
   double (*f)(double, double,...) = differentialEquation->getEquation();
   for (unsigned i = 0; i < pointsQuantity; i++) {
    X[i] = preX[i];
    Y[i] = preY[i];
   }
  }
  DEMAdams(const DEMAdams &right) : DEMethod(right) {
  }
  DEMAdams& operator =(const DEMAdams &right) {
   DEMethod::operator =(right);
   return *this;
  }
  void resolve() {
   unsigned i = DEMAdams::prevPointsQuantity;
   double h = differentialEquation->getXBegin() + i * differentialEquation->getXStep();
   while (h <= differentialEquation->getXEnd()) {
    h += differentialEquation->getXStep();
    i++;
   }
   pointsQuantity = i;
   double *newXs = new double [pointsQuantity];
   double *newYs = new double [pointsQuantity];
   for (i = 0; i < DEMAdams::prevPointsQuantity; i++) {
    newXs[i] = X[i];
    newYs[i] = Y[i];
   }
   delete [] X;
   delete [] Y;
   X = newXs;
   Y = newYs;
   double deltaY, correctedDeltaY;
   for (i = DEMAdams::prevPointsQuantity; i < pointsQuantity; i++) {
    X[i] = differentialEquation->getXBegin() + i * differentialEquation->getXStep();
    deltaY = calculateDeltaY(i - 1);
    Y[i] = Y[i - 1] + deltaY;
    correctedDeltaY = correctDeltaY(i - 1, X[i], Y[i]);
    Y[i] = Y[i - 1] + correctedDeltaY;
   }
  }
  ~DEMAdams() {
  }
};

const unsigned DEMAdams::prevPointsQuantity = 4;

#endif
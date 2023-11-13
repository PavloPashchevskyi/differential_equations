#ifndef DEREADER_HPP
#define DEREADER_HPP

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../INTERPOL/IFUSAGE.HPP"

double* convertXsArrayToSet(unsigned n, double *X, unsigned *dvq = NULL) {
 const double accuracy = 0.000001;
 *dvq = 0;
 for (unsigned i = 1; i < n; i++) {
  if (fabs(X[i] - X[0]) < accuracy) {
   *dvq = i;
   break;
  }
 }
 double *result = new double [*dvq];
 for (i = 0; i < *dvq; i++) {
  result[i] = X[i];
 }
 return result;
}

double* convertYsArrayToSet(unsigned n, double *Y, unsigned *rvq = NULL) {
 const double accuracy = 0.000001;
 *rvq = 0;
 for (unsigned i = 0; i < n; i++) {
  if (fabs(Y[i] - Y[0]) >= accuracy) {
   *rvq = i;
   break;
  }
 }
 double *result = new double [*rvq];
 unsigned k = 0;
 for (i = 0; i < n; i += *rvq) {
  result[k] = Y[i];
  k++;
 }
 return result;
}

double* convertDoublePointerToSingle(unsigned m, unsigned n, double **X) {
 double *result = new double[m*n];
 for (unsigned i = 0; i < m; i++) {
  for (unsigned j = 0; j < n; j++) {
   *(result+i*n+j) = X[i][j];
  }
 }
 return result;
}

double interpolateAbsent(
 unsigned order,
 unsigned rowsQty,
 double *X,
 double *Y,
 double *results,
 double *x
 ) {
 unsigned argumentsQuantity = order + 1;
 unsigned argumentsValuesQuantity;
 double **Xs = new double*[argumentsQuantity];
 Xs[0] = convertXsArrayToSet(rowsQty, X, &argumentsValuesQuantity);
 for (unsigned i = 1; i < argumentsQuantity; i++) {
  Xs[i] = convertYsArrayToSet(rowsQty, Y);
 }
 double *arguments = convertDoublePointerToSingle(
  argumentsQuantity,
  argumentsValuesQuantity,
  Xs
 );
 double *R;
 R = new double[(unsigned) pow(argumentsValuesQuantity, argumentsQuantity)];
 for (i = 0; i < argumentsValuesQuantity; i++) {
  for (unsigned j = 0; j < argumentsValuesQuantity; j++) {
   *(R+i*argumentsValuesQuantity+j) = results[j*argumentsValuesQuantity+i];
  }
 }
 for (i = 0; i < argumentsQuantity; i++) {
  delete [] Xs[i];
 }
 delete [] Xs;
 return IFUsage::apply(
  argumentsQuantity,
  argumentsValuesQuantity,
  arguments,
  R,
  x
 );
}

double readDEResults(double x, double y,...) {
 char strTemp[134];
 unsigned rowsQuantity, order;
 int sn = -1;
 double *X, *Y, *results, *Ys = &y, result = -1;
 const double accuracy = 0.000001;
 FILE *fl = fopen(".\\fe_deres.txt", "rt");
 if (fl == NULL) {
  printf("File with differential equation results not found!\n");
  exit(-1);
 }
 rowsQuantity = 0;
 while(!feof(fl)) {
  fgets(strTemp, 134, fl);
  order = 0;
  for(unsigned j = 0; j < strlen(strTemp); j++) {
   if (strTemp[j] == ' ') {
    order++;
   }
  }
  rowsQuantity++;
 }
 rowsQuantity--;
 order--;
 fseek(fl, 0, SEEK_SET);
 X = new double[rowsQuantity];
 Y = new double [rowsQuantity * order];
 results = new double [rowsQuantity];
 for (unsigned i = 0; i < rowsQuantity; i++) {
  fscanf(fl, "%lf", (X+i));
  for (unsigned j = 0; j < order; j++) {
   fscanf(fl, "%lf", (Y+i*order+j));
  }
  fscanf(fl, "%lf", (results+i));
 }
 fclose(fl);
 for (i = 0; i < rowsQuantity; i++) {
  for(int j = 0; j < order; j++) {
   if (fabs(X[i] - x) < accuracy && fabs(*(Y+i*order+j) - Ys[j]) < accuracy) {
    sn = i;
    result = results[i];
   }
  }
 }
 if (sn == -1) {
  double variables[] = {x, y};
  result = interpolateAbsent(order, rowsQuantity, X, Y, results, variables);
 }
 delete [] results;
 delete [] Y;
 delete [] X;
 return result;
}

#endif
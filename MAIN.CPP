#include "DIFFEQU.HPP"
#include "DEMRUNGE.HPP"

double equation(double x, double y,...) {
 return 0.25 * y * y + x * x;
}

int main() {
 unsigned order = 1;
 double from, to, step, *initConditions, *preX, *preY;
 clrscr();
 printf("Input band and step in format of <from to step>: ");
 scanf("%lf %lf %lf", &from, &to, &step);
 printf("Input initial conditions x0 y0 y10 y20 ... y(n-1)0: ");
 initConditions = new double[order + 1];
 for (unsigned i = 0; i < order + 1; i++) {
  scanf("%lf", (initConditions + i));
 }
 printf("You have input band [%f; %f] with step %f\n", from, to, step);
 printf("Initial conditions you have input:\n");
 for(i = 0; i < order + 1; i++) {
  printf("%f ", *(initConditions+i));
 }
 printf("\nExecuting...\n");
 DiffEqu *de = new DiffEqu(equation, initConditions, from, to, step, order);
 DEMethod *deMethod = new DEMRunge(de);
 deMethod->resolve();
 char *resolves = deMethod->output();
 printf("Runge-Kutt method results:\n");
 puts(resolves);
 delete [] resolves;
 delete deMethod;
 delete de;
 printf("Press any key to exit\n");
 getch();
 return 0;
}
#include "DIFFEQU.HPP"
#include "DEMRUNGE.HPP"
#include "DEMADAMS.HPP"
#include "DEEXEC.HPP"
#include "DEREADER.HPP"

int main() {
 unsigned order;
 double from, to, step, *initConditions, *preX, *preY;
 char equationRightPart[128];
 clrscr();
 do {
  printf("Input an order of the highest derivative in equation: ");
  scanf("%d", &order);
 } while (order < 1);
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
 Executor *dee = new DEExec(".\\", "deexecr", order);
 printf("\nInput right part of differential equation:\n");
 printf("y%d = ", order);
 scanf("%s", &equationRightPart);
 dee->setFormula(equationRightPart);
 printf("\nExecuting...\n");
 dee->execute(from, to, step, initConditions, order+1);
 delete dee;
 DiffEqu *de = new DiffEqu(readDEResults, initConditions, from, to, step, order);
 DEMethod *deMethod = new DEMRunge(de);
 deMethod->resolve();
 char *resolves = deMethod->output();
 printf("Runge-Kutt method results:\n");
 puts(resolves);
 delete [] resolves;
 printf("Press any key to watch results, got with Adams method\n");
 getch();
 deMethod->slice(0, 4, &preX, &preY);
 delete deMethod;
 DEMethod *demAdams = new DEMAdams(de, preX, preY);
 demAdams->resolve();
 resolves = demAdams->output();
 printf("Adams method results:\n");
 puts(resolves);
 delete [] resolves;
 delete demAdams;
 delete de;
 printf("Press any key to exit\n");
 getch();
 return 0;
}
#ifndef DEEXEC_HPP
#define DEEXEC_HPP

#include "../../DOSHLPRS/FOREXEC/EXECUTOR.HPP"

class DEExec : public Executor {
 private:
  unsigned order;
 protected:
  void saveBeforeExecute() {
   char strTemp[68];
   char source[1820];

   char strDERightPart[136];
   strcpy(strDERightPart, "f(x, ");
   for (unsigned j = 0; j < order; j++) {
    if (j == 0) {
     strcat(strDERightPart, "y");
    } else {
     sprintf(strTemp, "y%d", j);
     strcat(strDERightPart, strTemp);
    }
    strcat(strDERightPart, (j < order - 1) ? ", " : ");");
   }
   strcat(strDERightPart, "\n");
   char strDEOutput[129];
   strcpy(strDEOutput, "");
   strcat(strDEOutput, "  fprintf(fl, \"%f ");
   for(j = 0; j < order; j++) {
    strcat(strDEOutput, "%f");
    strcat(strDEOutput, (j < order - 1) ? " " : " %f\\n\", x, ");
   }
   for (j = 0; j < order; j++) {
    if (j == 0) {
     strcat(strDEOutput, "y");
    } else {
     sprintf(strTemp, "y%d", j);
     strcat(strDEOutput, strTemp);
    }
    strcat(strDEOutput, (j < order - 1) ? ", " : ", D);");
   }
   strcat(strDEOutput, "\n");
   strcpy(source, "");
   strcat(source, "#include <stdio.h>\n");
   strcat(source, "#include <conio.h>\n");
   strcat(source, "#include <math.h>\n");
   strcat(source, "#include <stdlib.h>\n\n");

   strcat(source, "double f(double x, ");
   for (j = 0; j < order; j++) {
    if (j == 0) {
     strcat(source, "double y");
    } else {
     sprintf(strTemp, "double y%d", j);
     strcat(source, strTemp);
    }
    strcat(source, (j < order - 1) ? ", " : ") {\n return ");
   }

   strcat(source, this->expression);
   strcat(source, "\n}\n\n");
   strcat(source, "int main(int argc, char *argv[]) {\n");
   strcat(source, " double from, to, step, x, y, *initialConditions, D;\n");

   if (order > 1) {
    char strDoubleDeclaration[30], strUnsignedDeclaration[30];
    strcpy(strTemp, "");
    strcpy(strDoubleDeclaration, " double ");
    strcpy(strUnsignedDeclaration, " unsigned ");
    for (j = 0; j < order - 1; j++) {
     sprintf(strTemp, "y%d", j+1);
     strcat(strDoubleDeclaration, strTemp);
     strcat(strDoubleDeclaration, (j < order-2) ? ", " : ";\n");
     sprintf(strTemp, "i%d", j+1);
     strcat(strUnsignedDeclaration, strTemp);
     strcat(strUnsignedDeclaration, (j < order-2) ? ", " : ";\n");
    }
    strcat(source, strDoubleDeclaration);
    strcat(source, strUnsignedDeclaration);
   }

   strcat(source, " unsigned icq = 0, icfq, vq, i;\n");
   strcat(source, " char **strInitialConditions;\n");
   strcat(source, " FILE *fl;\n");
   strcat(source, " if (argc < 6) {\n");
   strcat(source, "  printf(\"Command accepts from 6 arguments\\n\");\n");
   strcat(source, "  getch();\n  return -1;\n }\n");
   strcat(source, " from = atof(argv[1]);\n");
   strcat(source, " to = atof(argv[2]);\n");
   strcat(source, " step = atof(argv[3]);\n");
   strcat(source, " while (argv[icq + 4] != NULL) {\n  icq++;\n }\n");
   strcat(source, " strInitialConditions = &argv[4];\n");
   strcat(source, " initialConditions = (double*)malloc(icq * sizeof(double));\n");
   strcat(source, " for (i = 0; i < icq; i++) {\n");
   strcat(source, "  initialConditions[i] = atof(strInitialConditions[i]);\n");
   strcat(source, " }\n");
   strcat(source, " icfq = icq - 1;\n");
   strcat(source, " vq = (fabs(to - from)) / fabs(step) + 1;\n");
   strcat(source, " fl = fopen(\"fe_deres.txt\", \"wt\");\n");

   if (order > 1) {
    char strLoop[264];
    strcpy(strLoop, "");
    for (j = 0; j < order - 1; j++) {
     sprintf(strTemp, " for(y%d = initialConditions[%d], i%d = 0; i%d < vq; y%d += step, i%d++)\n",
      order-j-1, order-j, order-j-1, order-j-1, order-j-1, order-j-1);
     strcat(strLoop, strTemp);
     strcat(strLoop, " ");
    }
    strcat(source, strLoop);
   }

   strcat(source, " for(y = initialConditions[1], i = 0; i < vq; y += step, i++) {\n");
   strcat(source, "  for(x = from; x <= to; x += step) {\n");
   strcat(source, "  D = ");
   strcat(source, strDERightPart);
   strcat(source, strDEOutput);
   strcat(source, "  }\n");
   strcat(source, " }\n");
   strcat(source, " fclose(fl);\n");
   strcat(source, " free(initialConditions);\n");
   strcat(source, " return 0;\n}");

   FILE *f = fopen(this->execSourcePath, "wt");
   fprintf(f, "%s", source);
   fclose(f);
  }

 public:
  DEExec(char strFilesDir[116], char fileNameBeforeExtension[9], unsigned o) :
   Executor(strFilesDir, fileNameBeforeExtension) {
    order = (o < 1) ? 1 : o;
  }
  ~DEExec() {
  }
};

#endif
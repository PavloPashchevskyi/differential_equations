This program resolves differential equations with the first highest derivative by Runge-Kutt method.

The program can resolve differential equations like yI = f(x, y)

Example of this program usage is in "MAIN.CPP" file.
To resolve another equation, change the body of equation(double x, double y...); function.
Yes, now equation is hardcoded in program, but it is planned to inject recompilation or extend it from "FOREXEC" module (see "FOREXEC" folder in https://github.com/PavloPashchevskyi/doshlprs/tree/develop )

After starting this program you will be prompt to input range of values you want to resolve differential equation and step (minimal difference between two values). 
Input it in the format of "from to step" (without quotes, space is delimiter).
Then you will be prompt to input initial conditions. Input it in format "x f(x)" (without quotes, space is delimiter). For example, if initial condition is f(0) = -1, you should input the following.

    0 -1

Then you will see the results of equation resolutuin as table with the followung columns.


	i	X[i]	Y[i]	f(X[i], Y[i])

Where:
 i - iteration number, counting from 0 (for the initial condition)
 X[i] - value of X in the i point
 Y[i] - value of Y in the i point
 f(X[i], Y[i]) - value of function derivative (for equations like yI = f(x, y))

Then press any key to exit.

Enjoy!

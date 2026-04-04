This program resolves differential equations with the first highest derivative by Runge-Kutt and Adams methods.

The program can resolve differential equations like yI = f(x, y)

Recompilation is injected into this program via "FOREXEC" module (see "FOREXEC" folder in https://github.com/PavloPashchevskyi/doshlprs/tree/develop repository).
To use this module, please, do the following.
1. Create "dosmods" directory in the root directory of the project (directory, in which you have clonned this project, for example, via "git clone git@github.com:PavloPashchevskyi/differential_equations.git", if you use git)
2. Go to "dosmods" directory you have just created (cd dosmods/)
3. Copy "FOREXEC" folder from https://github.com/PavloPashchevskyi/doshlprs/tree/develop to "dosmods"
4. Copy "__CONFIG.HPP" file from https://github.com/PavloPashchevskyi/doshlprs/tree/develop to "dosmods"
5. Rename "__CONFIG.HPP" file to "CONFIG.HPP"
6. If it`s needed, you can change settings in "CONFIG.HPP" (paths to your compiler, linker, paths to "include" and "lib" directories...)
7. Return from "dosmods" to the root directory of the project (cd ..)
8. Run IDE from that directory with transfering to the IDE path to "MAIN.CPP" file
   Example for Borland C++ 3.1:
   c:\your\ide\dir\bin\bc.exe ./MAIN.CPP
   (or simply run your IDE and open "MAIN.CPP" file with it)
9. Make this project. In Borland C++3.1 it can be done by pressing "F9" key
10. Quit IDE ("Alt+X" keys combination in Borland C++3.1) and run "MAIN.EXE" file (from the root directory of the project) to start this program


After starting this program you will be prompt to input range of values you want to resolve differential equation and step (minimal difference between two values). 
Input it in the format of "from to step" (without quotes, space is delimiter).
Then you will be prompt to input initial conditions. Input it in format "x f(x)" (without quotes, space is delimiter). For example, if initial condition is f(0) = -1, you should input the following.

    0 -1

After that you will be prompt to input the right part of differential equation (left part is the highest order of derivative in the equation).

    y1 =

Input the right part of equation, using the "C" language syntax (sign ";" in the end is not required). For example,

    0.25*y*y+x*x

and press "Enter".
Note, that to define right part of equation you might use only the following variables

    x - independent variable
    y - searching function
    y1 - the first derivative

Then you will see the results of equation resolutuin as table with the followung columns.


	i	X[i]	Y[i]	f(X[i], Y[i])

Where:
 i - iteration number, counting from 0 (for the initial condition)
 X[i] - value of X in the i point
 Y[i] - value of Y in the i point (value of the function, which is resolution of the equation)
 f(X[i], Y[i]) - value of function derivative (for equations like yI = f(x, y))

It is solution by the Runge-Kutt method. Then the program will ask you whether you want to resolve the equation via Adams method. Press "y" key if you want to or "n" key if you don`t want to resolve via Adams method.

Then press any key to exit.

Enjoy!

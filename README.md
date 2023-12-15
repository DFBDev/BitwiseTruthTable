# BitwiseTruthTable
College project in Computer Organization. Calculates Boolean Expression results for differing, sequential parameters of 2-4 bit binary.

The main objective for this project was to take in a user-entered boolean expression, containing 2-4 undesignated variables, and solve the expression given multiple cases of differing binary values (in order of operator precedence). Below is a sample output: 

------------------------------------------------
Enter the Boolean expression: (A + B) * (C ^ D)

 A  B  C  D | A + B | C ^ D | (A + B) * (C ^ D)
 ===============================================
 0  0  0  0 |   0   |   0   |         0
 0  0  0  1 |   0   |   1   |         0
 0  0  1  0 |   0   |   1   |         0
 0  0  1  1 |   0   |   0   |         0
 0  1  0  0 |   1   |   0   |         0
 0  1  0  1 |   1   |   1   |         1
 0  1  1  0 |   1   |   1   |         1
 0  1  1  1 |   1   |   0   |         0
 1  0  0  0 |   1   |   0   |         0
 1  0  0  1 |   1   |   1   |         1
 1  0  1  0 |   1   |   1   |         1
 1  0  1  1 |   1   |   0   |         0
 1  1  0  0 |   1   |   0   |         0
 1  1  0  1 |   1   |   1   |         1
 1  1  1  0 |   1   |   1   |         1
 1  1  1  1 |   1   |   0   |         0

Run again (Y/N): N
------------------------------------------------

Code contains no non-portable libraries/dependencies, only standard C++ library.
Program runs in terminal and was developed in Visual Studio.

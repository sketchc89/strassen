# Strassen

Linear algebra library that implements matrix transpose and multiplication. Named after Volker Strassen famous for O(n^2.6) matrix multiplication algorithm.

## Design Choices

* Implemented as a template library and care was taken to make as many errors occur at compile time as possible
* Matrices are statically allocated so the size of matrices must be known at compile time
* Compile-time failures - matrix multiplication with invalid dimensions, matrix multiplication with unequal types

* A variable size matrix library has the advantages of ease of use and less templating, but suffers from memory fragmentation which can potentially hurt performance. If a variable size matrix were needed I would implement it as a separate class (similar to Matrix2d vs MatrixXd in the popular linear algebra library Eigen)


## Building

* Requires cmake and a compiler that supports c++ 14 or later
* To build

```bash
mkdir build && cd build
cmake ..
make -j
```

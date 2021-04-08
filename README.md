# Strassen

Linear algebra library that implements matrix transpose and multiplication. Named after [Volker Strassen](https://en.wikipedia.org/wiki/Volker_Strassen) famous for O(n^2.6) matrix multiplication algorithm.

## Design Choices

* Implemented as a template library and care was taken to make as many errors occur at compile time as possible
* Matrices are statically allocated so the size of matrices must be known at compile time
* Compile-time failures - matrix multiplication with invalid dimensions, matrix multiplication with unequal types
* Implements naive matrix multiplication. [Strassen's algorithm](https://en.wikipedia.org/wiki/Strassen_algorithm) and other very efficient matrix multiplication algos are only more efficient for large matrices.
* A variable size matrix library has the advantages of ease of use and less templating, but suffers from memory fragmentation which can potentially hurt performance. If a variable size matrix were needed I would implement it as a separate class (similar to Matrix2d vs MatrixXd in the popular linear algebra library Eigen)


## Building

* Requires cmake and a compiler that supports c++ 14 or later
* Also requires a connection to the internet and git, since gtest is downloaded as part of the build
* To build from root level directory (folder this README is in)

```bash
mkdir build
cd build
cmake ..
make -j
```


## Using

The best documentation are the unit tests located [here](./test/TestStrassen.cpp)

```C++
strassen::Mat<double, 3, 2> lhs{{1.1, 2.2}, {3.3, 4.4}, {5.5, 6.6}};
strassen::Mat<double, 2, 4> rhs{{11.11, 22.22, 33.33, 44.44}, {55.55, 66.66, 77.77, 88.88}};

auto res = lhs * rhs;
std::cerr << "Values are\n" << res;
// prints out:
// Values are
// 122.21,146.652,171.094,195.536,
// 244.42,293.304,Values are
// 366.63,439.956,513.282,586.608,
std::cerr << "Dimensions are (" << res.dim().first << ',' << res.dim().second << ")\n";
// prints out:
// Dimensions are (3,4)

auto tres = res.transpose();
std::cerr << "Dimensions are (" << tres.dim().first << ',' << tres.dim().second << ")\n";
// prints out:
// Dimensions are (4,3)

```


## Testing

Run the executable `${BUILD_DIR}/test/testStrassen`

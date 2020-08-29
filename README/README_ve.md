# vec_op
C++ Header: Operator definition for std::vector

## How to Use
Include the header `vec_op.hpp`:

```
#include "vec_op.hpp"
```

See sample source `sample.cpp`. 

The result of `sample.cpp`:

```
$ make
$ ./run.exe
v1 = [ 1, 2.5, 5.6, 3.1, 8, ]
v2 = [ 4.9, 3, 1.5, 2, 1.7, ]
c = 1.4
--------------------------------------------------
+v1 = [ 1, 2.5, 5.6, 3.1, 8, ]
-v2 = [ -4.9, -3, -1.5, -2, -1.7, ]
--------------------------------------------------
v1 + v2 = [ 5.9, 5.5, 7.1, 5.1, 9.7, ]
v1 - v2 = [ -3.9, -0.5, 4.1, 1.1, 6.3, ]
v1 * v2 = [ 4.9, 7.5, 8.4, 6.2, 13.6, ]
v1 / v2 = [ 0.204082, 0.833333, 3.73333, 1.55, 4.70588, ]
v1 ^ v2 = [ 1, 15.625, 13.252, 9.61, 34.2968, ]
--------------------------------------------------
v1 + c = [ 2.4, 3.9, 7, 4.5, 9.4, ]
v1 - c = [ -0.4, 1.1, 4.2, 1.7, 6.6, ]
v1 * c = [ 1.4, 3.5, 7.84, 4.34, 11.2, ]
v1 / c = [ 0.714286, 1.78571, 4, 2.21429, 5.71429, ]
v1 ^ c = [ 1, 3.60675, 11.1548, 4.87423, 18.3792, ]
c ^ v1 = [ 1.4, 2.3191, 6.58138, 2.8379, 14.7579, ]
--------------------------------------------------
(v1 == v2) = [ 0, 0, 0, 0, 0, ]
(v1 != v2) = [ 1, 1, 1, 1, 1, ]
(v1 < v2) = [ 1, 1, 0, 0, 0, ]
(v1 > v2) = [ 0, 0, 1, 1, 1, ]
(v1 <= v2) = [ 1, 1, 0, 0, 0, ]
(v1 >= v2) = [ 0, 0, 1, 1, 1, ]
--------------------------------------------------
dot(v1, v2) = 40.6
sum(v1) = 20.2
prod(v1) = 347.2
min(v1) = 1
max(v1) = 8
cast<double, int>(v1) = [ 1, 2, 5, 3, 8, ]
concat(v1, v2) = [ 1, 2.5, 5.6, 3.1, 8, 4.9, 3, 1.5, 2, 1.7, ]
sort(v1) = [ 1, 2.5, 3.1, 5.6, 8, ]
argsort(v1) = [ 0, 1, 3, 2, 4, ]
randomIndex(10) = [ 2, 7, 1, 5, 6, 0, 9, 4, 3, 8, ]
range(10) = [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ]
range(2,10,2) = [ 2, 4, 6, 8, ]
fill(v1, 1); v1 = [ 1, 1, 1, 1, 1, ]
```
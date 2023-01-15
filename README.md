# Nibl

### Building
Nibl requires a C++ compiler and CMake to build.

```
cd nibl
mkdir build
cd build
cmake ..
make
./nibl
Nibl v1

1 2 3 dup

[1 2 3 3]
```

### Stack Operations

#### dup
Duplicates the top value.

#### pop
Removes the top value.

#### swap
Swaps the two top values.

### Tracing

Tracing may be toggled using `trace`.

```
  trace
  
0 STOP
[]
  1 2 3 dup
  
2 PUSH_INT1 1
4 PUSH_INT1 2
6 PUSH_INT1 3
8 DUP
10 STOP
[1 2 3 3]
  trace
  
[1 2 3 3]
```

### Numerical Operations

#### +
Adds the two top numbers.

#### -
Subtracts the two top numbers.

#### *
Multiples the two top numbers

#### /
Divides the two top numbers.

#### %
Calculates the remainder from dividing the two top numbers.

### Types
`typeof` may be used to get the type of any value.

```
  1 typeof

[Int]
  typeof

[Meta]
```

Every value has one of the following types:

#### Int
The type of numbers.

#### Macro
The type of macros.

#### Meta
The type of types.

### References
References may be captured using `&`.

```
  1 2 3 dup

[1 2 3 3]
  &dup

[1 2 3 3 dup]
```
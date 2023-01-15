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
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
Nibl v2

1 2 3 dup

[1 2 3 3]
```

### Stack Operations

#### dup [a | a a]
Duplicate `a`.

#### pop [a |]
Remove `a`.

#### swap [a b | b a]
Swaps `a` and `b`.

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

### Numbers

#### + [a b | c]
`c` is `b` added to `a`.

#### - [a b | c]
`c` is `b` subtracted from `a`.

#### * [a b | c]
`c` is `a` multiplied by `b`.

#### / [a b | c]
`c` is `a` divided by `b`.

#### % [a b | c]
`c` is the remainder from dividing `a` by `b`.

### Booleans
Booleans have one of two values: `T` or `F`.

#### < [a b | c]
`c` is `T` if `a` is less than `b`, else `F`.

#### > [a b | c]
`c` is `T` if `a` is greater than `b`, else `F`.

### Types
Every value has one of the following types:

- `Bool` The type of booleans.
- `Int` The type of numbers.
- `Macro` The type of macros.
- `Meta` The type of types.

#### typeof [a | b]
`b` is the type of `a`.

```
  1 typeof

[Int]
  typeof

[Meta]
```

### References
References may be captured using `&`.

```
  1 2 3 dup

[1 2 3 3]
  &dup

[1 2 3 3 dup]
```
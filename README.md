# Nibl

### Intro
Nibl is a virtualized Forth-like language that aims to be both simple to understand/extend/embed and practical.
The complete implementation supporting all features described in this document currently weighs in at around 1kloc.

### Building
Nibl requires a C++ compiler and CMake to build.

```
cd nibl
mkdir build
cd build
cmake ..
make
./nibl
Nibl v3

1 2 3 dup

[1 2 3 3]
```

### Stack Operations

#### dup [a | a a]
Duplicate `a`.

#### pop [a |]
Remove `a`.

#### swap [a b | b a]
Swap `a` and `b`.

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
Booleans can be either true (`T`) or false (`F`).

#### = [a b | c]
`c` is true if `a` and `b` are equal, else false.

```
1 3 =
  
[F]
```
```
  3 3 =
  
[T]
```
```
  T F =
  
[F]
```
```
  T T =
  
[T]
```
#### < [a b | c]
`c` is true if `a` is less than `b`, else false.

#### > [a b | c]
`c` is true if `a` is greater than `b`, else false.

#### not [a | b]
`b` is true if `a` is false, else false.

#### and: b [a | c]
`c` is false if `a` is false, else the result of evaluating `b`.

```
  T and: 3
  
[3]
```
```
  F and: 3

[F]
```

#### or: b [a | c]
`c` is true if `a` is true, else the result of evaluating `b`.

```
  T or: 3
  
[T]
```
```
  F or: 3

[3]
```

#### if: ...; [a | ...]
Skip evaluation until `;` is reached or the program ends when `a` is false.

```
  T if: 1 2; 3

[1 2 3]
```
```
  F if: 1 2; 3

[3]
```

### Types
Every value has one of the following types:

- `Bool` The type of booleans.
- `Int` The type of numbers.
- `Macro` The type of macros.
- `Meta` The type of types.

#### type-of [a | b]
`b` is the type of `a`.

```
  1 type-of

[Int]
  type-of

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

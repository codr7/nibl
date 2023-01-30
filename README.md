# Nibl

### Intro
Nibl is a Forth VM that aims to be simple to understand, extend and embed; it currently weighs in at around 2kloc.

### Building
Nibl requires a C++ compiler and CMake to build.

```
cd nibl
mkdir build
cd build
cmake ..
make
./nibl help
Nibl v11

Usage: nibl [command] [file1.nl] [file2.nl]

Commands:
dump    Dump VM code
eval	Evaluate and exit
repl	Start REPL
v	Print version and exit
```

### Stack Operations

#### dup [a | a a]
Duplicate `a`.

#### pop [a |]
Remove `a`.

#### swap [a b | b a]
Swap `a` and `b`.

#### rotl [a b c | c a b]
Rotate top three values left.

#### rotr [a b c | b c a]
Rotate top three values right.

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

### Comparisons

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

### Branching

#### if: ...; [a | ...]
Skip evaluation until `;` or `else:` is reached or the program ends when `a` is false.

```
  T if: 1 2; 3

[1 2 3]
```
```
  F if: 1 2; 3

[3]
```

```
  T if: 1 else: 2; 3

[1 3]
```
```
  F if: 1 else: 2; 3

[2 3]
```

```
   20 dup 10 = if: pop 1 else: dup 20 = if: pop 2 else: pop 3;;

[2]
```

### Definitions
Values may be bound to names using `def:`.

```
  def: foo 42

[]
  foo

[42]
```

### Functions
Functions are first class and may be defined using `fun:`, and subsequently called using `call`.

```
  fun: 1 2 3;
  
[Fun(repl@1:1)]
  call
  
[1 2 3]
```

### Types
Every value has one of the following types:

- `Bool` The type of booleans
- `Fun` The type of functions
- `Int` The type of numbers
- `Lib` The type of libraries
- `Macro` The type of macros
- `Meta` The type of types
- `Prim` The type of primitives
- `Str` The type of strings

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
```
```
  1 2 3 &dup

[1 2 3 dup]
```

### Loading
Code may be loaded from file using `load`.

foo.nl
```
1 2 3
```
```
  "foo.nl" load

[1 2 3]
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
```

### Testing
`test:` may be used to write tests, it compares the contents of the stack before and after running the code.

```
  1 2 test: 1 2 3;
  
Test failed, expected: [1 2], actual: [1 2 3]
[]
```
```
  1 2 3 test: 1 2 3;
  
Test ok: [1 2 3]
[]
```

Nibl comes with a [regression test suite](https://github.com/codr7/nibl/blob/main/tests.nl).

```
./nibl ../tests.nl

Test ok: [1 2 2]
...
```

### Benchmarking
`bench:` evaluates its body specified number of repetitions and measures elapsed time in milliseconds.

#### Recursive Fibonacci
```
  def: fib fun:
    dup 1 > if:
      dec dup fib swap
      dec fib +;;
[]

  1000 bench: 20 fib pop;

[1120]
```
```
python bench/fib.py
1004
```

#### Tail recursive Fibonacci
```
  def: fib fun:
    rotr dup 1 > if:
      dec rotl dup rotl + rec
    else:
      1 = if: swap;
      pop;;

[]

  100000 bench: 100 0 1 fib pop;
[1091]
```
```
python bench/fibt.py
657
```
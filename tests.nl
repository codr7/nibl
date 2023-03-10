1 2 2 test: 1 2 dup;
1 2 test: 1 2 3 pop;
1 3 2 test: 1 2 3 swap;
3 1 2 test: 1 2 3 rotl;
2 3 1 test: 1 2 3 rotr;

7 test: 3 4 +;
4 test: 7 3 -;
12 test: 3 4 *;
3 test: 10 3 /;

"42" test: 42 to-str;
42 "foo" test: "42foo" parse-int;
7 " 14" test: "7 14" parse-int;

"foo 2 bar 1 baz" test: 1 2 "foo % bar % baz";
"foo 3 bar" test: "foo %{1 2 +} bar";
"foo 42 bar \%" test: 42 "foo % bar \%";

F test: 42 not;
3 test: 42 and: 3;
F test: F and: 3;
42 test: 42 or: 3;
3 test: F or: 3;

T test: 3 3 =;
F test: 1 3 =;
T test: 1 3 <;
F test: 3 1 <;
T test: 3 1 >;
F test: 1 3 >;

1 2 3 test: T if: 1 2; 3;
3 test: F if: 1 2; 3;
1 3 test: T if: 1 else: 2; 3;
2 3 test: F if: 1 else: 2; 3;

1 test: 10 dup 10 = if: pop 1 else: dup 20 = if: pop 2 else: pop 3;;;
2 test: 20 dup 10 = if: pop 1 else: dup 20 = if: pop 2 else: pop 3;;;
3 test: 30 dup 10 = if: pop 1 else: dup 20 = if: pop 2 else: pop 3;;;

1 2 3 test: fun: 1 2 3; call;

def: fib fun:
  dup 1 > if: 1 - dup fib swap 1 - fib +;;

55 test: 10 fib;

def: fibt fun:
  rotr dup 1 > if:
    dec rotl dup rotl + rec
  else:
    1 = if: swap;
    pop;;

55 test: 10 0 1 fibt;

Int test: 1 type-of;
Meta test: Int type-of;
Macro test: &dup type-of;
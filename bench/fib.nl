def: fib fun:
  dup 1 > if:
    dec dup fib swap
    dec fib +;;

1000 bench: 20 fib pop;
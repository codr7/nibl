def: fib fun:
  rotr dup 1 > if:
    dec rotl dup rotl + rec
  else:
    1 = if: swap;
    pop;;

100000 bench: 100 0 1 fib pop;
def: fib fun:
  rotr dup 1 > if:
    dec rotl dup rotl + rec
  else:
    0 = if:
      pop
    else:
      swap pop;;;

1000000 bench: 20 0 1 fib pop;
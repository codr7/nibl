def: fib fun:
  rotr dup 0 = if:
    pop pop
  else: dup 1 = if:
    pop swap pop
  else:
    dec rotl dup rotl + fib;;;

1000000 bench: 20 fib pop;
def: fib fun:
  rotr dup 0 = if:
    pop pop
  else: dup 1 = if:
    pop swap pop
  else:
    dec rotl dup rotl + rec;;;

1000000 bench: 20 0 1 fib pop;
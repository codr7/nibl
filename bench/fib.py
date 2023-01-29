from bench import bench

print(bench(1000, '''
def fib(n):
  if n < 2: return n
  return fib(n-1) + fib(n-2)
''', '''
fib(20)
'''))

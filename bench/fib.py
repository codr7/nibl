from bench import bench

print(bench(1000, '''
def fib(n):
  return fib(n-1) + fib(n-2) if n > 1 else n
''', '''
fib(20)
'''))

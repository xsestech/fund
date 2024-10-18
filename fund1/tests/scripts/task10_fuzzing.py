import subprocess
import string
import random

process = subprocess.Popen(["./cmake-build-debug/task10/task10"], stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                           stderr=subprocess.PIPE)
stdin = process.stdin
stdin.write("36 ".encode())
for i in range(1000):
    stdin.write(random.choice(string.printable).encode())

stdin.write("Stop".encode())
stdin.close()
lines = process.stdout.readlines()
lines2 = process.stderr.readlines()
print(*[s.decode() for s in lines], sep="\n")
print(*[s.decode() for s in lines2], sep="\n")
# print(process.stdout.)

import random
import string
n_abc = 0
poses = []
for line in range(random.randint(5, 20)):
    column = 0
    for _ in range(random.randint(0, 150)):
        if random.random() < 0.3:
            print(" ", end="")
        else:
            print(random.choice(string.ascii_letters + string.punctuation), end="")
        column += 1
        if random.random() < 0.01:
            poses += [(line + 1, column + 1)]
            print("abc", end="")
            n_abc += 1
            column += 3
    if n_abc > 10:
        print()
        break
    print()
print("-------------Answers--------------")
print("{")
for pose in poses:
    print(f"  {{1, {pose[0]}, {pose[1]}}},")
print("};")

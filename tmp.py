import sys

lines = []
res = 0
for line in sys.stdin:
    line=line[:-1]
    if line[0].isdigit() and line[1].isdigit() and line[2].isdigit() and line[3].isdigit() and line[4].isdigit():
        res+=1
print(res)
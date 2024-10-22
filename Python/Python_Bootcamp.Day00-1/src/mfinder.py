import sys

def check(lines):
    res=True
    for i  in range(len(lines)):
        if len(lines[i])!=5:
            res = False
    return res

def transform(lines):
    str=''
    str=[line for line in lines]
    return ''.join(str)


with open('m.txt', 'r') as f:
    lines = [line.strip() for line in f]
if len(lines)==3 and check(lines):
    str=transform(lines)
    index:list = [0, 4, 5, 6, 8, 9, 10, 12, 14]
    res ='True'
    for i in range(len(str)):
        if i in index and str[i] != '*':
            res = 'False'
        if i not in index and str[i] == '*':
            res = 'False'
    print (res)
else:
    print('Error')
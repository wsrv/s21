
import sys

num_lines = int(sys.argv[1])
for i in range(num_lines):
  new_string:str = input()
  if new_string[:5] == "00000" and len(new_string) == 32:
    print(new_string)

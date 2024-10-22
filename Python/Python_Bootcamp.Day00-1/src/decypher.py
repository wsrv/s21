
import sys

def extract_initials(sentence):
    words = sentence.split()
    initials = [word[0] for word in words]
    return ''.join(initials)

input_sentence = ' '.join(sys.argv[1:])
result = extract_initials(input_sentence)
print(result)
import re
import numpy as np
import string

with open('loremipsum.txt', 'rb') as f:
  text = f.read()
  letters = 0
  words = 0
  for letter in text.decode('latin1'):
    if letter == ' ':
      words += 1
    elif letter in string.ascii_letters:
      letters += 1
    # else:
    #   print(letter)
    # there are ";" characters in the file

  words += 1 # count last word
  print(f'Total words - {words}')
  print(f'Mean lettes per word - {letters / words}')
  print(f'Total letters - {letters}')

  print('\nUsing regexp and numpy:')
  result = re.findall(r"\w+", text.decode('latin1'))
  print(len(result))
  result = list(map(lambda x: len(x), result))
  print(np.mean(result))
  print(sum(result))
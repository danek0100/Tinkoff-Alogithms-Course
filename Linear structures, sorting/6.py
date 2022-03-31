#Число 
#Формат входных данных
#Входной файл содержит одну или более строк, каждая из которых содержит последовательность цифр. Количество строк во входном файле не превышает 10000, каждая строка содержит от 1 до 100 цифр. Гарантируется, что хотя бы в одной строке первая цифра отлична от нуля.

#Формат результата
#Выведите в выходной файл одну строку — максимальное число, которое могло быть написано на полоске перед разрезанием. */

import sys
from functools import cmp_to_key

def compare(item1, item2):
    if int(item1+item2) < int(item2+item1):
        return -1
    return 1

words_array = []
for line in sys.stdin:
    words_array.append(line.rstrip())
words_array = sorted(words_array, key=cmp_to_key(compare), reverse=True)
answer = ""
for word in words_array:
    answer += word
print(answer)
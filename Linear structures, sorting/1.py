# Анаграммы

# Формат входных данных
#Даны два слова на отдельных строках. Слова состоят из строчных латинских букв и цифр. Длины слов не превышают 10^5

#Формат результата
#Требуется вывести «YES» – если введенные слова являются анаграммами друг друга, «NO» – если нет.

firstWord = input()

checkDict1 = {}
for char in firstWord:
    if char in checkDict1:
        newValue = checkDict1.get(char)+ 1
        checkDict1.update({char : newValue})
    else:
        checkDict1[char] = 1

secondWord = input()
checkDict2 = {}
for char in secondWord:
    if char in checkDict2:
        newValue = checkDict2.get(char)+ 1
        checkDict2.update({char : newValue})
    else:
        checkDict2[char] = 1

if checkDict1.items() == checkDict2.items():
    print('YES')
else:
    print('NO')
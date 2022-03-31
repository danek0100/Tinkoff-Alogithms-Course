#Постфиксная запись
#В постфиксной записи (или обратной польской записи) операция записывается после двух операндов.

#Формат входных данных
#В единственной строке записано выражение в постфиксной записи, содержащее цифры и операции 

#Числа и операции разделяются пробелами. В конце строки может быть произвольное количество пробелов.

#Формат результата
#Необходимо вывести значение записанного выражения. */

queue = input()
endl = 0
for i in range(len(queue)):
    if queue[i] != ' ':
        endl = i
    elif i - endl > 2:
        break
queue = queue[0:endl + 1]
queue = queue.split(sep=' ')

operation = ['+', '-', '*']
operation_stack = []
number_stack = []
for elem in queue:
    if elem not in operation:
        number_stack.append(int(elem))
    else:
        if elem == '+':
            first = number_stack.pop()
            second = number_stack.pop()
            number_stack.append(first + second)
        elif elem == '*':
            first = number_stack.pop()
            second = number_stack.pop()
            number_stack.append(first * second)
        elif elem == '-':
            first = number_stack.pop()
            second = number_stack.pop()
            number_stack.append(second - first)
print(number_stack.pop())
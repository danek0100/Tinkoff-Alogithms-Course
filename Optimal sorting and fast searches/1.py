# Count me In
#Формат входных данных
#В единственной строке входных данных дан исходный массив. Количество элементов в нём не превосходит 10^6

#Формат результата
#В единственной строке выходных данных выведите отсортированный массив.

numbers = list(map(int, input().split(sep=' ')))

second_array = [0 for i in range(10)]

for i in range(len(numbers)):
    second_array[numbers[i] - 1] += 1

for i in range(10):
    for j in range(second_array[i]):
        print(i + 1, end=' ')

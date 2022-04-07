# Инверсии
# Напишите программу, которая для заданного массива A=a1,a2,…,an находит количество пар (i,j)
# таких, что i<j и ai>aj.

#Обратите внимание на то, что ответ может не влезать в int.

#Формат входных данных
#Первая строка входного файла содержит натуральное число n(1⩽n⩽100000) “— количество элементов массива. 
# Вторая строка содержит n попарно различных элементов массива A ”— целых неотрицательных чисел, не превосходящих 10^9.

#Формат результата
#В выходной файл выведите одно число — ответ на задачу.


def merge_sort(array, left, right):
    if right - left < 2:
        return 0
    middle = (right + left) // 2
    left_inversions = merge_sort(array, left, middle)
    right_inversions = merge_sort(array, middle, right)
    return left_inversions + right_inversions + merge(array, left, middle, right)

def merge(array, left, middle, right):
    left_1, right_1 = left, middle
    left_2, right_2 = middle, right
    result = []
    inversions = 0
    while left_1 < right_1 and left_2 < right_2:
        if array[left_1] < array[left_2]:
            result.append(array[left_1])
            left_1 += 1
            inversions += left_2 - middle
        else:
            result.append(array[left_2])
            left_2 += 1
    while left_1 < right_1:
        result.append(array[left_1])
        left_1 += 1
        inversions += left_2 - middle
    while left_2 < right_2:
        result.append(array[left_2])
        left_2 += 1
    for i in range(left, right):
        array[i] = result[i - left]
    return inversions

with open('inverse.in', 'r') as f:
    n = int(f.readline())
    x = list(map(int, f.readline().split()))

answer = merge_sort(x, 0, n)
with open('inverse.out', 'w') as f:
    print(answer, file=f)

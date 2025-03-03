"""
Промяна на списък от числа:
Ако дадено число е по-голямо от въведеното сравнение, то се заменя с 0
"""

numbers = input("Въведете числата, разделени с интервал: ")
numbers_list = [int(num) for num in numbers.split()]
num = int(input("Въведете число за сравнение: "))

def modify_list(numbers_list, num):
    return [0 if x > num else x for x in numbers_list]

print(modify_list(numbers_list, num))

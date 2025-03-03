# Въвеждане на 5-цифрено число и преобразуване на всяка цифра в кортежи
num = input("Въведете цяло число: ")

# Преобразуване на всяка цифра в отделен елемент на списък
digits_list = [int(digit) for digit in num]

# Създаване на кортежи
my_tuple1 = tuple(digits_list)

# Преобразуване на digits_list в обратен ред и създаване на кортеж
digits_list.reverse()
my_tuple2 = tuple(digits_list)

print(my_tuple1)
print(my_tuple2)

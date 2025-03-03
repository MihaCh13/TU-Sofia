# Сумиране на числата в даден диапазон

last = int(input("Въведете края на диапазона за сумиране: "))
suma = 0
for i in range(1, last + 1):
    suma += i
print(suma)

"""
Калкулатор за основни математически операции:
- Събиране
- Изваждане
- Умножение
- Деление
"""

# Събиране
def subirane(a,b):
    return a + b

# Изваждане
def izvajdane(a, b):
    return a - b

# Умножение
def umnojenie(a, b):
    return a * b

# Деление
def delenie(a, b):
    return a / b

command = input("Въведете желаното действие, което искате да изпълните (събиране / изваждане / умножение / деление): ")
if command == "събиране":
    a = float(input("Въведете събираемото а: "))
    b = float(input("Въведете събираемото b: "))
    print(f"Сбора на числата е {subirane(a, b)}")

elif command == "изваждане":
    a = float(input("Въведете числото а: "))
    b = float(input("Въведете числото b: "))
    print(f"Разликата на числата е {izvajdane(a, b)}")

elif command == "умножение":
    a = float(input("Въведете числото а: "))
    b = float(input("Въведете числото b: "))
    print(f"Произведението на числата е {umnojenie(a, b)}")

else:
    a = float(input("Въведете делимото а: "))
    b = float(input("Въведете делителя b: "))
    print(f"Частното на числата е {delenie(a, b)}")


numbers = input("Въведете числата, разделени с интервал: ")
numbers_list = [int(num) for num in numbers.split()]
num = int(input("Въведете число за сравнение: "))

def promeni(n):
    lenght = len(numbers_list)
    for i in range(lenght):
        if numbers_list[i] > num:
            numbers_list[i] = 0
        else:
            numbers_list[i] = numbers_list[i]
    return numbers_list

print(promeni(numbers_list))

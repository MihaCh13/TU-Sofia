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
command = input("Въведете желаното действие (събиране / изваждане / умножение / деление): ")

if command == "събиране":
    a = float(input("Въведете събираемото а: "))
    b = float(input("Въведете събираемото b: "))
    print(f"Сборът на числата е {add(a, b)}")
    
elif command == "изваждане":
    a = float(input("Въведете числото а: "))
    b = float(input("Въведете числото b: "))
    print(f"Разликата на числата е {subtract(a, b)}")
    
elif command == "умножение":
    a = float(input("Въведете числото а: "))
    b = float(input("Въведете числото b: "))
    print(f"Произведението на числата е {multiply(a, b)}")
    
elif command == "деление":
    a = float(input("Въведете делимото а: "))
    b = float(input("Въведете делителя b: "))
    print(f"Частното на числата е {divide(a, b)}")
    
else:
    print("Невалидна операция")

# Проверка дали число е просто
num = int(input("Въведете число: "))
del_count = 0
for i in range(1, num + 1):
    if num % i == 0:
        del_count += 1
if del_count == 2:
    print(f"Числото {num} е просто")
else:
    print(f"Числото {num} не е просто")

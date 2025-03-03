# Изчисляване на сумата на въведените числа
chisla = int(input("Въведете n на брой цели числа: "))
ch_sum = 0
for i in range(chisla):
    print("Въведете число: ")
    chislo = int(input())
    ch_sum += chislo
print(f"Сумата от числата е {ch_sum}")

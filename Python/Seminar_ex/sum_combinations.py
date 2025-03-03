# Всички комбинации от три числа, които дават 15

target_sum = 15
for i in range(1, target_sum + 1):
    for j in range(i, target_sum + 1):
        k = target_sum - i - j
        if k >= 0:
            print(i, j, k)

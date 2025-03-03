import numpy as np

# Въведете стойностите на квадратната матрица 3х3
print('Въведете стойностите на квадратната матрица 3х3 като запишете числата разделени с интервал:')

# Въвеждане на стойностите с формат за подравняване
matrix_list = []
for i in range(3):
    row = input().split()
    matrix_list.append([int(num) for num in row])

A = np.array([[matrix_list[0][0], matrix_list[0][1], matrix_list[0][2]],
              [matrix_list[1][0], matrix_list[1][1], matrix_list[1][2]],
              [matrix_list[2][0], matrix_list[2][1], matrix_list[2][2]]])

# Отпечатване за проверка
for row in matrix_list:
    print('|{:>5} {:>5} {:>5}|'.format(*row))

# Изчисляване на детерминантата
det = ((matrix_list[0][0] * matrix_list[1][1] * matrix_list[2][2] +
                 matrix_list[0][1] * matrix_list[1][2] * matrix_list[2][0] +
                 matrix_list[0][2] * matrix_list[1][0] * matrix_list[2][1]) -
                (matrix_list[2][0] * matrix_list[1][1] * matrix_list[0][2] +
                 matrix_list[2][1] * matrix_list[1][2] * matrix_list[0][0] +
                 matrix_list[2][2] * matrix_list[1][0] * matrix_list[0][1]))

print(f'Стойността на детерминантата е: {det}')

oppositive_matrix_list = [[matrix_list[1][1]*matrix_list[2][2] - matrix_list[2][1]*matrix_list[1][2], (-1)*(matrix_list[0][1]*matrix_list[2][2] - matrix_list[2][1]*matrix_list[0][2]), matrix_list[0][1]*matrix_list[1][2] - matrix_list[1][1]*matrix_list[0][2]],
                              [(-1)*(matrix_list[1][0]*matrix_list[2][2] - matrix_list[2][0]*matrix_list[1][2]), matrix_list[0][0]*matrix_list[2][2] - matrix_list[2][0]*matrix_list[0][2], (-1)*(matrix_list[0][0]*matrix_list[1][2] - matrix_list[1][0]*matrix_list[0][2])],
                             [matrix_list[1][0]*matrix_list[2][1] - matrix_list[2][0]*matrix_list[1][1], (-1)*(matrix_list[0][0]*matrix_list[2][1] - matrix_list[2][0]*matrix_list[0][1]), matrix_list[0][0]*matrix_list[1][1] - matrix_list[1][0]*matrix_list[0][1]]]

print(f"Обратната матрица е:")
for row in oppositive_matrix_list:
    print('|{:>5} {:>5} {:>5}|'.format(*row))

A_inv = np.array(oppositive_matrix_list)

print('Посочете типа уравнение, по който ще работите (A*x=B или x*A=B)')
exer = input()

B_matrix_list = []
B = np.array(B_matrix_list)

if exer == "A*x=B":
    print("Формулата е: x = A^(−1).B")

    print("Въведете типа на втората матрица (3х3 / 3х2 / 3х1 / 2х3 / 2х2 / 1х1 / 1х3 / 1х2)")

    matrix_type = input()

    if matrix_type == "3х3":
        for i in range(3):
            row = input().split()
            B_matrix_list.append([int(num) for num in row])

    elif matrix_type == "3х2":
        for i in range(3):
            row = input().split()
            B_matrix_list.append([int(num) for num in row])

    elif matrix_type == "3х1":
        for i in range(3):
            row = input().split()
            B_matrix_list.append([int(num) for num in row])
    else:
        print("Матриците не могат да бъдат умножени")

    #C = det * (A_inv * B)
    B = np.array(B_matrix_list)
    C = np.dot(A_inv, B)
    C_matrix_list = C.tolist()
    print("Резултатната матрица Х е:")
    for row in C_matrix_list:
        print(' '.join(f'{num}/{det}' for num in row))

elif exer == "x*A=B":
    print("Формулата е: x = B.A^(−1)")

    print('Въведете типа на втората матрица (3х3 / 3х2 / 3х1 / 2х3 / 2х2 / 1х1 / 1х3 / 1х2)')
    matrix_type = input()

    if matrix_type == "3х3":
        for i in range(3):
            row = input().split()
            B_matrix_list.append([int(num) for num in row])

    elif matrix_type == "2х3":
        for i in range(2):
            row = input().split()
            B_matrix_list.append([int(num) for num in row])

    elif matrix_type == "1х3":
        for i in range(1):
            row = input().split()
            B_matrix_list.append([int(num) for num in row])
    else:
        print("Матриците не могат да бъдат умножени")

    #C = (B * A_inv) * det
    B = np.array(B_matrix_list)
    C = np.dot(B, A_inv)
    C_matrix_list = C.tolist()
    print("Резултатната матрица Х е:")
    for row in C_matrix_list:
        print(' '.join(f'{num}/{det}' for num in row))
        #print('|{:>5} {:>5} {:>5}|'.format(*row))
else:
    print("Имате грешка в изписването на уравнението")

# Въвеждане на списък от числа, добавяне на нови числа при определени условия
num = int(input("Въведете дължината на списъка от n елементи: "))
my_list = []

for i in range(num):
    print("Добавете число: ")
    my_list.append(int(input()))

print("Готовият списък е: ", my_list)

new_list = []
for j in range(num):
    new_list.append(my_list[j])
    if j < num - 1 and j % 2 == 0:
        new = my_list[j] + my_list[j + 1]
        new_list.append(new)
print("Новият списък е: ", new_list)

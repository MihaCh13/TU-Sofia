# Печатане на пирамида от звезди
num = int(input("Въведете число: "))
for i in range(1, num + 1):
    stars = '*' * i
    spaces = ' ' * (num - i)
    print(spaces + stars + spaces)

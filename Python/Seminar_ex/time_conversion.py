# Преобразуване на минути в дни, часове и минути

minuts = int(input("Въведете минутите: "))
minutes = minuts
day = minutes // 1440
minutes %= 1440
h = minutes // 60
minutes %= 60
print(f"{minuts} минути са равни на {day} дни {h} часа и {minutes} минути")

# Оценка според брой точки

points = int(input("Въведете вашия резултат: "))
if points <= 20:
    print("Слаб (2)")
elif points <= 45:
    print("Среден (3)")
elif points <= 65:
    print("Добър (4)")
elif points <= 85:
    print("Мн. Добър (5)")
else:
    print("Отличен (6)")

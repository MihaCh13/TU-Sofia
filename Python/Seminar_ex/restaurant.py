"""
Входни дании които въвежда потребителя:
Име на ресторант:
Адрес:
Име на ястие:
Цена на ястие:
последните две данни са намират в цикъл който се върти докато потребителя не въведе 
отговор "Не" на въпроса ще добавите ли още нещо в менюто, ако отговора е да цикъла се завърта отново

първата функция съдържа:
Въвежда се номер на масата
Поръчват се желаните ястия като ако са повече от едно се разделят със запетая

Втората функция съдържа:
информация за касовия бон:
Име на ресторант
Адрес
Номер на маса
принтира се ред от звездички 
изброява се всяко поръчано ястие на нов ред във формата "ястие – цена в лв"
най отдолу се изписва общата стойност която клиента трябва да плати
"""

class Restaurant:
    def __init__(self, name, address):
        self.name = name
        self.address = address
        self.menu = {}

    def add_dish(self, dish_name, price):
        self.menu[dish_name] = price

    def print_receipt(self, table_number, ordered_dishes):
        total = 0
        print("Касов бон:")
        print(f"\n{self.name}\n{self.address}\nМаса № {table_number}")
        print("*" * 30)
        for dish in ordered_dishes:
            if dish in self.menu:
                price = self.menu[dish]
                total += price
                print(f"{dish} – {price} лв")
            else:
                print(f"{dish} не е в менюто")
        print("*" * 30)
        print(f"Обща сума: {total:.2f} лв")

def menu_input():
    name = input("Въведете име на ресторант: ")
    address = input("Въведете адрес: ")
    restaurant = Restaurant(name, address)

    while True:
        dish_name = input("Въведете име на ястие: ")
        price = float(input("Въведете цена на ястие: "))
        restaurant.add_dish(dish_name, price)
        add_more = input("Ще добавите ли още нещо в менюто? (да/не): ").strip().lower()
        if add_more == "не":
            break

    table_number = input("\nВъведете номер на масата: ")
    ordered_dishes = input("Въведете поръчани ястия (разделени със запетая): ").split(', ')

    restaurant.print_receipt(table_number, ordered_dishes)

menu_input()

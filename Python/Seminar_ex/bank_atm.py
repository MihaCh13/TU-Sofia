"""
входни данни които въвежда потребителя:
IBAN
Баланс по сметка
ПИН

конзолата принтира съобщение за избор на операция от менюто
Меню:
1. Депозит (сумата се прибавя към вече съществуващата)
2. Теглене (потребителя си въвежда на ново пина и се проверява дали е същия като въведения в началото
проверява се дали операцията е възможна, ако желаната сума е по-голяма от наличната не може да се осъществи
накрая трябва да се изведе информация за наличната сума, отанала след тегленето, ако операцията е била осъществена )
3. Информация (извежда баланса и IBAN)
4. Изход (извежда се съобщение "Благодарим за доверието")

Да се използват класове и обекти
"""

class BankAccount:
    def __init__(self, iban, balance, pin):
        self.iban = iban
        self.balance = balance
        self.pin = pin

    def deposit(self, amount):
        self.balance += amount
        print(f"Балансът след депозита е: {self.balance} лв")

    def withdraw(self, amount, pin):
        if pin != self.pin:
            print("Невалиден ПИН")
            return
        if amount > self.balance:
            print("Недостатъчна наличност")
            return
        self.balance -= amount
        print(f"Балансът след тегленето е: {self.balance} лв")

    def show_info(self):
        print(f"IBAN: {self.iban}")
        print(f"Баланс: {self.balance} лв")

def main():
    # Входни данни от потребителя
    iban = input("Въведете IBAN: ")
    balance = float(input("Въведете начален баланс: "))
    pin = input("Въведете ПИН: ")

    account = BankAccount(iban, balance, pin)

    while True:
        print("\nМеню:")
        print("1. Депозит")
        print("2. Теглене")
        print("3. Информация")
        print("4. Изход")

        choice = input("Изберете операция (1-4): ")

        if choice == "1":
            amount = float(input("Въведете сума за депозит: "))
            account.deposit(amount)
        elif choice == "2":
            amount = float(input("Въведете сума за теглене: "))
            pin = input("Въведете ПИН отново: ")
            account.withdraw(amount, pin)
        elif choice == "3":
            account.show_info()
        elif choice == "4":
            print("Благодарим за доверието")
            break
        else:
            print("Невалиден избор, моля опитайте отново")

main()

# Игра: Камък, ножица, хартия

import random
options = ["камък", "ножица", "хартия"]
user_choice = input("Изберете камък, ножица или хартия: ").lower()
if user_choice not in options:
    print("Некоректен избор! Моля изберете камък, ножица или хартия.")
else:
    computer_choice = random.choice(options)
    print(f"Компютърът избра: {computer_choice}")
    if user_choice == computer_choice:
        print("Равенство!")
    elif (user_choice == "камък" and computer_choice == "ножица") or \
         (user_choice == "ножица" and computer_choice == "хартия") or \
         (user_choice == "хартия" and computer_choice == "камък"):
        print("Вие спечелихте!")
    else:
        print("Вие загубихте!")

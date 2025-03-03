# Проверка дали число е палиндром

def is_palindrome(number):
    return str(number) == str(number)[::-1]

number = int(input("Въведете число: "))
if is_palindrome(number):
    print("Числото е палиндром")
else:
    print("Числото не е палиндром")

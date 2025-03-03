# Рекурсивна функция за изчисляване на сумата на числата от k до 0

def tri_recursion(k):
    if k >= 0:
        result = k + tri_recursion(k - 1)  # Извикваме функцията рекурсивно с k-1
        print(result)  # Отпечатваме текущия резултат
        return result  # Връщаме резултата
    else:
        return 0  # При достигане на 0, прекратяваме рекурсията

print("\n\nRecursion Example Results")
tri_recursion(10)

import addition
import subtraction
import multiplication
import division


def main():
    print("Калкулатор за аритметични операции")
    a = int(input("Въведете първото число: "))
    b = int(input("Въведете второто число: "))

    print("Изберете операция:")
    print("1. Събиране")
    print("2. Изваждане")
    print("3. Умножение")
    print("4. Деление")

    choice = input("Вашият избор (1/2/3/4): ")

    if choice == '1':
        print(f"Резултатът от събирането: {addition.add(a, b)}")
    elif choice == '2':
        print(f"Резултатът от изваждането: {subtraction.subtract(a, b)}")
    elif choice == '3':
        print(f"Резултатът от умножението: {multiplication.multiply(a, b)}")
    elif choice == '4':
        print(f"Резултатът от делението: {division.divide(a, b)}")
    else:
        print("Невалиден избор. Опитайте отново.")


if __name__ == "__main__":
    main()

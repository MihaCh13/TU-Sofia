import triangle
import square
import rectangle
import rhombus
import trapezoid

def main():
    print("Изчисляване на площи на геометрични фигури")

    # Триъгълник
    a = int(input("Въведете страната а (триъгълник): "))
    ha = int(input("Въведете височината към страната а (триъгълник): "))
    print(f"Площ на триъгълника: {triangle.area(a, ha)}")

    # Квадрат
    a1 = int(input("Въведете страната а (квадрат): "))
    print(f"Площ на квадрата: {square.area(a1)}")

    # Правоъгълник
    a2 = int(input("Въведете страната а (правоъгълник): "))
    b = int(input("Въведете страната b (правоъгълник): "))
    print(f"Площ на правоъгълника: {rectangle.area(a2, b)}")

    # Ромб
    a3 = int(input("Въведете страната а (ромб): "))
    ha1 = int(input("Въведете височината към страната а (ромб): "))
    print(f"Площ на ромба: {rhombus.area(a3, ha1)}")

    # Трапец
    a4 = int(input("Въведете страната а (трапец): "))
    b1 = int(input("Въведете страната b (трапец): "))
    ha2 = int(input("Въведете височината (трапец): "))
    print(f"Площ на трапеца: {trapezoid.area(a4, b1, ha2)}")

if __name__ == "__main__":
    main()

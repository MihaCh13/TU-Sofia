num = input("Въведете число: ")
def palindrom(a):
    my_list = [int(digit) for digit in a]
    my_list.reverse()
    r_num = ''.join(map(str, my_list))
    return r_num
if num == palindrom(num):
    print(f"Числото {num} е палиндром")
else:
    print(f"Числото {num} не е палиндром")

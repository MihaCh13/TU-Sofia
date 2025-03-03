# Въвеждане на число и създаване на речник, където ключовете са числата от 1 до n, а стойностите са в обратен ред
num = int(input("Въведете цяло число: "))
my_list = []

for i in range(1, num + 1):
    my_list.append(i)

num_dict = {}
new_list = list(reversed(my_list))

for j in range(num):
    num_dict[my_list[j]] = new_list[j]
print(num_dict)

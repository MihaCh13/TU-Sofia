# Броене на срещанията на всеки символ в текст
text = input("Въведете текст или набор от символи: ")
char_list = list(text)

char_count = {}
for char in char_list:
    if char in char_count:
        char_count[char] += 1
    else:
        char_count[char] = 1
print(char_count)

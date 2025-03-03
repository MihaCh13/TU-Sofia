# Извличане на текст от PDF файл

import PyPDF2

filename = r'C:\Users\user\Desktop\folder\name.pdf'

with open(filename, 'rb') as file:
    reader = PyPDF2.PdfReader(file)
    for page_num in range(len(reader.pages)):
        page = reader.pages[page_num]
        print(page.extract_text())

# Изчисляване на крайна цена с ДДС

suma = float(input("Въведете стойността на артикула без ДДС: "))
dds = float(input("Въведете ДДС-то в проценти: "))
print(f"Стойността на закупения от вас артикул е: {suma + suma * (0.01 * dds):.2f} лв")

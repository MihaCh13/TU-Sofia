# Работа с JSON – преобразуване на Python обект в JSON

import json

# Примерен Python обект (речник)
python_obj = {
    "име": "Иван",
    "възраст": 30,
    "град": "София"
}

# Преобразуване на Python обекта в JSON данни
json_data = json.dumps(python_obj, ensure_ascii=False, indent=4)

# Печат на JSON данните
print(json_data)

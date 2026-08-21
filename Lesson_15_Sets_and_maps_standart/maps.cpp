/*
Словарь - это структура данных, которая хранит пары "ключ → значение":
- Ключ - уникальный идентификатор (например, имя студента)
- Значение - данные, связанные с ключом (например, возраст студента)

Когда использовать map?
+--------------------------------------+----------------------------------------+
| Ситуация                             | Решение                                |
+--------------------------------------+----------------------------------------+
| Нужно хранить пары "ключ → значение" | map / unordered_map                    |
| Ключи должны быть отсортированы      | map                                    |
| Нужна максимальная скорость          | unordered_map                          |
| Ключи - простые числа или строки     | map / unordered_map                    |
| Порядок элементов не важен           | unordered_map                          |
+--------------------------------------+----------------------------------------+

Отличие от других структур:
+----------------+----------------------------+-----------------------+
| Структура      | Что хранит                 | Быстрый поиск по      |
+----------------+----------------------------+-----------------------+
| map            | пары (ключ, значение)      | ключу (O(log n))      |
| unordered_map  | пары (ключ, значение)      | ключу (O(1))          |
| vector         | элементы (индекс, значение)| индексу (O(1))        |
| set            | только ключи               | ключу (O(log n))      |
+----------------+----------------------------+-----------------------+

Методы:
+---------------------+--------------------------------------------------+
| Метод               | Описание                                         |
+---------------------+--------------------------------------------------+
| insert({key,value}) | Добавить пару ключ-значение                      |
| emplace(key,value)  | Эффективная вставка (без копирования)            |
| insert_or_assign()  | Вставить или обновить (C++17)                    |
| erase(key)          | Удалить элемент по ключу                         |
| erase(iterator)     | Удалить элемент по итератору                     |
| find(key)           | Поиск элемента (возвращает итератор)             |
| contains(key)       | Проверка наличия ключа (C++20)                   |
| operator[](key)     | Доступ/создание элемента по ключу                |
| at(key)             | Доступ с проверкой (бросает исключение)          |
| size()              | Количество элементов в словаре                   |
| empty()             | Проверка на пустоту (true - пусто)               |
| clear()             | Очистить весь словарь                            |
| begin()/end()       | Итераторы для обхода словаря                     |
+---------------------+--------------------------------------------------+

Важные особенности словарей:
- Ключи уникальны - каждый ключ может встречаться только один раз
- Ключи могут быть любого типа (с поддержкой сравнения для map)
- operator[] создаёт ключ, если его нет (будьте осторожны!)
- Для проверки используйте find(), а не operator[]
- unordered_map быстрее, но не сохраняет порядок

Итог: Словари незаменимы, когда нужно быстро находить данные по уникальному ключу!
*/

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>      // <-- ДОБАВИТЬ ЭТУ СТРОКУ
#include <string>

using namespace std;

int main() {
    // ===== СОЗДАНИЕ И ИНИЦИАЛИЗАЦИЯ =====
    
    // Пустой словарь (ключ -> значение)
    map<string, int> ages;
    
    // Инициализация списком
    map<string, int> students = {
        {"Alice", 20},
        {"Bob", 22},
        {"Charlie", 21}
    };
    
    // Копирование
    map<string, int> copy_map(students);
    
    // Из массивов
    string names[] = {"John", "Jane", "Joe"};
    int scores[] = {85, 92, 78};
    map<string, int> from_arrays;
    for (int i = 0; i < 3; i++) {
        from_arrays[names[i]] = scores[i];
    }
    
    // ===== ВЫВОД В ТЕРМИНАЛ =====
    
    cout << "Студенты и возраст:" << endl;
    for (const auto& pair : students) {
        cout << pair.first << ": " << pair.second << " лет" << endl;
    }
    
    // Вывод с итераторами
    cout << "\nОценки студентов:" << endl;
    for (auto it = from_arrays.begin(); it != from_arrays.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }
    
    // ===== ДОБАВИТЬ =====
    
    ages["Alice"] = 25;        // через оператор []
    ages.insert({"Bob", 30});  // через insert
    ages.emplace("Charlie", 28); // через emplace (эффективнее)
    
    // Вставка, если ключа нет
    auto result = ages.insert({"Alice", 99}); // не вставится, т.к. Alice уже есть
    if (!result.second) {
        cout << "\nAlice уже существует со значением: " << ages["Alice"] << endl;
    }
    
    // Вставка с проверкой
    ages.insert_or_assign("David", 35); // C++17: вставить или обновить
    
    cout << "\nВозраст после добавлений:" << endl;
    for (const auto& p : ages) {
        cout << p.first << ": " << p.second << endl;
    }
    
    // ===== УДАЛИТЬ =====
    
    ages.erase("Alice");        // удаление по ключу
    
    // Удаление по итератору
    auto it = ages.find("Bob");
    if (it != ages.end()) {
        ages.erase(it);
    }
    
    // Удаление по диапазону
    auto start = ages.find("Charlie");
    auto end = ages.find("David");
    if (start != ages.end() && end != ages.end()) {
        ages.erase(start, ++end);
    }
    
    cout << "\nПосле удалений:" << endl;
    for (const auto& p : ages) {
        cout << p.first << ": " << p.second << endl;
    }
    
    // ===== ДРУГИЕ ДЕЙСТВИЯ =====
    
    map<string, int> map1 = {
        {"A", 1}, {"B", 2}, {"C", 3}
    };
    map<string, int> map2 = {
        {"C", 30}, {"D", 4}, {"E", 5}
    };
    
    // 1. РАЗМЕР и ПРОВЕРКА
    cout << "\nРазмер map1: " << map1.size() << endl;
    cout << "map1 пуст? " << (map1.empty() ? "Да" : "Нет") << endl;
    
    // 2. ПОИСК ПО КЛЮЧУ
    if (map1.find("B") != map1.end()) {
        cout << "Ключ B найден, значение: " << map1["B"] << endl;
    }
    
    // 3. ДОСТУП С ПРОВЕРКОЙ (без создания нового ключа)
    auto itB = map1.find("B");
    if (itB != map1.end()) {
        cout << "Значение B: " << itB->second << endl;
    }
    
    // 4. ПРОВЕРКА НАЛИЧИЯ (C++20)
    // if (map1.contains("X")) { cout << "Есть X" << endl; }
    
    // 5. ОБЪЕДИНЕНИЕ словарей (если ключ совпадает - приоритет у map1)
    map<string, int> merged = map1;
    for (const auto& p : map2) {
        if (merged.find(p.first) == merged.end()) {
            merged[p.first] = p.second;
        }
    }
    cout << "\nОбъединение map1 и map2:" << endl;
    for (const auto& p : merged) {
        cout << p.first << ": " << p.second << endl;
    }
    
    // 6. ПОЛУЧЕНИЕ ТОЛЬКО КЛЮЧЕЙ или ЗНАЧЕНИЙ
    cout << "\nКлючи map1: ";
    for (const auto& p : map1) {
        cout << p.first << " ";
    }
    cout << endl;
    
    cout << "Значения map1: ";
    for (const auto& p : map1) {
        cout << p.second << " ";
    }
    cout << endl;
    
    // 7. ОБНОВЛЕНИЕ ЗНАЧЕНИЯ
    map1["B"] = 20;  // обновление существующего
    cout << "\nПосле обновления B: " << map1["B"] << endl;
    
    // 8. ОЧИСТКА
    map1.clear();
    cout << "После очистки size: " << map1.size() << endl;
    
    // ===== UNORDERED_MAP (неотсортированный словарь) =====
    
    unordered_map<string, int> unordered_dict = {
        {"apple", 1},
        {"banana", 2},
        {"orange", 3}
    };
    
    cout << "\nНеотсортированный словарь (порядок может быть произвольным):" << endl;
    for (const auto& p : unordered_dict) {
        cout << p.first << ": " << p.second << endl;
    }
    
    // ===== РАБОТА С ВЛОЖЕННЫМИ СЛОВАРЯМИ =====
    
    map<string, map<string, int>> grades = {
        {"Alice", {{"Math", 90}, {"Physics", 85}}},
        {"Bob", {{"Math", 75}, {"Chemistry", 88}}}
    };
    
    cout << "\nОценки студентов:" << endl;
    for (const auto& student : grades) {
        cout << student.first << ":" << endl;
        for (const auto& subject : student.second) {
            cout << "  " << subject.first << ": " << subject.second << endl;
        }
    }
    
    // ===== КОМПЛЕКСНЫЙ ПРИМЕР =====
    
    map<string, vector<int>> student_scores = {
        {"Alice", {85, 90, 78}},
        {"Bob", {92, 88, 95}}
    };
    
    cout << "\nСредние баллы:" << endl;
    for (const auto& student : student_scores) {
        int sum = 0;
        for (int score : student.second) {
            sum += score;
        }
        double avg = static_cast<double>(sum) / student.second.size();
        cout << student.first << ": " << avg << endl;
    }
    
    // ===== ПОЛЬЗОВАТЕЛЬСКИЙ КОМПАРАТОР =====
    
    map<int, string, greater<int>> reverse_map = {
        {1, "one"}, {2, "two"}, {3, "three"}
    };
    cout << "\nСловарь с обратным порядком:" << endl;
    for (const auto& p : reverse_map) {
        cout << p.first << ": " << p.second << endl;
    }
    
    return 0;
}
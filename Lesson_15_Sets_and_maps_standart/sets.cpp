/*
*/

/*
+-----------------+------------------------------------------+
| Метод           | Описание                                 |
+-----------------+------------------------------------------+
| insert(value)   | Добавить элемент                         |
| erase(value)    | Удалить элемент по значению              |
| erase(iterator) | Удалить элемент по итератору             |
| find(value)     | Поиск элемента (возвращает итератор)     |
| contains(value) | Проверка наличия элемента (C++20)        |
| size()          | Количество элементов в множестве         |
| empty()         | Проверка на пустоту (true - пусто)       |
| clear()         | Очистить всё множество                   |
| begin()/end()   | Итераторы для обхода множества           |
+-----------------+------------------------------------------+
*/

#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
    // ===== СОЗДАНИЕ И ИНИЦИАЛИЗАЦИЯ =====
    
    // Пустое множество
    set<int> numbers;
    
    // Инициализация списком
    set<int> primes = {2, 3, 5, 7, 11, 13};
    
    // Копирование
    set<int> copy_set(primes);
    
    // Из массива
    int arr[] = {10, 20, 30, 20, 10}; // дубликаты будут удалены
    set<int> from_array(arr, arr + 5);
    
    // ===== ВЫВОД В ТЕРМИНАЛ =====
    
    cout << "Простые числа: ";
    for (int num : primes) {
        cout << num << " ";
    }
    cout << endl;
    
    // Вывод с итераторами
    cout << "Из массива: ";
    for (auto it = from_array.begin(); it != from_array.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // ===== ДОБАВИТЬ =====
    
    numbers.insert(10);    // вставка одного элемента
    numbers.insert(20);
    numbers.insert(30);
    numbers.insert(20);    // дубликат не будет добавлен
    
    // Вставка нескольких элементов
    numbers.insert({40, 50, 60});
    
    cout << "Множество чисел: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    // ===== УДАЛИТЬ =====
    
    numbers.erase(30);     // удаление по значению
    numbers.erase(20);     // удаление по значению
    
    // Удаление по итератору
    auto it = numbers.find(40);
    if (it != numbers.end()) {
        numbers.erase(it); // удаление элемента, на который указывает итератор
    }
    
    // Удаление диапазона
    auto start = numbers.find(50);
    auto end = numbers.find(60);
    if (start != numbers.end() && end != numbers.end()) {
        numbers.erase(start, ++end); // удалить от 50 до 60 включительно
    }
    
    cout << "После удалений: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    // ===== ДРУГИЕ ДЕЙСТВИЯ =====
    
    set<int> set1 = {1, 2, 3, 4, 5};
    set<int> set2 = {4, 5, 6, 7, 8};
    
    // 1. РАЗМЕР и ПРОВЕРКА НА ПУСТОТУ
    cout << "Размер set1: " << set1.size() << endl;
    cout << "set1 пуст? " << (set1.empty() ? "Да" : "Нет") << endl;
    
    // 2. ПОИСК ЭЛЕМЕНТА
    if (set1.find(3) != set1.end()) {
        cout << "Число 3 найдено в set1" << endl;
    }
    
    // 3. ПРОВЕРКА НАЛИЧИЯ (C++20)
    // if (set1.contains(5)) { cout << "Есть 5" << endl; }
    
    // 4. ОБЪЕДИНЕНИЕ
    set<int> union_set;
    for (int x : set1) union_set.insert(x);
    for (int x : set2) union_set.insert(x);
    cout << "Объединение: ";
    for (int x : union_set) cout << x << " ";
    cout << endl;
    
    // 5. ПЕРЕСЕЧЕНИЕ
    set<int> intersection;
    for (int x : set1) {
        if (set2.find(x) != set2.end()) {
            intersection.insert(x);
        }
    }
    cout << "Пересечение: ";
    for (int x : intersection) cout << x << " ";
    cout << endl;
    
    // 6. РАЗНОСТЬ (set1 - set2)
    set<int> difference;
    for (int x : set1) {
        if (set2.find(x) == set2.end()) {
            difference.insert(x);
        }
    }
    cout << "Разность (set1 - set2): ";
    for (int x : difference) cout << x << " ";
    cout << endl;
    
    // 7. СИММЕТРИЧЕСКАЯ РАЗНОСТЬ
    set<int> sym_diff;
    for (int x : set1) {
        if (set2.find(x) == set2.end()) sym_diff.insert(x);
    }
    for (int x : set2) {
        if (set1.find(x) == set1.end()) sym_diff.insert(x);
    }
    cout << "Симметрическая разность: ";
    for (int x : sym_diff) cout << x << " ";
    cout << endl;
    
    // 8. ОЧИСТКА
    numbers.clear();
    cout << "После очистки size: " << numbers.size() << endl;
    
    // 9. ПРОВЕРКА ВКЛЮЧЕНИЯ (подмножество)
    set<int> small = {1, 2};
    set<int> big = {1, 2, 3, 4};
    
    bool is_subset = true;
    for (int x : small) {
        if (big.find(x) == big.end()) {
            is_subset = false;
            break;
        }
    }
    cout << "small является подмножеством big? " << (is_subset ? "Да" : "Нет") << endl;
    
    // ===== МНОЖЕСТВО С ДРУГИМИ ТИПАМИ =====
    
    set<string> fruits = {"apple", "banana", "orange"};
    
    // С пользовательским компаратором (обратный порядок)
    set<int, greater<int>> descending = {1, 2, 3, 4, 5};
    cout << "Обратный порядок: ";
    for (int x : descending) cout << x << " ";
    cout << endl;
    
    return 0;
}
// Lesson_09_References


/*
Ссылки в C++
Суть
Ссылка — это псевдоним (альтернативное имя) для существующей переменной.
Она не копирует значение, а дает доступ к той же области памяти.

Основные особенности
- Обязательно инициализируется при создании
- Не может быть nullptr (в отличие от указателей)
- Не требует оператора разыменования *
- Не может быть перепривязана к другой переменной
- Работает как "постоянный указатель" с удобным синтаксисом
*/

#include <iostream>
using namespace std;

// ===== РАЗДЕЛ 1: ОСНОВЫ ССЫЛОК =====
void demo_basics() {
    cout << "\n=== 1. ОСНОВЫ ССЫЛОК ===\n";
    
    int a = 10;
    int &ref = a;  // ref — ссылка на a
    
    cout << "a = " << a << ", ref = " << ref << endl;
    
    ref = 20;  // меняем через ссылку
    cout << "После ref = 20: a = " << a << ", ref = " << ref << endl;
    
    int b = 30;
    ref = b;  // НЕ перепривязка! Это просто a = b
    cout << "После ref = b (b=30): a = " << a << ", ref = " << ref << ", b = " << b << endl;
    
    // ref = nullptr;  // ОШИБКА: ссылка не может быть nullptr
}

// ===== РАЗДЕЛ 2: ССЫЛКИ В ФУНКЦИЯХ (ПАРАМЕТРЫ) =====
void increment(int &x) {
    x++;  // меняем оригинал
}

void demo_params() {
    cout << "\n=== 2. ПЕРЕДАЧА ПАРАМЕТРОВ ПО ССЫЛКЕ ===\n";
    
    int num = 5;
    cout << "До increment: num = " << num << endl;
    increment(num);
    cout << "После increment: num = " << num << endl;
}

// ===== РАЗДЕЛ 3: ВОЗВРАТ ПО ССЫЛКЕ =====
int& getElement(int arr[], int index) {
    return arr[index];  // возвращаем ссылку на элемент
}

void demo_return() {
    cout << "\n=== 3. ВОЗВРАТ ПО ССЫЛКЕ ===\n";
    
    int arr[3] = {1, 2, 3};
    cout << "Исходный массив: ";
    for (int i = 0; i < 3; i++) cout << arr[i] << " ";
    cout << endl;
    
    getElement(arr, 1) = 10;  // меняем элемент через ссылку
    cout << "После getElement(arr, 1) = 10: ";
    for (int i = 0; i < 3; i++) cout << arr[i] << " ";
    cout << endl;
}

// ===== РАЗДЕЛ 4: КОНСТАНТНЫЕ ССЫЛКИ =====
void printValue(const int &x) {  // защита от изменения
    cout << "Значение: " << x << endl;
    // x = 10;  // ОШИБКА: нельзя изменить const ссылку
}

void demo_const_refs() {
    cout << "\n=== 4. КОНСТАНТНЫЕ ССЫЛКИ ===\n";
    
    int value = 42;
    printValue(value);      // передача переменной
    printValue(100);        // передача временного объекта (const int&)
    
    const int &ref = 999;   // временный объект живет пока жива ссылка
    cout << "Временный объект через const ссылку: " << ref << endl;
}

// ===== РАЗДЕЛ 5: ССЫЛКИ VS УКАЗАТЕЛИ =====
void demo_vs_pointers() {
    cout << "\n=== 5. ССЫЛКИ VS УКАЗАТЕЛИ ===\n";
    
    int x = 5, y = 10;
    int *ptr = &x;   // указатель
    int &ref = x;    // ссылка
    
    cout << "x = " << x << ", y = " << y << endl;
    cout << "ptr указывает на " << *ptr << ", ref ссылается на " << ref << endl;
    
    ptr = &y;        // OK: указатель можно перепривязать
    ref = y;         // НЕ перепривязка! Это x = y (x становится 10)
    
    cout << "После ptr = &y, ref = y:" << endl;
    cout << "x = " << x << ", y = " << y << endl;
    cout << "ptr указывает на " << *ptr << ", ref ссылается на " << ref << endl;
    
    *ptr = 20;       // разыменование указателя
    ref = 30;        // без разыменования
    
    cout << "После *ptr = 20, ref = 30:" << endl;
    cout << "x = " << x << ", y = " << y << endl;
    cout << "ptr указывает на " << *ptr << ", ref ссылается на " << ref << endl;
    
    ptr = nullptr;   // OK: указатель может быть нулевым
    cout << "ptr = nullptr (разыменовывать нельзя!)" << endl;
    // ref = nullptr; // ОШИБКА: ссылка не может быть нулевой
}

// ===== РАЗДЕЛ 6: ПРАКТИЧЕСКОЕ ПРИМЕНЕНИЕ =====
void swapValues(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void demo_practical() {
    cout << "\n=== 6. ПРАКТИЧЕСКОЕ ПРИМЕНЕНИЕ ===\n";
    
    int first = 100, second = 200;
    cout << "До swap: first = " << first << ", second = " << second << endl;
    swapValues(first, second);
    cout << "После swap: first = " << first << ", second = " << second << endl;
    
    // Ссылка как псевдоним для длинных имен
    struct Data {
        int very_long_field_name = 777;
    };
    Data data;
    int &alias = data.very_long_field_name;  // удобный псевдоним
    cout << "data.very_long_field_name = " << data.very_long_field_name << endl;
    alias = 888;
    cout << "После alias = 888: data.very_long_field_name = " << data.very_long_field_name << endl;
}

// ===== ГЛАВНАЯ ФУНКЦИЯ =====
int main() {
    cout << "======= ССЫЛКИ В C++ =======\n";
    
    demo_basics();
    demo_params();
    demo_return();
    demo_const_refs();
    demo_vs_pointers();
    demo_practical();
    
    cout << "\n============================\n";
    return 0;
}
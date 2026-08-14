// Указатель — это переменная, которая хранит адрес памяти другой переменной.

/* Основные операции:
* — оператор разыменования (получение значения по адресу)
& — оператор взятия адреса
nullptr — нулевой указатель (ни на что не указывает)
*/

#include <iostream>
using namespace std;

int main() {
    // ===== ОБЪЯВЛЕНИЕ И ИНИЦИАЛИЗАЦИЯ =====
    int number = 42;           // обычная переменная
    int* ptr = &number;        // указатель на number
    
    cout << "=== ОСНОВНЫЕ ОПЕРАЦИИ ===" << endl;
    cout << "Значение number: " << number << endl;
    cout << "Адрес number (&number): " << &number << endl;
    cout << "Значение ptr (адрес): " << ptr << endl;
    cout << "Значение по адресу ptr (*ptr): " << *ptr << endl;
    
    // ===== ИЗМЕНЕНИЕ ЧЕРЕЗ УКАЗАТЕЛЬ =====
    *ptr = 100;                // меняем значение number через указатель
    cout << "\n=== ПОСЛЕ ИЗМЕНЕНИЯ ===" << endl;
    cout << "number: " << number << endl;
    cout << "*ptr: " << *ptr << endl;
    
    // ===== ДИНАМИЧЕСКАЯ ПАМЯТЬ =====
    int* dynamicPtr = new int(10);  // выделение памяти в куче
    cout << "\n=== ДИНАМИЧЕСКАЯ ПАМЯТЬ ===" << endl;
    cout << "dynamicPtr: " << dynamicPtr << endl;
    cout << "*dynamicPtr: " << *dynamicPtr << endl;
    
    *dynamicPtr = 25;
    cout << "Новое значение: " << *dynamicPtr << endl;
    
    delete dynamicPtr;         // ОСВОБОЖДЕНИЕ ПАМЯТИ!
    dynamicPtr = nullptr;      // защита от висячего указателя
    
    // ===== УКАЗАТЕЛЬ НА МАССИВ =====
    int arr[] = {10, 20, 30, 40, 50};
    int* arrPtr = arr;         // имя массива = указатель на 1-й элемент
    
    cout << "\n=== УКАЗАТЕЛИ И МАССИВЫ ===" << endl;
    for(int i = 0; i < 5; i++) {
        cout << "arrPtr[" << i << "] = " << arrPtr[i] << " ";
        cout << "(*(arrPtr+" << i << ") = " << *(arrPtr + i) << ")" << endl;
    }
    
    // ===== АРИФМЕТИКА УКАЗАТЕЛЕЙ =====
    cout << "\n=== АРИФМЕТИКА УКАЗАТЕЛЕЙ ===" << endl;
    cout << "arrPtr указывает на: " << *arrPtr << endl;
    arrPtr++;                  // сдвиг на 1 элемент (4 байта для int)
    cout << "После arrPtr++: " << *arrPtr << endl;
    arrPtr += 2;               // сдвиг на 2 элемента
    cout << "После arrPtr+=2: " << *arrPtr << endl;
    
    // ===== УКАЗАТЕЛЬ НА УКАЗАТЕЛЬ =====
    int** ptrToPtr = &ptr;     // указатель на указатель
    cout << "\n=== УКАЗАТЕЛЬ НА УКАЗАТЕЛЬ ===" << endl;
    cout << "ptrToPtr: " << ptrToPtr << endl;
    cout << "*ptrToPtr: " << *ptrToPtr << endl;
    cout << "**ptrToPtr: " << **ptrToPtr << endl;
    
    // ===== nullptr и проверка =====
    int* nullPtr = nullptr;
    cout << "\n=== nullptr ===" << endl;
    if(nullPtr == nullptr) {
        cout << "nullPtr - нулевой указатель" << endl;
    }
    
    // ВАЖНО: всегда проверяйте указатель перед использованием!
    if(nullPtr != nullptr) {
        cout << "*nullPtr: " << *nullPtr << endl;  // не выполнится
    }
    
    return 0;
}


/*
Ключевые моменты
1. * — может означать:
- объявление указателя (int* ptr)
- разыменование (*ptr = 10)
2. & — оператор взятия адреса

3. Динамическая память:
- new — выделение
- delete — освобождение. Всегда удаляйте! Иначе утечка памяти

4. Опасности:
- Разыменование nullptr → краш
- Утечки памяти (забыли delete)
- Висячие указатели (после delete)

5. Арифметика — сдвиг на sizeof(тип) байт

*/
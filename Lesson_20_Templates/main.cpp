// Lesson 20: Templates

/*
Шаблон — это код, который работает с любым типом (T) и с любым значением (N), известным на этапе компиляции.
Точнее и правильнее: Шаблон — это **рецепт** для генерации кода, который компилятор превращает в конкретную версию для каждого типа/значения

Виды: 
- Функция-шаблон
- Класс-шаблон, в котором метод (функция класса) - мложет быть шаблоном
- Структура - шаблон

В любом случае, template<> пишется строкой выше

Шаблон работает независимо от:
- Типа данных (type parameter)
    template<typename T>  // T - любой тип
    Не важно: int, double, string, свой класс
    Главное: чтобы операции (+, >, =) работали для этого типа

- Значения (non-type parameter)
    template<int N>  // N - конкретное число
    Не важно: размер массива, количество элементов, граница
    Главное: значение известно на этапе компиляции

Коротко:
Шаблон типа — template<typename T> (работает с разными типами)
Шаблон значения — template<int N> (работает с разными числами)
Можно комбинировать: template<typename T, int N> (и тип, и значение)
Шаблон универсален = "не важно ЧТО за тип" + "не важно КАКОЕ значение"

*/

#include <iostream>
using namespace std;

// ===== 1. ФУНКЦИЯ-ШАБЛОН (ТИП) =====
// Что делает: возвращает максимум из двух значений ЛЮБОГО типа
template<typename T>
T maxValue(T a, T b) {
    return (a > b) ? a : b;
}

// ===== 2. ФУНКЦИЯ-ШАБЛОН (ЗНАЧЕНИЕ) =====
// Что делает: умножает число на КОНСТАНТУ (известную на этапе компиляции)
template<int N>
int multiplyByConst(int x) {
    return x * N;  // N - это число, например 5 или 10
}

// ===== 3. ФУНКЦИЯ-ШАБЛОН (ТИП + ЗНАЧЕНИЕ) =====
// Что делает: суммирует все элементы массива ЛЮБОГО ТИПА и ЛЮБОГО РАЗМЕРА
template<typename T, int Size>
T sumArray(T arr[Size]) {
    T sum = 0;
    for (int i = 0; i < Size; i++) sum += arr[i];
    return sum;
}

// ===== 4. КЛАСС-ШАБЛОН (ТИП) =====
// Что делает: коробка для хранения ОДНОГО значения ЛЮБОГО ТИПА
template<typename T>
class Box {
    T data;
public:
    void set(T val) { data = val; }
    T get() { return data; }
};

// ===== 5. КЛАСС-ШАБЛОН (ТИП + ЗНАЧЕНИЕ) =====
// Что делает: хранилище для НЕСКОЛЬКИХ элементов ЛЮБОГО ТИПА и ФИКСИРОВАННОГО РАЗМЕРА
template<typename T, int Size>
class Storage {
    T items[Size];
    int count = 0;
public:
    void add(T item) { if (count < Size) items[count++] = item; }
    void show() { for (int i = 0; i < count; i++) cout << items[i] << " "; }
};

// ===== 6. МЕТОД КЛАССА - ШАБЛОН =====
// Что делает: класс Printer умеет печатать ЛЮБЫЕ ТИПЫ (метод-шаблон)
class Printer {
public:
    template<typename T>
    void print(T value) {
        cout << value << endl;
    }
};

// ===== 7. СТРУКТУРА-ШАБЛОН =====
// Что делает: точка с координатами ЛЮБОГО ТИПА (int, double, float...)
template<typename T>
struct Point {
    T x, y;
};

// ===== 8. КОМБИНАЦИЯ ВСЕГО =====
// Что делает: контейнер с ФИКСИРОВАННЫМ РАЗМЕРОМ для ЛЮБОГО ТИПА,
//            у которого метод process принимает ЛЮБОЙ ДРУГОЙ ТИП
template<typename T, int N>
class Container {
    T data[N];
public:
    template<typename U>
    void process(U value) {
        data[0] = (T)value;  // преобразует U в T
    }
};

int main() {
    // ===== 1. Функция с типом =====
    cout << "1. Максимум: ";
    cout << maxValue(5, 3) << endl;          // 8 (int)
    cout << "   " << maxValue(2.5, 1.2) << endl;      // 3.7 (double)
    
    // ===== 2. Функция со значением =====
    cout << "2. Умножение на 5: ";
    cout << multiplyByConst<5>(10) << endl;    // 50
    
    // ===== 3. Функция с типом + значением =====
    int arr[] = {1, 2, 3, 4, 5};
    cout << "3. Сумма массива: ";
    cout << sumArray<int, 5>(arr) << endl;  // 15
    
    // ===== 4. Класс с типом =====
    Box<int> b1; b1.set(42);
    Box<string> b2; b2.set("Hello");
    cout << "4. Коробки: " << b1.get() << " и " << b2.get() << endl;
    
    // ===== 5. Класс с типом + значением =====
    Storage<int, 3> s;
    s.add(10); s.add(20); s.add(30);
    cout << "5. Хранилище: ";
    s.show();  // 10 20 30
    cout << endl;
    
    // ===== 6. Метод-шаблон в классе =====
    Printer p;
    cout << "6. Печать: ";
    p.print(100);      // int
    p.print(3.14);     // double
    p.print("Hi");     // string
    
    // ===== 7. Структура-шаблон =====
    Point<double> pt{1.5, 2.7};
    cout << "7. Точка: (" << pt.x << ", " << pt.y << ")" << endl;
    
    // ===== 8. Комбинация всего =====
    Container<int, 5> c;
    c.process(3.14);  // double → int
    cout << "8. Контейнер обработал double как int: 3.14 → 3" << endl;
}
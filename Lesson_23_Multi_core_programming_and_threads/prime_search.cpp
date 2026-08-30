#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>
#include <iomanip>

using namespace std;
using namespace chrono;

// Атомарный счётчик — безопасен для нескольких потоков
atomic<int> prime_count = 0;

// Проверка: простое ли число?
bool is_prime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2) {  // До корня из n, только нечётные
        if (n % i == 0) return false;
    }
    return true;
}

// Однопоточный подсчёт
int count_primes_single(int limit) {
    int count = 0;
    for (int i = 1; i <= limit; ++i) {
        if (is_prime(i)) count++;
    }
    return count;
}

// Функция для потока: считает простые в своём диапазоне
void check_range(int start, int end) {
    int local = 0;
    for (int i = start; i <= end; ++i) {
        if (is_prime(i)) local++;
    }
    prime_count += local;  // Безопасно добавляем в общий счётчик
}

// Многопоточный подсчёт
int count_primes_multi(int limit, int threads_count) {
    prime_count = 0;                      // Обнуляем перед запуском
    int range = limit / threads_count;    // Размер куска на поток
    vector<thread> threads;               // Вектор для хранения потоков
    
    // Создаём потоки
    for (int i = 0; i < threads_count; ++i) {
        int start = i * range + 1;        // Начало диапазона
        int end = (i == threads_count - 1) ? limit : (i + 1) * range;  // Конец
        threads.emplace_back(check_range, start, end);  // Запуск потока
    }
    
    // Ждём завершения всех потоков
    for (auto& t : threads) t.join();
    
    return prime_count.load();  // Читаем результат
}

int main() {
    const int LIMIT = 100'000'000;  // 100 миллионов
    int threads = thread::hardware_concurrency();  // Число ядер
    if (threads == 0) threads = 4;
    
    cout << "Поиск простых чисел до " << LIMIT << "\n";
    cout << "Потоков: " << threads << "\n\n";
    
    // ===== ОДНОПОТОЧНЫЙ ТЕСТ =====
    auto start = steady_clock::now();
    int single = count_primes_single(LIMIT);
    auto single_time = duration_cast<milliseconds>(steady_clock::now() - start).count();
    
    cout << "Однопоток: " << single << " простых чисел | " 
         << single_time << " ms\n";
    
    // ===== МНОГОПОТОЧНЫЙ ТЕСТ =====
    start = steady_clock::now();
    int multi = count_primes_multi(LIMIT, threads);
    auto multi_time = duration_cast<milliseconds>(steady_clock::now() - start).count();
    
    cout << "Многопоток (" << threads << "): " << multi << " простых чисел | " 
         << multi_time << " ms\n";
    
    // ===== СРАВНЕНИЕ =====
    cout << "\nУскорение: " << (double)single_time / multi_time << "x\n";
    cout << "Результаты " << (single == multi ? "совпадают" : "НЕ совпадают!") << "\n";
    
    return 0;
}
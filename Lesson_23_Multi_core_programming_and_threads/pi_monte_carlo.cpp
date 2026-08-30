#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include <numeric>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

// Эталонное значение числа Пи (20 знаков после запятой)
const double PI = 3.14159265358979323846;

/**
 * Функция бросает n случайных точек в квадрат [-1, 1] x [-1, 1]
 * и считает, сколько из них попало во вписанный круг радиусом 1.
 * Возвращает количество попаданий.
 */
long long throwPoints(long long n) {
    // thread_local - каждый поток получает свой собственный генератор
    // Это предотвращает блокировки при параллельном доступе
    thread_local mt19937 gen(random_device{}());
    uniform_real_distribution<> dis(-1.0, 1.0);
    
    long long hits = 0;
    for (long long i = 0; i < n; ++i) {
        double x = dis(gen); // случайная координата X от -1 до 1
        double y = dis(gen); // случайная координата Y от -1 до 1
        
        // Проверка: точка внутри круга, если x^2 + y^2 <= R^2 (R=1)
        if (x*x + y*y <= 1.0) {
            hits++; // точка попала в круг
        }
    }
    return hits;
}

int main() {
    // Общее количество точек для симуляции (200 миллионов)
    long long total = 200'000'000;
    
    // Определяем количество аппаратных потоков (ядер)
    unsigned threads = thread::hardware_concurrency();
    
    // Устанавливаем вывод с 12 знаками после запятой
    cout << fixed << setprecision(12);
    cout << "PI (эталон): " << PI << "\n";
    cout << "Количество потоков: " << threads << "\n\n";
    
    // ========== ОДНОПОТОЧНЫЙ РАСЧЁТ ==========
    auto start = high_resolution_clock::now();
    
    // Один поток обрабатывает все точки
    long long hits = throwPoints(total);
    double pi_single = 4.0 * hits / total;
    
    auto end = high_resolution_clock::now();
    auto single_time = duration_cast<milliseconds>(end - start).count();
    
    cout << "Однопоток (1 поток): " << pi_single
         << " | Время: " << single_time << " ms\n";
    
    // ========== МНОГОПОТОЧНЫЙ РАСЧЁТ ==========
    start = high_resolution_clock::now();
    
    vector<thread> pool;           // Вектор потоков
    vector<long long> results(threads); // Результаты каждого потока
    
    // Запускаем потоки, каждый обрабатывает свою порцию точек
    for (unsigned t = 0; t < threads; ++t) {
                // Создаём новый поток и добавляем его в вектор pool
        // [&, t] - лямбда-функция с захватом переменных:
        //   & - захватываем все переменные по ссылке (total, threads, results)
        //   t - захватываем номер потока по значению (копируем)
        //       Это важно, чтобы каждый поток знал свой индекс
        pool.emplace_back([&, t] { 
            // Каждый поток вызывает throwPoints для своей порции точек
            // total / threads - количество точек на поток (делим поровну)
            // Результат записывается в results[t] - ячейку с номером потока
            results[t] = throwPoints(total / threads); 
        });
    }
    
    // Ожидаем завершения всех потоков
    for (auto &th : pool) th.join();
    
    // Суммируем результаты всех потоков
    hits = accumulate(results.begin(), results.end(), 0LL);
    
    // Вычисляем Пи по формуле: Пи = 4 * (попаданий / всего точек)
    double pi_multi = 4.0 * hits / total;
    
    end = high_resolution_clock::now();
    auto multi_time = duration_cast<milliseconds>(end - start).count();
    
    cout << "Многопоток (" << threads << " потоков): " << pi_multi 
         << " | Время: " << multi_time << " ms\n";
    
    // ========== ВЫВОД СТАТИСТИКИ ==========
    cout << "\nУскорение: " << (double)single_time / multi_time << " раз\n";

    return 0;
}
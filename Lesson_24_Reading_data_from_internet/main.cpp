// Lesson 24: Reading_data_from_internet

// Чтение данных из интернета

/*
Чтение данных из интернета — это:
Процесс, в котором программа на C++ отправляет запрос к удалённому серверу через интернет, получает от него ответ с данными и обрабатывает эти данные для использования в программе.

Простыми словами:
Это когда программа заходит на сайт/сервер, скачивает оттуда информацию и показывает её пользователю или использует для своих целей.

Три главных шага:
Шаг     Что происходит	    Пример
1   	Отправить запрос	Программа говорит сайту: "Дай погоду в Москве"
2       Получить ответ	    Сайт возвращает: {"temp": 18.5}
3       Обработать данные	Программа показывает: "Температура: 18.5°C"


Для этого нужно:
- Библиотека для HTTP — чтобы отправлять запросы
- Библиотека для JSON — чтобы разбирать ответы

POST — это метод HTTP, который используется для отправки данных на сервер. 
JSON (JavaScript Object Notation) — это формат для хранения и передачи данных в виде текста, который понятен и человеку, и компьютеру.

Самый частый запрос — GET (просто получить данные)
Формат данных — JSON (как таблица с данными)
Сайт-посредник — API (специальный адрес для программ)


Библиотеки для C++
В C++ нет встроенной работы с интернетом. Нужно подключать библиотеки.

Библиотека      Для чего	                                Тип
httplib.h	    Отправлять HTTP-запросы (GET, POST...)	    Header-only (один файл)
json.hpp	    Парсить JSON-ответы от сервера	            Header-only (один файл)
Header-only = просто скачать .h файл и положить в проект.

ссылки на файлы:
https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h
https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp
*/

// Пример - получение погоды по городу с сайта https://open-meteo.com/

#include "httplib.h"
#include "json.hpp"
#include <iostream>
#include <iomanip>

using namespace httplib;
using json = nlohmann::json;

// ============================================================
// ФУНКЦИЯ 1: Получение координат по названию города
// ============================================================
bool getCoordinates(const std::string& cityName, double& lat, double& lon) {
    std::cout << "  Отправляем запрос на поиск города..." << std::endl;
    
    Client geoClient("geocoding-api.open-meteo.com");
    std::string url = "/v1/search?name=" + cityName + "&count=1&language=ru";
    //std::string url = "/v1/search?name=" + cityName + "&count=1&language=en";
    
    // ============================================================
    // ВЫВОД ПОЛНОГО URL ЗАПРОСА (геокодинг)
    // ============================================================
    std::cout << "\n  ЗАПРОС:" << std::endl;
    std::cout << "  ────────────────────────────────────────────────────" << std::endl;
    std::cout << "  https://geocoding-api.open-meteo.com" << url << std::endl;
    std::cout << "  ────────────────────────────────────────────────────\n" << std::endl;
    
    auto res = geoClient.Get(url);
    
    if (!res) {
        std::cout << "  Ошибка: сервер геокодинга не отвечает" << std::endl;
        return false;
    }
    
    if (res->status != 200) {
        std::cout << "  Ошибка: сервер вернул код " << res->status << std::endl;
        return false;
    }
    
    // ============================================================
    // ВЫВОД СЫРОГО JSON ОТВЕТА (геокодинг)
    // ============================================================
    std::cout << "  Сырой JSON ответ (геокодинг):" << std::endl;
    std::cout << "  ────────────────────────────────────────────────────" << std::endl;
    
    if (res->body.length() > 500) {
        std::cout << res->body.substr(0, 500) << "..." << std::endl;
        /*
        res->body.substr(0, 500)
        │    │      │
        │    │      └─ метод substr() у строки (вырезать часть)
        │    └─ поле body у объекта Response (тело ответа)
        └─ указатель на объект Response (возврат от Get())
        -> — это оператор доступа к структуре объекта через указатель 
        // Обычный объект
        std::string name = "Alex";
        name.length();        // ← используем точку (.)

        // Указатель на объект
        std::string* ptr = &name;
        ptr->length();        // ← используем стрелку (->)
        */
        std::cout << "  (показано первые 500 символов из " << res->body.length() << ")" << std::endl;
    } else {
        std::cout << res->body << std::endl;
    }
    std::cout << "  ────────────────────────────────────────────────────\n" << std::endl;
    
    try {
        json data = json::parse(res->body);
        
        if (data["results"].empty()) {
            std::cout << "  Город \"" << cityName << "\" не найден!" << std::endl;
            return false;
        }
        
        lat = data["results"][0]["latitude"];
        lon = data["results"][0]["longitude"];
        
        std::string country = data["results"][0]["country"];
        std::string name = data["results"][0]["name"];
        
        std::cout << "  Город найден!" << std::endl;
        std::cout << "     Название: " << name << std::endl;
        std::cout << "     Страна: " << country << std::endl;
        std::cout << "     Координаты: " << std::fixed << std::setprecision(4) 
                  << lat << ", " << lon << std::endl;
        
        return true;
        
    } catch (const std::exception& e) {
        std::cout << "  Ошибка парсинга JSON: " << e.what() << std::endl;
        return false;
    }
}

// ============================================================
// ФУНКЦИЯ 2: Получение погоды по координатам
// ============================================================
bool getWeather(double lat, double lon, double& temperature, std::string& weatherCode) {
    std::cout << "  Отправляем запрос на получение погоды..." << std::endl;
    
    Client weatherClient("api.open-meteo.com");
    std::string url = "/v1/forecast?latitude=" + std::to_string(lat) +
                      "&longitude=" + std::to_string(lon) +
                      "&current_weather=true&timezone=auto";
    
    // ============================================================
    // ВЫВОД ПОЛНОГО URL ЗАПРОСА (погода)
    // ============================================================
    std::cout << "\n  ЗАПРОС:" << std::endl;
    std::cout << "  ────────────────────────────────────────────────────" << std::endl;
    std::cout << "  https://api.open-meteo.com" << url << std::endl;
    std::cout << "  ────────────────────────────────────────────────────\n" << std::endl;
    
    auto res = weatherClient.Get(url);
    
    if (!res) {
        std::cout << "  Ошибка: сервер погоды не отвечает" << std::endl;
        return false;
    }
    
    if (res->status != 200) {
        std::cout << "  Ошибка: сервер вернул код " << res->status << std::endl;
        return false;
    }
    
    // ============================================================
    // ВЫВОД СЫРОГО JSON ОТВЕТА (погода)
    // ============================================================
    std::cout << "  Сырой JSON ответ (погода):" << std::endl;
    std::cout << "  ────────────────────────────────────────────────────" << std::endl;
    
    if (res->body.length() > 500) {
        std::cout << res->body.substr(0, 500) << "..." << std::endl;
        std::cout << "  (показано первые 500 символов из " << res->body.length() << ")" << std::endl;
    } else {
        std::cout << res->body << std::endl;
    }
    std::cout << "  ────────────────────────────────────────────────────\n" << std::endl;
    
    try {
        json data = json::parse(res->body);
        
        temperature = data["current_weather"]["temperature"];
        int code = data["current_weather"]["weathercode"];
        weatherCode = std::to_string(code);
        
        std::cout << "Данные о погоде получены!" << std::endl;
        std::cout << "Температура: " << temperature << "°C" << std::endl;
        std::cout << "Код погоды: " << code << std::endl;
        
        return true;
        
    } catch (const std::exception& e) {
        std::cout << "  Ошибка парсинга JSON: " << e.what() << std::endl;
        return false;
    }
}

// ============================================================
// ФУНКЦИЯ 3: Расшифровка кода погоды в человекочитаемый вид
// ============================================================
std::string getWeatherDescription(int code) {
    switch (code) {
        case 0: return "Ясно ☀️";
        case 1: return "Преимущественно ясно 🌤️";
        case 2: return "Переменная облачность ⛅";
        case 3: return "Пасмурно ☁️";
        case 45: return "Туман 🌫️";
        case 48: return "Туман с изморозью 🌫️";
        case 51: return "Мелкая морось 🌦️";
        case 53: return "Морось 🌦️";
        case 55: return "Сильная морось 🌧️";
        case 61: return "Небольшой дождь 🌧️";
        case 63: return "Дождь 🌧️";
        case 65: return "Сильный дождь 🌧️";
        case 71: return "Небольшой снег 🌨️";
        case 73: return "Снег 🌨️";
        case 75: return "Сильный снег 🌨️";
        case 80: return "Ливень ⛈️";
        case 81: return "Сильный ливень ⛈️";
        case 95: return "Гроза ⚡";
        case 96: return "Гроза с градом ⚡❄️";
        case 99: return "Сильная гроза с градом ⚡❄️";
        default: return "Неизвестно ❓";
    }
}

/*
std::string getWeatherDescription(int code) {
    switch (code) {
        case 0: return "Clear ☀️";
        case 1: return "Mainly clear 🌤️";
        case 2: return "Partly cloudy ⛅";
        case 3: return "Overcast ☁️";
        case 45: return "Fog 🌫️";
        case 48: return "Depositing rime fog 🌫️";
        case 51: return "Light drizzle 🌦️";
        case 53: return "Moderate drizzle 🌦️";
        case 55: return "Dense drizzle 🌧️";
        case 61: return "Slight rain 🌧️";
        case 63: return "Moderate rain 🌧️";
        case 65: return "Heavy rain 🌧️";
        case 71: return "Slight snow fall 🌨️";
        case 73: return "Moderate snow fall 🌨️";
        case 75: return "Heavy snow fall 🌨️";
        case 80: return "Rain showers ⛈️";
        case 81: return "Moderate rain showers ⛈️";
        case 95: return "Thunderstorm ⚡";
        case 96: return "Thunderstorm with hail ⚡❄️";
        case 99: return "Heavy thunderstorm with hail ⚡❄️";
        default: return "Unknown ❓";
    }
}
*/

// ============================================================
// ОСНОВНАЯ ФУНКЦИЯ (main)
// ============================================================
int main() {
    std::cout << "\n";
    std::cout << "╔═══════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║           УЗНАТЬ ПОГОДУ В ЛЮБОМ ГОРОДЕ            ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════════╝" << std::endl;
    std::cout << "\n";
    
    std::string city;
    std::cout << "Введите название города: ";
    std::getline(std::cin, city);
    
    if (city.empty()) {
        std::cout << "Название города не может быть пустым!" << std::endl;
        return 1;
    }
    
    std::cout << "\n";
    std::cout << "════════════════════════════════════════════════════" << std::endl;
    std::cout << "ИНФОРМАЦИЯ ДЛЯ ЗАПРОСА:" << std::endl;
    std::cout << "Город: " << city << std::endl;
    std::cout << "════════════════════════════════════════════════════" << std::endl;
    std::cout << "\n";
    
    // ШАГ 1: Получаем координаты
    std::cout << "ШАГ 1: Поиск координат города" << std::endl;
    std::cout << "────────────────────────────────────────────────────" << std::endl;
    
    double lat, lon;
    if (!getCoordinates(city, lat, lon)) {
        std::cout << "\nНе удалось получить координаты. Проверьте название города." << std::endl;
        return 1;
    }
    
    std::cout << "\n";
    
    // ШАГ 2: Получаем погоду
    std::cout << "ШАГ 2: Получение данных о погоде" << std::endl;
    std::cout << "────────────────────────────────────────────────────" << std::endl;
    
    double temperature;
    std::string weatherCode;
    if (!getWeather(lat, lon, temperature, weatherCode)) {
        std::cout << "\nНе удалось получить данные о погоде." << std::endl;
        return 1;
    }
    
    std::cout << "\n";
    
    // ШАГ 3: Выводим результат
    std::cout << "════════════════════════════════════════════════════" << std::endl;
    std::cout << "РЕЗУЛЬТАТ:" << std::endl;
    std::cout << "════════════════════════════════════════════════════" << std::endl;
    
    int code = std::stoi(weatherCode);
    std::string description = getWeatherDescription(code);
    
    std::cout << "Город:        " << city << std::endl;
    std::cout << "Координаты:   " << std::fixed << std::setprecision(4) << lat << ", " << lon << std::endl;
    std::cout << "Температура:  " << temperature << "°C" << std::endl;
    std::cout << "Погода:       " << description << std::endl;
    std::cout << "════════════════════════════════════════════════════" << std::endl;
    
    std::cout << "\nПрограмма завершена!" << std::endl;
    
    return 0;
}
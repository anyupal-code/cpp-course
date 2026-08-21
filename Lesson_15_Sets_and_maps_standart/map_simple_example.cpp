#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    map<string, int> ages = {
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 28},
        {"David", 35},
        {"Eve", 22}
    };
    
    map<string, int> more_ages = {
        {"Frank", 40},
        {"Grace", 27},
        {"Henry", 33}
    };
    
    // Объединение словарей
    ages.insert(more_ages.begin(), more_ages.end());
    
    cout << "Общмий список:" << endl;
    for (const auto& pair : ages) {
        cout << pair.first << ": " << pair.second << endl;
    }
    
    return 0;
}
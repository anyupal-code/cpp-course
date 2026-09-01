#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>

using namespace std;

int main() {
    // Создаём словарь как Ptr
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::makePtr<cv::aruco::Dictionary>(
        cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50)
    );
    
    // Создаём метку №5
    cv::Mat markerImage;
    dictionary->generateImageMarker(5, 200, markerImage, 1);
    
    // Сохраняем в PNG (БЕЗ ПОТЕРЬ!)
    cv::imwrite("marker.png", markerImage);
    std::cout << "Создана метка №5 как marker.png" << std::endl;
    
    // Загружаем PNG
    cv::Mat image = cv::imread("marker.png");
    if (image.empty()) {
        std::cout << "Ошибка: не могу загрузить marker.png" << std::endl;
        return -1;
    }
    
    // Распознаём
    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners;
    cv::aruco::detectMarkers(image, dictionary, corners, ids);
    
    if (ids.empty()) {
        std::cout << "Меток не найдено" << std::endl;
    } else {
        std::cout << "Найдена метка №" << ids[0] << std::endl;
        cv::aruco::drawDetectedMarkers(image, corners, ids);
        cv::imwrite("result.png", image);
        std::cout << "Результат сохранён как result.png" << std::endl;
        
        cv::imshow("Результат", image);
        cv::waitKey(0);
    }
    
    return 0;
}
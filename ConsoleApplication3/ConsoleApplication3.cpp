#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Перевіряємо версію OpenCV
    std::cout << "OpenCV version: " << CV_VERSION << std::endl;

    // Завантажуємо зображення (замініть шлях на свій)
    cv::Mat image = cv::imread("test.jpg");

    if (image.empty()) {
        std::cout << "Error: Could not read the image." << std::endl;
        return -1;
    }

    // Показуємо зображення
    cv::imshow("Window", image);
    cv::waitKey(0);

    return 0;
}
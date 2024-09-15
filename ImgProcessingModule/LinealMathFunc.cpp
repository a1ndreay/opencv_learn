#include "LinealMathFunc.h"
#include <opencv2/opencv.hpp>
#include <utility>

cv::Vec3d Blur(const cv::Mat &src, const std::vector<cv::Point>& Locality, std::pair<uint, uint> Core) {
	cv::Vec3d Val;
	uint Sum = 0;
	for (cv::Point Point : Locality)
	{
		Val += (cv::Vec3d)src.at<cv::Vec3b>(Point) * (double)(1 / (Core.first * Core.second));
	}
    return Val;
}

cv::Mat NormalizeColorRange_CV_8UC3(const cv::Mat& src) {
                                                       // Создаем матрицу для работы с double
    cv::Mat srcDouble = src;
    //src.convertTo(srcDouble, CV_64F);                // Конвертируем исходное изображение в тип double

    cv::Mat channels[3];
    cv::split(srcDouble, channels);                    // Разделяем на 3 канала (B, G, R)

    cv::Mat Minimazed[3];
    for (int c = 0; c < 3; c++) {
        double minVal, maxVal;                         // Локальные минимумы и максимумы каналов исходной матрицы
        cv::minMaxLoc(channels[c], &minVal, &maxVal);  // Находим минимум и максимум для канала исходной матрицы

                                                       // Минимизируем каждый канал
        Minimazed[c] = (channels[c] - minVal);         // Минимизируем каналы матрицы для локального минимума
    }

    cv::Mat Normalized[3];                              //Нормализованная матрица
    for (int c = 0; c < 3; c++) {
        double minVal, maxVal;                          // Локальные минимумы и максимумы каналов минимизированной матрицы
        cv::minMaxLoc(Minimazed[c], &minVal, &maxVal);  // Находим минимум и максимум для канала минимизированной матрицы

                                                        // Минимизируем каждый канал
        Normalized[c] = (Minimazed[c] / maxVal) * 255.0;
    }
                                                        // Объединяем обратно каналы
    cv::Mat result;
    cv::merge(Normalized, 3, result);
                                                        // Преобразуем матрицу обратно в 8-битное изображение
    result.convertTo(result, CV_8UC3);                  // Конвертируем в 8-битное изображение с 3 каналами

    return result;
}
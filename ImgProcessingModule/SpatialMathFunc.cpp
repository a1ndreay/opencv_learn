#include "SpatialMathFunc.h"
#include "LinealMathFunc.cpp"
#include "pch.cpp"
#include <opencv2/opencv.hpp>
#include <utility>
#include <functional>

/// <summary>
/// Этот файл содержит имплеметнацию мат. функций для работы с пространственными операциями в библиотеке OpenCV
/// (Гонсалес, Р. Цифровая обработка изображений  / Р. Гонсалес, Р. Вудс. — 3-е изд., испр. и доп. — Москва : Техносфера, 2012. — ISBN 978-5-94836-331-8. — 
/// ( URL: https://e.lanbook.com/book/73514 — С. 121.).
/// </summary>

template <typename Func>

/// <summary>
/// Является подклассом функций пространтсвенных операций
/// Имплементация стандартной функции представляющей операции над окрестностью в библиотеке OpenCV
/// </summary>
/// <param name="src">Исходная матрица</param>
/// <param name="MathFunc">Указатель на функцию линейных операторов из заголовочного файла LinealMathFunc.h</param>
/// <param name="Core">Ядро локальной области (маска или окрестность)</param>
/// <returns>
/// Матрица, полученная в результате поэлементной обработки окрестности линейным оператором.
/// «Операции над окрестностью» (Гонсалес, Р. Цифровая обработка изображений. — URL: https://e.lanbook.com/book/73514 — С. 122.).
/// </returns>
/// <remarks>
/// Примечание размеры Маски должны быть равными и нечётными.
/// </remarks>
cv::Mat ThrowNeighborhood(const cv::Mat& src, Func MathFunc, std::pair<uint, uint> Core) {
	cv::Mat srcDouble;
	src.convertTo(srcDouble, CV_64F);                // Конвертируем исходное изображение в тип double
	for (uint Y = 0; Y < src.rows; Y++) {
		for (uint X = 0; X < src.cols; X++) {
			(cv::Vec3d)srcDouble.at<cv::Vec3b>(X, Y) = MathFunc(src, GetLocalityD(cv::Point(X, Y), Core), Core);
		}
	}
	cv::Mat dst = NormalizeColorRange_CV_8UC3(dst);	 // Нормализуем матрицу для избежания переполнения в тип 8-битового изображения
	return dst;
}
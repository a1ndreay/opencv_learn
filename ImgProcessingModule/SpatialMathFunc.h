#ifndef SPATIALMATHFUNC_H
#define SPATIALMATHFUNC_H
#ifdef IMGPROCESSINGMODULE_EXPORTS
// Ётот макрос будет использоватьс€ при создании .dll
#define IMGPROCESSINGMODULE_API __declspec(dllexport)
#else
// Ётот макрос будет использоватьс€ при подключении к .dll
#define IMGPROCESSINGMODULE_API __declspec(dllimport)
#endif
// ƒобавьте сюда заголовочные файлы дл€ предварительной компил€ции
#include "framework.h"
#include "LinealMathFunc.h"
#include <opencv2/opencv.hpp>
#include <utility>
#include <functional>

template <typename Func>
__declspec(dllexport) cv::Mat ThrowNeighborhood(const cv::Mat& src, Func MathFunc, std::pair<uint, uint> Core) {
	cv::Mat srcDouble;
	src.convertTo(srcDouble, CV_64F);                //  онвертируем исходное изображение в тип double
	cv::Mat extendedImage = extendImage(src, cv::Size(Core.first, Core.second), cv::BORDER_REPLICATE);
	for (uint Y = 0; Y < src.rows; Y++) {
		for (uint X = 0; X < src.cols; X++) {
			cv::Vec3d pixel = MathFunc(extendedImage, GetLocalityD(cv::Point(X + Core.first / 2, Y + Core.second / 2), Core), Core);
			srcDouble.at<cv::Vec3d>(Y, X) = pixel;
		}
	}
	cv::Mat dst = NormalizeColorRange_CV_8UC3(srcDouble);	 // Ќормализуем матрицу дл€ избежани€ переполнени€ в тип 8-битового изображени€
	return dst;
}

template <typename _Func>
__declspec(dllexport) cv::Mat ApplyCorrelation(const cv::Mat& src, _Func MathFunc, std::pair<uint, uint> Core, double _Sigma) {
	cv::Mat srcDouble;
	src.convertTo(srcDouble, CV_64F);                //  онвертируем исходное изображение в тип double
	cv::Mat extendedImage = extendImage(src, cv::Size(Core.first, Core.second), cv::BORDER_REPLICATE);
	std::vector<std::vector<double>> coefficients = createGaussianKernel(Core.first, Core.second, _Sigma); //здесь бы Immutable vector и вообще збс
	for (uint Y = 0; Y < src.rows; Y++) {
		for (uint X = 0; X < src.cols; X++) {
			cv::Vec3d pixel = MathFunc(extendedImage, GetLocalityD(cv::Point(X + Core.first / 2, Y + Core.second / 2), Core), Core, coefficients);
			srcDouble.at<cv::Vec3d>(X, Y) = pixel;
		}
	}
	cv::Mat dst = NormalizeColorRange_CV_8UC3(srcDouble);	 // Ќормализуем матрицу дл€ избежани€ переполнени€ в тип 8-битового изображени€
	return dst;
}

#endif //SPATIALMATHFUNC_H
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

__declspec(dllexport) enum class LaplacianMasks {
	NegMulx90,
	PosMulx90,
	NegMulx45,
	PosMulx45
};

__declspec(dllexport) enum class SobelMasks {
	Left,
	Right
};

__declspec(dllexport) class ProximityMask {
public:
	static std::vector<std::vector<double>> getLaplacianMask(LaplacianMasks mask) {
		switch (mask) {
		case LaplacianMasks::NegMulx90: return { {0,1,0},{1,-4,1},{0,1,0} };
		case LaplacianMasks::PosMulx90: return { {0,-1,0},{-1,4,-1},{0,-1,0} };
		case LaplacianMasks::NegMulx45: return { {1,1,1},{1,-8,1},{1,1,1} };
		case LaplacianMasks::PosMulx45: return { {-1,-1,-1},{-1,8,-1},{-1,-1,-1} };
		default: return {};
		}
	}

	static std::vector<std::vector<double>> getSobelMask(SobelMasks mask) {
		switch (mask) {
		case SobelMasks::Left: return { {-1,-2,-1},{0,0,0},{1,2,1} };
		case SobelMasks::Right: return { {-1,0,1},{-2,0,2},{-1,0,1} };
		default: return {};
		}
	}

	std::vector<std::vector<double>> ReservedMask;
	cv::Mat_<double> ReservedMask3x3;
	void MaskAdapter(const std::vector<std::vector<double>>& _Source) {
		this->ReservedMask = _Source;
	}
	//ѕреобразуем наш тип маски (std::vector<std::vector<double>>) в маску типа opencv (cv::Mat_<double>) ѕрим. только маска 3x3 
	void MaskAdapterCV(const std::vector<std::vector<double>>& _Source) {
		cv::Mat_<double> mask(3, 3);
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				mask(i, j) = _Source[i][j];
			}
		}
		this->ReservedMask3x3 = mask;
	}
};

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

template <typename _Func>
__declspec(dllexport) cv::Mat ApplyCorrelation(const cv::Mat& src, _Func MathFunc, std::vector<std::vector<double>> Mask) {
	cv::Mat srcDouble;
	std::pair<uint, uint> Core = std::pair<uint, uint>(3, 3);
	src.convertTo(srcDouble, CV_64F);                //  онвертируем исходное изображение в тип double
	cv::Mat extendedImage = extendImage(src, cv::Size(Core.first, Core.second), cv::BORDER_REPLICATE);
	std::vector<std::vector<double>> coefficients = Mask; //здесь бы Immutable vector и вообще збс
	for (uint Y = 0; Y < src.rows; Y++) {
		for (uint X = 0; X < src.cols; X++) {
			cv::Vec3d pixel = MathFunc(extendedImage, GetLocalityD(cv::Point(X + Core.first / 2, Y + Core.second / 2), Core), Core, coefficients);
			srcDouble.at<cv::Vec3d>(X, Y) = pixel;
		}
	}
	cv::Mat dst = NormalizeColorRange_CV_8UC3(srcDouble);	 // Ќормализуем матрицу дл€ избежани€ переполнени€ в тип 8-битового изображени€
	return srcDouble;
}

#endif //SPATIALMATHFUNC_H
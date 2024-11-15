#ifndef LINEALMATHFUNC_H
#define LINEALMATHFUNC_H

#ifdef IMGPROCESSINGMODULE_EXPORTS
// Этот макрос будет использоваться при создании .dll
#define IMGPROCESSINGMODULE_API __declspec(dllexport)
#else
// Этот макрос будет использоваться при подключении к .dll
#define IMGPROCESSINGMODULE_API __declspec(dllimport)
#endif

// Добавьте сюда заголовочные файлы для предварительной компиляции
#include "framework.h"
#include <opencv2/opencv.hpp>
#include <utility>
#include <vector>

__declspec(dllexport) cv::Vec3d Blur(const cv::Mat& src, const std::vector<cv::Point>& Locality, std::pair<uint, uint> Core);

__declspec(dllexport) cv::Vec3d medianBlur(const cv::Mat& src, const std::vector<cv::Point>& Locality, std::pair<uint, uint> Core);

__declspec(dllexport) cv::Mat NormalizeColorRange_CV_8UC3(const cv::Mat& src);

__declspec(dllexport) cv::Vec3d GaussianBlur(const cv::Mat& src, const std::vector<cv::Point>& Locality, std::pair<uint, uint> Core, std::vector<std::vector<double>> coefficients);

__declspec(dllexport) cv::Vec3d Derivative(const cv::Mat& src, const std::vector<cv::Point>& Locality, std::pair<uint, uint> Core, std::vector<std::vector<double>> coefficients);

__declspec(dllexport) std::vector<std::vector<double>> createGaussianKernel(int width, int height, double sigma);

__declspec(dllexport) cv::Mat DPF(const cv::Mat& src, int flag = 0);

double gaussian2D(int x, int y, double sigma);

cv::Vec3d Correlation(const cv::Mat& src, const std::vector<cv::Point>& Locality, std::pair<uint, uint> Core, std::vector<std::vector<double>> coefficients);

cv::Vec3d Convolution(const cv::Mat& src, const std::vector<cv::Point>& Locality, std::pair<uint, uint> Core, std::vector<std::vector<double>> coefficients);

cv::Point shiftCoordinates(int s, int t, int a, int b);
#endif //LINEALMATHFUNC_H

#ifndef FILTERFUNCTIONS_H
#define FILTERFUNCTIONS_H

// Добавьте сюда заголовочные файлы для предварительной компиляции

#include "framework.h"
#include <opencv2/opencv.hpp>
#include <utility>
#include <vector>
#include <math.h>

__declspec(dllexport) enum class FrequencyFilters {
	LowPass,
	HightPass
};

__declspec(dllexport) cv::Mat GetSimmetricFilterImage(const int P, const int Q, FrequencyFilters type, int (*PerfectLowPassFilter)(const int, const int, const int, const int, const int), const int Factor);
__declspec(dllexport) cv::Mat GetSimmetricFilterImage(const int P, const int Q, FrequencyFilters type, double (*ButterworthLowPassFilter)(const int, const int, const int, const int, const int, const int), const int Factor, const int order);
__declspec(dllexport) cv::Mat GetSimmetricFilterImage(const int P, const int Q, FrequencyFilters type, double (*GaussianLowPassFilter)(const int, const int, const int, const int, const int), const int Factor);
__declspec(dllexport) cv::Mat GetSimmetricFilterImage(const int P, const int Q, double (*PerfectBandPassFilter)(const int, const int, const int, const int, const int, const int), const int innerRadius, const int outerRadius);
__declspec(dllexport) cv::Mat GetSimmetricFilterImage(const int P, const int Q, double (*ButterworthBandPassFilter)(const int, const int, const int, const int, const int, const int, const int), const int innerRadius, const int outerRadius, const int order);
__declspec(dllexport) cv::Mat GetSimmetricFilterImage(const int P, const int Q, long double (*GaussianBandPassFilter)(const int, const int, const int, const int, const int, const int), const int innerRadius, const int outerRadius);

__declspec(dllexport) int PerfectLowPassFilter(const int U, const int V, const int P, const int Q, const int Factor);
__declspec(dllexport) double ButterworthLowPassFilter(const int U, const int V, const int P, const int Q, const int Factor, const int order);
__declspec(dllexport) double GaussianLowPassFilter(const int U, const int V, const int P, const int Q, const int Factor);
__declspec(dllexport) double PerfectBandPassFilter(const int U, const int V, const int P, const int Q, int innerRadius, int outerRadius);
__declspec(dllexport) double ButterworthBandPassFilter(const int U, const int V, const int P, const int Q, const int innerRadius, const int outerRadius, const int order);
__declspec(dllexport) long double GaussianBandPassFilter(const int U, const int V, const int P, const int Q, int innerRadius, int outerRadius);

__declspec(dllexport) void shiftDFT(cv::Mat& mat);

__declspec(dllexport) void PrepareExtendedImage(cv::Mat& mat);
#endif //FILTERFUNCTIONS_H
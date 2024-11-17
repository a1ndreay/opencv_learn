#ifndef FILTERFUNCTIONS_H
#define FILTERFUNCTIONS_H

// Добавьте сюда заголовочные файлы для предварительной компиляции

#include "framework.h"
#include <opencv2/opencv.hpp>
#include <utility>
#include <vector>
#include <math.h>

__declspec(dllexport) enum class FrequencyFilters {
	PerfectLowPassFilter
};

__declspec(dllexport) cv::Mat GetSimmetricFilterImage(const int P, const int Q, int (*PerfectLowPassFilter)(const int, const int, const int, const int, const int), const int Factor);
__declspec(dllexport) cv::Mat GetSimmetricFilterImage(const int P, const int Q, double (*ButterworthLowPassFilter)(const int, const int, const int, const int, const int, const int), const int Factor, const int order);
__declspec(dllexport) cv::Mat GetSimmetricFilterImage(const int P, const int Q, double (*GaussianLowPassFilter)(const int, const int, const int, const int, const int), const int Factor);

__declspec(dllexport) int PerfectLowPassFilter(const int U, const int V, const int P, const int Q, const int Factor);
__declspec(dllexport) double ButterworthLowPassFilter(const int U, const int V, const int P, const int Q, const int Factor, const int order);
__declspec(dllexport) double GaussianLowPassFilter(const int U, const int V, const int P, const int Q, const int Factor);

__declspec(dllexport) void shiftDFT(cv::Mat& mat);

__declspec(dllexport) void PrepareExtendedImage(cv::Mat& mat);
#endif //FILTERFUNCTIONS_H
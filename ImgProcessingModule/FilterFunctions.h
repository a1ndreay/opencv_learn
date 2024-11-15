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
#endif //FILTERFUNCTIONS_H
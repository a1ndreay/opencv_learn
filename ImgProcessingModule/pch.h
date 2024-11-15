// pch.h: это предварительно скомпилированный заголовочный файл.
// Перечисленные ниже файлы компилируются только один раз, что ускоряет последующие сборки.
// Это также влияет на работу IntelliSense, включая многие функции просмотра и завершения кода.
// Однако изменение любого из приведенных здесь файлов между операциями сборки приведет к повторной компиляции всех(!) этих файлов.
// Не добавляйте сюда файлы, которые планируете часто изменять, так как в этом случае выигрыша в производительности не будет.

#ifndef PCH_H
#define PCH_H

// Добавьте сюда заголовочные файлы для предварительной компиляции
#include "framework.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <utility>
#include <stack>


__declspec(dllexport) std::vector<cv::Point> GetLocalityD(cv::Point _CPoint, std::pair<uint, uint> Core);
__declspec(dllexport) cv::Mat extendImage(const cv::Mat& src, const cv::Size& ksize, int borderType = cv::BORDER_REPLICATE);
__declspec(dllexport) cv::Mat ExtendMatrixZeros(const cv::Mat& src, int P, int Q);
__declspec(dllexport) std::stack<cv::Point> ConvertVectorToStack(std::vector<cv::Point> _Locality);

#endif //PCH_H

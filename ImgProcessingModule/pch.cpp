// pch.cpp: файл исходного кода, соответствующий предварительно скомпилированному заголовочному файлу

#include "pch.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <utility>

// При использовании предварительно скомпилированных заголовочных файлов необходим следующий файл исходного кода для выполнения сборки.

/// <summary>
/// Возвращает вектор, содержащий пары координат (Xi, Yj), принадлежащие окрестности Sxy.
/// Окрестность строится вокруг исходной точки с центром в координате _CPOINT(uint x, uint y)
/// и имеет размеры, определяемые параметрами _Height и _Width.
/// </summary>
/// <param name="x">Координата X центра окрестности (_CPOINT).</param>
/// <param name="y">Координата Y центра окрестности (_CPOINT).</param>
/// <param name="_Height">Высота окрестности (должна быть нечётной).</param>
/// <param name="_Width">Ширина окрестности (должна быть нечётной).</param>
/// <returns>
/// Вектор, содержащий пары координат (Xi, Yj), принадлежащих окрестности.
/// (URL: https://e.lanbook.com/book/73514 — С. 122.)
/// </returns>
/// <remarks>
/// Примечание параметры _Height и _Width должны быть равными и нечётными.
/// </remarks>
std::vector<cv::Point> GetLocalityD(cv::Point _CPoint, std::pair<uint, uint> Core) {
	std::vector<cv::Point> Locality = std::vector<cv::Point>();
	const uint8_t OffsetX = _CPoint.x - Core.second / 2;
	const uint8_t OffsetY = _CPoint.y - Core.first / 2;
	for (uint_fast8_t i = 0; i < Core.second; i++) {
		uint_fast8_t LocalY = OffsetY + i;
		for (uint_fast8_t j = 0; j < Core.first; j++) {
			cv::Point LocalCoord = { OffsetX + j, LocalY};
			Locality.push_back(LocalCoord);
		}
	}
	return Locality;
}
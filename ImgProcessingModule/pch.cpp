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
/// Вектор пар координат (Xi, Yj), принадлежащих окрестности.
/// </returns>
/// <remarks>
/// Примечание: параметры _Height и _Width должны быть равными и нечётными.
/// </remarks>
std::vector<std::pair<uint_fast8_t, uint_fast8_t>> GetLocalityD(std::pair<uint, uint> _CPoint, uint_fast8_t _Height, uint_fast8_t _Width) {
	std::vector<std::pair<uint_fast8_t, uint_fast8_t>> Locality = std::vector<std::pair<uint_fast8_t, uint_fast8_t>>();
	const uint8_t OffsetX = _CPoint.first - _Height / 2;
	const uint8_t OffsetY = _CPoint.second - _Width / 2;
	for (uint_fast8_t i = 0; i < _Height; i++) {
		uint_fast8_t LocalY = OffsetY + i;
		for (uint_fast8_t j = 0; j < _Width; j++) {
			std::pair<uint_fast8_t, uint_fast8_t> LocalCoord = { OffsetX + j, LocalY};
			Locality.push_back(LocalCoord);
		}
	}
	return Locality;
}
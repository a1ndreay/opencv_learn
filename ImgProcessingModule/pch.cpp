#include "pch.h"
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
	const uint OffsetX = _CPoint.x - Core.second / 2;
	const uint OffsetY = _CPoint.y - Core.first / 2;
	for (uint i = 0; i < Core.second; i++) {
		uint LocalY = OffsetY + i;
		for (uint j = 0; j < Core.first; j++) {
			cv::Point LocalCoord = { (int)OffsetX + (int)j, (int)LocalY};
			Locality.push_back(LocalCoord);
		}
	}
	return Locality;
}

cv::Mat extendImage(const cv::Mat& src, const cv::Size& ksize, int borderType) {
	int halfWidth = ksize.width / 2;
	int halfHeight = ksize.height / 2;
	cv::Mat extended;
	cv::copyMakeBorder(src, extended, halfHeight, halfHeight, halfWidth, halfWidth, borderType);

	return extended;
}

/// <summary>
/// расширяет матрицу нулями
/// </summary>
/// <param name="src"></param>
/// <param name="P">numbers of rows</param>
/// <param name="Q">number of cols</param>
/// <returns></returns>
cv::Mat ExtendMatrixZeros(const cv::Mat& src, int P, int Q) {
	if (src.cols > P || src.rows > Q) {
		throw std::runtime_error("P and Q must be greater than original src");
	}
	cv::Mat srcExtended = cv::Mat::zeros(P, Q, src.type());
	for (int Y = 0; Y < src.rows; Y++) {
		for (int X = 0; X < src.cols; X++) {
			srcExtended.at<uchar>(X, Y) = src.at<uchar>(X, Y);
		}
	}
	return srcExtended;
}

std::stack<cv::Point> ConvertVectorToStack(std::vector<cv::Point> _Locality) {
	std::stack<cv::Point> Locality;
	for (std::vector<cv::Point>::size_type i = 0 ; i < _Locality.size(); i++) {
		Locality.push(_Locality[i]);
	}
	return Locality;
}
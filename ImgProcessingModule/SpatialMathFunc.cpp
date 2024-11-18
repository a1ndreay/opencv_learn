#include "pch.h"
#include "SpatialMathFunc.h"


/// <summary>
/// Этот файл содержит имплеметнацию мат. функций для работы с пространственными операциями в библиотеке OpenCV
/// (Гонсалес, Р. Цифровая обработка изображений  / Р. Гонсалес, Р. Вудс. — 3-е изд., испр. и доп. — Москва : Техносфера, 2012. — ISBN 978-5-94836-331-8. — 
/// ( URL: https://e.lanbook.com/book/73514 — С. 121.).
/// </summary>
template <typename Func>
/// <summary>
/// Является подклассом функций пространтсвенных операций
/// Имплементация стандартной функции представляющей операции над окрестностью в библиотеке OpenCV
/// </summary>
/// <param name="src">Исходная матрица</param>
/// <param name="MathFunc">Указатель на функцию линейных операторов из заголовочного файла LinealMathFunc.h</param>
/// <param name="Core">Ядро локальной области (маска или окрестность)</param>
/// <returns>
/// Матрица, полученная в результате поэлементной обработки окрестности линейным оператором.
/// «Операции над окрестностью» (Гонсалес, Р. Цифровая обработка изображений. — URL: https://e.lanbook.com/book/73514 — С. 122.).
/// </returns>
/// <remarks>
/// Примечание размеры Маски должны быть равными и нечётными.
/// </remarks>
cv::Mat __ThrowNeighborhood(const cv::Mat& src, Func MathFunc, std::pair<uint, uint> Core) {
	cv::Mat srcDouble;
	src.convertTo(srcDouble, CV_64F);                // Конвертируем исходное изображение в тип double
	cv::Mat extendedImage = extendImage(srcDouble, cv::Size(Core.first, Core.second), cv::BORDER_REPLICATE);
	for (uint Y = 0; Y < src.rows; Y++) {
		for (uint X = 0; X < src.cols; X++) {
			(cv::Vec3d)srcDouble.at<cv::Vec3b>(X, Y) = MathFunc(src, GetLocalityD(cv::Point(X, Y), Core), Core);
		}
	}
	cv::Mat dst = NormalizeColorRange_CV_8UC3(dst);	 // Нормализуем матрицу для избежания переполнения в тип 8-битового изображения
	return dst;
}

cv::Mat FrequencyFiltering(const cv::Mat& src, FrequencyFilters type, int (*PerfectLowPassFilter)(const int, const int, const int, const int, const int), const int Factor) {
	int P = cv::getOptimalDFTSize(src.rows);										//Находим оптимальные размеры расширения
	int Q = cv::getOptimalDFTSize(src.cols);										//
	cv::Mat result;
	cv::Mat filter = GetSimmetricFilterImage(P, Q, type, PerfectLowPassFilter, Factor);				//Строем симметричную фильтр-функцию H(P,Q) с радиусом = Factor
	result = ComFrequencyFiltering(src, filter, P, Q);
	return result;
}

cv::Mat FrequencyFiltering(const cv::Mat& src, FrequencyFilters type, double (*ButterworthLowPassFilter)(const int, const int, const int, const int, const int, const int), const int Factor, const int order) {
	int P = cv::getOptimalDFTSize(src.rows);										//Находим оптимальные размеры расширения
	int Q = cv::getOptimalDFTSize(src.cols);										//
	cv::Mat result;
	cv::Mat filter = GetSimmetricFilterImage(P, Q, type, ButterworthLowPassFilter, Factor, order);	//Строем симметричную фильтр-функцию H(P,Q) с радиусом = Factor
	result = ComFrequencyFiltering(src, filter, P, Q);
	return result;
}

cv::Mat FrequencyFiltering(const cv::Mat& src, FrequencyFilters type, double (*GaussianLowPassFilter)(const int, const int, const int, const int, const int), const int Factor) {
	int P = cv::getOptimalDFTSize(src.rows);										//Находим оптимальные размеры расширения
	int Q = cv::getOptimalDFTSize(src.cols);										//
	cv::Mat result;
	cv::Mat filter = GetSimmetricFilterImage(P, Q, type, GaussianLowPassFilter, Factor);	//Строем симметричную фильтр-функцию H(P,Q) с радиусом = Factor
	result = ComFrequencyFiltering(src, filter, P, Q);
	return result;
}

cv::Mat FrequencyFiltering(const cv::Mat& src, double (*PerfectBandPassFilter)(const int, const int, const int, const int, const int, const int), const int innerRadius, const int outerRadius) {
	int P = cv::getOptimalDFTSize(src.rows);										//Находим оптимальные размеры расширения
	int Q = cv::getOptimalDFTSize(src.cols);										//
	cv::Mat result;
	cv::Mat filter = GetSimmetricFilterImage(P, Q, PerfectBandPassFilter, innerRadius, outerRadius);	//Строем симметричную фильтр-функцию H(P,Q) с радиусом = Factor
	result = ComFrequencyFiltering(src, filter, P, Q);
	return result;
}

cv::Mat FrequencyFiltering(const cv::Mat& src, double (*ButterworthBandPassFilter)(const int, const int, const int, const int, const int, const int, const int), const int innerRadius, const int outerRadius, const int order) {
	int P = cv::getOptimalDFTSize(src.rows);										//Находим оптимальные размеры расширения
	int Q = cv::getOptimalDFTSize(src.cols);										//
	cv::Mat result;
	cv::Mat filter = GetSimmetricFilterImage(P, Q, ButterworthBandPassFilter, innerRadius, outerRadius, order);	//Строем симметричную фильтр-функцию H(P,Q) с радиусом = Factor
	result = ComFrequencyFiltering(src, filter, P, Q);
	return result;
}

cv::Mat FrequencyFiltering(const cv::Mat& src, long double (*GaussianBandPassFilter)(const int, const int, const int, const int, const int, const int), const int innerRadius, const int outerRadius) {
	int P = cv::getOptimalDFTSize(src.rows);										//Находим оптимальные размеры расширения
	int Q = cv::getOptimalDFTSize(src.cols);										//
	cv::Mat result;
	cv::Mat filter = GetSimmetricFilterImage(P, Q, GaussianBandPassFilter, innerRadius, outerRadius);	//Строем симметричную фильтр-функцию H(P,Q) с радиусом = Factor
	result = ComFrequencyFiltering(src, filter, P, Q);
	return result;
}

cv::Mat ComFrequencyFiltering(const cv::Mat& src, const cv::Mat& filter, const int P, const int Q) {
	cv::Mat imgFFT, filterFFT, result;
	std::vector<cv::Mat> results(3);
	cv::Mat imgFloat, imgComplex;
	cv::Mat filterComplex = filter.clone();											//Необязательный шаг, наша фильтр-функция и так имеет тип CV_64FC2
	shiftDFT(filterComplex);														//Центрируем фильтр-функцию 
	if (src.type() == 16) {
		std::vector<cv::Mat> channels;
		cv::split(src, channels);
		for (int c = 0; c < 3; c++) {
			cv::Mat ExtendedSrc = ExtendMatrixZeros(channels[c], P, Q);				//расширяем изображение нулями
			/*PrepareExtendedImage(ExtendedSrc);*/
			ExtendedSrc.convertTo(imgFloat, CV_64FC2);
			// Преобразование изображения и фильтра в частотную область
			dft(imgFloat, imgFFT, cv::DFT_COMPLEX_OUTPUT);							//находим комплексную часть прямое ДФТ изображения
			dft(filterComplex, filterFFT, cv::DFT_COMPLEX_OUTPUT);					//находим комплексную часть прямое ДФТ фильтра
			cv::Mat output;
			mulSpectrums(imgFFT, filterFFT, output, 0);								//умножаем комплексные части ДФТ				

			idft(output, output, cv::DFT_SCALE | cv::DFT_REAL_OUTPUT | cv::DFT_COMPLEX_OUTPUT);			// Обратное преобразование в пространственную область

			// Нормализация и приведение к типу CV_8U для отображения
			normalize(output, output, 0, 255, cv::NORM_MINMAX);											// Нормализуем изображение
			output.convertTo(output, CV_8U);
			results[c] = cv::Mat(P, Q, CV_8U);
			output.copyTo(results[c]);
		}
		cv::merge(results, result);
	}
	return result;
}

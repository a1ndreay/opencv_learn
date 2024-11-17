#include "pch.h"
#include "SpatialMathFunc.h"


/// <summary>
/// ���� ���� �������� ������������� ���. ������� ��� ������ � ����������������� ���������� � ���������� OpenCV
/// (��������, �. �������� ��������� �����������  / �. ��������, �. ����. � 3-� ���., ����. � ���. � ������ : ����������, 2012. � ISBN 978-5-94836-331-8.�� 
/// ( URL: https://e.lanbook.com/book/73514 � �. 121.).
/// </summary>
template <typename Func>
/// <summary>
/// �������� ���������� ������� ���������������� ��������
/// ������������� ����������� ������� �������������� �������� ��� ������������ � ���������� OpenCV
/// </summary>
/// <param name="src">�������� �������</param>
/// <param name="MathFunc">��������� �� ������� �������� ���������� �� ������������� ����� LinealMathFunc.h</param>
/// <param name="Core">���� ��������� ������� (����� ��� �����������)</param>
/// <returns>
/// �������, ���������� � ���������� ������������ ��������� ����������� �������� ����������.
/// ��������� ��� ������������� (��������, �. �������� ��������� �����������. � URL: https://e.lanbook.com/book/73514 � �. 122.).
/// </returns>
/// <remarks>
/// ���������� ������� ����� ������ ���� ������� � ���������.
/// </remarks>
cv::Mat __ThrowNeighborhood(const cv::Mat& src, Func MathFunc, std::pair<uint, uint> Core) {
	cv::Mat srcDouble;
	src.convertTo(srcDouble, CV_64F);                // ������������ �������� ����������� � ��� double
	cv::Mat extendedImage = extendImage(srcDouble, cv::Size(Core.first, Core.second), cv::BORDER_REPLICATE);
	for (uint Y = 0; Y < src.rows; Y++) {
		for (uint X = 0; X < src.cols; X++) {
			(cv::Vec3d)srcDouble.at<cv::Vec3b>(X, Y) = MathFunc(src, GetLocalityD(cv::Point(X, Y), Core), Core);
		}
	}
	cv::Mat dst = NormalizeColorRange_CV_8UC3(dst);	 // ����������� ������� ��� ��������� ������������ � ��� 8-�������� �����������
	return dst;
}

cv::Mat FrequencyFiltering(const cv::Mat& src, int (*PerfectLowPassFilter)(const int, const int, const int, const int, const int), const int Factor) {
	int P = cv::getOptimalDFTSize(src.rows);										//������� ����������� ������� ����������
	int Q = cv::getOptimalDFTSize(src.cols);										//
	cv::Mat result;
	cv::Mat filter = GetSimmetricFilterImage(P, Q, PerfectLowPassFilter, Factor);	//������ ������������ ������-������� H(P,Q) � �������� = Factor
	result = ComFrequencyFiltering(src, filter, P, Q);
	return result;
}

cv::Mat FrequencyFiltering(const cv::Mat& src, double (*ButterworthLowPassFilter)(const int, const int, const int, const int, const int, const int), const int Factor, const int order) {
	int P = cv::getOptimalDFTSize(src.rows);										//������� ����������� ������� ����������
	int Q = cv::getOptimalDFTSize(src.cols);										//
	cv::Mat result;
	cv::Mat filter = GetSimmetricFilterImage(P, Q, ButterworthLowPassFilter, Factor, order);	//������ ������������ ������-������� H(P,Q) � �������� = Factor
	result = ComFrequencyFiltering(src, filter, P, Q);
	return result;
}

cv::Mat FrequencyFiltering(const cv::Mat& src, double (*GaussianLowPassFilter)(const int, const int, const int, const int, const int), const int Factor) {
	int P = cv::getOptimalDFTSize(src.rows);										//������� ����������� ������� ����������
	int Q = cv::getOptimalDFTSize(src.cols);										//
	cv::Mat result;
	cv::Mat filter = GetSimmetricFilterImage(P, Q, GaussianLowPassFilter, Factor);	//������ ������������ ������-������� H(P,Q) � �������� = Factor
	result = ComFrequencyFiltering(src, filter, P, Q);
	return result;
}

cv::Mat ComFrequencyFiltering(const cv::Mat& src, const cv::Mat& filter, const int P, const int Q) {
	cv::Mat imgFFT, filterFFT, result;
	std::vector<cv::Mat> results(3);
	cv::Mat imgFloat, imgComplex;
	cv::Mat filterComplex = filter.clone();											//�������������� ���, ���� ������-������� � ��� ����� ��� CV_64FC2
	shiftDFT(filterComplex);														//���������� ������-������� 
	if (src.type() == 16) {
		std::vector<cv::Mat> channels;
		cv::split(src, channels);
		for (int c = 0; c < 3; c++) {
			cv::Mat ExtendedSrc = ExtendMatrixZeros(channels[c], P, Q);				//��������� ����������� ������
			/*PrepareExtendedImage(ExtendedSrc);*/
			ExtendedSrc.convertTo(imgFloat, CV_64FC2);
			// �������������� ����������� � ������� � ��������� �������
			dft(imgFloat, imgFFT, cv::DFT_COMPLEX_OUTPUT);							//������� ����������� ����� ������ ��� �����������
			dft(filterComplex, filterFFT, cv::DFT_COMPLEX_OUTPUT);					//������� ����������� ����� ������ ��� �������
			cv::Mat output;
			mulSpectrums(imgFFT, filterFFT, output, 0);								//�������� ����������� ����� ���				

			idft(output, output, cv::DFT_SCALE | cv::DFT_REAL_OUTPUT | cv::DFT_COMPLEX_OUTPUT);			// �������� �������������� � ���������������� �������

			// ������������ � ���������� � ���� CV_8U ��� �����������
			normalize(output, output, 0, 255, cv::NORM_MINMAX);											// ����������� �����������
			output.convertTo(output, CV_8U);
			results[c] = cv::Mat(P, Q, CV_8U);
			output.copyTo(results[c]);
		}
		cv::merge(results, result);
	}
	return result;
}

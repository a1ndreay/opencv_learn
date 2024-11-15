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
//cv::Mat ThrowNeighborhood(const cv::Mat& src, Func MathFunc, std::pair<uint, uint> Core) {
//	cv::Mat srcDouble;
//	src.convertTo(srcDouble, CV_64F);                // ������������ �������� ����������� � ��� double
//	for (uint Y = 0; Y < src.rows; Y++) {
//		for (uint X = 0; X < src.cols; X++) {
//			(cv::Vec3d)srcDouble.at<cv::Vec3b>(X, Y) = MathFunc(src, GetLocalityD(cv::Point(X, Y), Core), Core);
//		}
//	}
//	cv::Mat dst = NormalizeColorRange_CV_8UC3(dst);	 // ����������� ������� ��� ��������� ������������ � ��� 8-�������� �����������
//	return dst;
//}

cv::Mat FrequencyFiltering(const cv::Mat& src, int (*PerfectLowPassFilter)(const int, const int, const int, const int, const int), const int Factor) {
	int P = cv::getOptimalDFTSize(src.rows);
	int Q = cv::getOptimalDFTSize(src.cols);
	cv::Mat MatExtended = ExtendMatrixZeros(src, P, Q);										 //��������� ������� ������
	cv::Mat FourierImage = DPF(MatExtended);												 //��������� ������ ���������� �������������� �����
	cv::Mat SimmetricFilterImage = GetSimmetricFilterImage(P, Q, PerfectLowPassFilter, 1);	 //��������� ������-�������
	cv::Mat _Multiplexed = cv::Mat(P, Q, CV_8UC3);											 //������������ ������-������� �� �����-�����

	for (uint Y = 0; Y < P; Y++) {
		for (uint X = 0; X < Q; X++) {
			cv::Vec3d pixel = FourierImage.at<cv::Vec3d>(X, Y) * SimmetricFilterImage.at<cv::Vec3d>(X, Y);
			_Multiplexed.at<cv::Vec3d>(X, Y) = pixel;
		}
	}

	cv::Mat _Result = DPF(_Multiplexed, 1);													//������������� ����������� (�������� ���)				
	cv::Mat dst = NormalizeColorRange_CV_8UC3(_Result);										// ����������� ������� ��� ��������� ������������ � ��� 8-�������� �����������
	return dst;
}

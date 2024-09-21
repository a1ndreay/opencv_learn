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


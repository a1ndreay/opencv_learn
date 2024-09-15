#include "LinealMathFunc.h"
#include <opencv2/opencv.hpp>
#include <utility>

cv::Vec3d Blur(const cv::Mat &src, const std::vector<cv::Point>& Locality, std::pair<uint, uint> Core) {
	cv::Vec3d Val;
	uint Sum = 0;
	for (cv::Point Point : Locality)
	{
		Val += (cv::Vec3d)src.at<cv::Vec3b>(Point) * (double)(1 / (Core.first * Core.second));
	}
    return Val;
}

cv::Mat NormalizeColorRange_CV_8UC3(const cv::Mat& src) {
                                                       // ������� ������� ��� ������ � double
    cv::Mat srcDouble = src;
    //src.convertTo(srcDouble, CV_64F);                // ������������ �������� ����������� � ��� double

    cv::Mat channels[3];
    cv::split(srcDouble, channels);                    // ��������� �� 3 ������ (B, G, R)

    cv::Mat Minimazed[3];
    for (int c = 0; c < 3; c++) {
        double minVal, maxVal;                         // ��������� �������� � ��������� ������� �������� �������
        cv::minMaxLoc(channels[c], &minVal, &maxVal);  // ������� ������� � �������� ��� ������ �������� �������

                                                       // ������������ ������ �����
        Minimazed[c] = (channels[c] - minVal);         // ������������ ������ ������� ��� ���������� ��������
    }

    cv::Mat Normalized[3];                              //��������������� �������
    for (int c = 0; c < 3; c++) {
        double minVal, maxVal;                          // ��������� �������� � ��������� ������� ���������������� �������
        cv::minMaxLoc(Minimazed[c], &minVal, &maxVal);  // ������� ������� � �������� ��� ������ ���������������� �������

                                                        // ������������ ������ �����
        Normalized[c] = (Minimazed[c] / maxVal) * 255.0;
    }
                                                        // ���������� ������� ������
    cv::Mat result;
    cv::merge(Normalized, 3, result);
                                                        // ����������� ������� ������� � 8-������ �����������
    result.convertTo(result, CV_8UC3);                  // ������������ � 8-������ ����������� � 3 ��������

    return result;
}
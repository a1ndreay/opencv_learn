#include "pch.h"
#include "LinealMathFunc.h"


/// <summary>
/// ����������� ������.
/// </summary>
/// <param name="src">�������� �������</param>
/// <param name="Locality">����</param>
/// <param name="Core">��������� �����</param>
/// <returns>����������� �������� �������� �����������</returns>
cv::Vec3d Blur(const cv::Mat &src, const std::vector<cv::Point>& Locality, std::pair<uint, uint> Core) {
	cv::Vec3d Val;
	uint Sum = 0;
	for (cv::Point Point : Locality)
	{
        cv::Vec3d _MappedPoint = src.at<cv::Vec3b>(Point);
		Val += _MappedPoint * ((double)(1) / ((double)(Core.first) * (double)Core.second));
	}
    return Val;
}

/// <summary>
/// ������� ��������� ���������� �����������.
/// </summary>
/// <param name="src"></param>
/// <param name="Locality"></param>
/// <param name="Core"></param>
/// <returns></returns>
cv::Vec3d GaussianBlur(const cv::Mat& src, const std::vector<cv::Point>& Locality, std::pair<uint, uint> Core, std::vector<std::vector<double>> coefficients)
{
    cv::Vec3d Val = Correlation(src, Locality, Core, coefficients);
    return Val;
}

/// <summary>
/// �������� ����� ������������� � ���������� ��������������
/// </summary>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="sigma">����������� ����������</param>
/// <returns>���������� ����� �������������</returns>
std::vector<std::vector<double>> createGaussianKernel(int width, int height, double sigma) {
    std::vector<std::vector<double>> coefficients(width, std::vector<double>(height));

    // ����� ����
    int centerX = width / 2;
    int centerY = height / 2;

    double sum = 0.0;  // ��� ������������

    // ���������� ������� �������������
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            int x = i - centerX;
            int y = j - centerY;
            coefficients[i][j] = gaussian2D(x, y, sigma);
            sum += coefficients[i][j];
        }
    }

    // ������������ ���� (����� ����� ���� ��������� ���� ����� 1)
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            coefficients[i][j] /= sum;
        }
    }

    return coefficients;
}

/// <summary>
/// �������� ������� ��� ���� ����������
/// ��������� ������� ���� ����������� (��������, �. �������� ��������� �����������  / �. ��������, �. ����. � 3-� ���., ����. � ���. � ������ : ����������, 2012. � ISBN 978-5-94836-331-8.
/// �� �����: �����������// ���� : ����������-������������ �������. � URL: https://e.lanbook.com/book/73514  � �. 194.).
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="sigma">����������� ����������</param>
/// <returns></returns>
double gaussian2D(int x, int y, double sigma) {
    double exponent = -(x * x + y * y) / (2 * sigma * sigma);
    return std::exp(exponent);
}

/// <summary>
/// ������� ���������� �������
/// </summary>
/// <param name="src">�������� �������</param>
/// <param name="Locality">����</param>
/// <param name="Core">��������� ����</param>
/// <param name="coefficients">����� �������������</param>
/// <returns>�������� ����������</returns>
cv::Vec3d Correlation(const cv::Mat& src, const std::vector<cv::Point>& Locality, std::pair<uint, uint> Core, std::vector<std::vector<double>> coefficients)
{
    std::stack<cv::Point> SLocality = ConvertVectorToStack(Locality);
    cv::Vec3d Val;
    int a = (Core.first - 1) / 2;
    int b = (Core.second - 1) / 2;
    for (int s = -a; s < a; s++) {
        for (int t = -b; t < b; t++) {
            cv::Point Point = SLocality.top(); SLocality.pop();
            cv::Point SPoint = shiftCoordinates(s, t, a, b);              //����� � ������ ������� ���������
            cv::Vec3d _MappedPoint = src.at<cv::Vec3b>(Point.x, Point.y);
            Val += (double)coefficients[SPoint.x][SPoint.y] * _MappedPoint;
        }
    }
    return Val;
}

/// <summary>
/// ������� ������ �������
/// </summary>
/// <param name="src">�������� �������</param>
/// <param name="Locality">����</param>
/// <param name="Core">��������� ����</param>
/// <param name="coefficients">����� �������������</param>
/// <returns>�������� ������</returns>
cv::Vec3d Convolution(const cv::Mat& src, const std::vector<cv::Point>& Locality, std::pair<uint, uint> Core, std::vector<std::vector<double>> coefficients)
{
    std::stack<cv::Point> SLocality = ConvertVectorToStack(Locality);
    cv::Vec3d Val;
    int a = (Core.first - 1) / 2;
    int b = (Core.second - 1) / 2;
    for (int s = -a; s < a; s++) {
        for (int t = -b; t < b; t++) {
            cv::Point Point = SLocality.top(); SLocality.pop();
            cv::Vec3d _MappedPoint = src.at<cv::Vec3b>(Point.x - s, Point.y - t);
            Val += (double)coefficients[s][t] * _MappedPoint;
        }
    }
    return Val;
}

// ������� ��� �������������� ��������� (������� ������� ��������� �� ������ � ����� ������� ����) ������������ ������� ���������
cv::Point shiftCoordinates(int s, int t, int a, int b) {
    // ����� ��������� �� a � b ��� ����������� ������� � �������
    return cv::Point(s + a, t + b);
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
/*
 * Project Name: [Project Name]
 * File Name: [File Name]
 * Description: [Short description of the file]
 * Author: Zorkin Andrey A.
 * Created: [Creation Date]
 * Last Modified: [Last Modified Date]
 * Version: 1.0
 *
 * Copyright (c) [Year] [Your Company]. All rights reserved.
 *
 * Description:
 * [Detailed description of the file's purpose and functionality]
 */

 // Code starts here

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

const char* winname = "Template window";
Rect trinangle;
Rect tmp;
bool lockEvent = false;

void my_mouse_callback(int event, int x, int y, int flags, void* param);
void Cblur(InputArray src,
    OutputArray dst,
    Size ksize,
    Point anchor = Point(-1, -1),
    int borderType = BORDER_DEFAULT);
void CGaussianBlur(InputArray src,
    OutputArray dst,
    Size ksize,
    double sigmaX,
    double sigmaY = 0,
    int borderType = BORDER_DEFAULT);
void CmedianBlur(InputArray src,
    OutputArray dst,
    int ksize);
void CLaplacian(InputArray src,
    OutputArray dst,
    int ddepth,
    int ksize = 1,
    double scale = 1,
    double delta = 0,
    int borderType = BORDER_DEFAULT);
void CSobel(InputArray src,
    OutputArray dst,
    int ddepth,
    int dx,
    int dy,
    int ksize = 3,
    double scale = 1,
    double delta = 0,
    int borderType = BORDER_DEFAULT);

void my_mouse_callback(int event, int x, int y, int flags, void* param)
{
    Mat* pimg = (Mat*)param;
    switch (event)
    {
    case EVENT_MOUSEMOVE:
        if (lockEvent)
        {
            trinangle.width = x - trinangle.x;
            trinangle.height = y - trinangle.y;
        }
        break;
    case EVENT_LBUTTONDOWN:
        lockEvent = true;
        trinangle = Rect(x, y, 0, 0);
        break;
    case EVENT_LBUTTONUP:
        lockEvent = false;
        if (trinangle.width < 0)
        {
            trinangle.x += trinangle.width;
            trinangle.width *= -1;
        }
        if (trinangle.height < 0)
        {
            //trinangle.y += trinangle.height;
            //trinangle.height *= -1;
        }
        break;
    }
}

void applyBlur(const cv::Mat& src, cv::Mat& dst, const cv::Size& ksize, const cv::Point& anchor = cv::Point(-1, -1), int borderType = cv::BORDER_DEFAULT)
{
    // ���������� ������������ ������� � ��������� �����������
    cv::blur(src, dst, ksize, anchor, borderType);
}
void customBlur(const cv::Mat& src, cv::Mat& dst, const cv::Size& ksize) {
    // ���������, ��� ������ ���� �������� �������� ������
    if (ksize.width % 2 == 0 || ksize.height % 2 == 0) {
        std::cerr << "������ ���� ������ ���� �������� ������!" << std::endl;
        return;
    }

    // ������� ����������� � ����� �� ��������, ��� ��������
    dst = cv::Mat::zeros(src.size(), src.type());

    // �������� ������� ����
    int halfWidth = ksize.width / 2;
    int halfHeight = ksize.height / 2;

    // ��������� �� ������� ������� �����������
    for (int y = halfHeight; y < src.rows - halfHeight; ++y) {
        for (int x = halfWidth; x < src.cols - halfWidth; ++x) {
            // ���������� ��� ���������� ��������
            cv::Vec3i sum = { 0, 0, 0 };

            // ��������� �� ����������� ������ �������� �������
            for (int ky = -halfHeight; ky <= halfHeight; ++ky) {
                for (int kx = -halfWidth; kx <= halfWidth; ++kx) {
                    sum += src.at<cv::Vec3b>(y + ky, x + kx);
                }
            }

            // ��������� ������� ��������
            int kernelSize = ksize.width * ksize.height;
            dst.at<cv::Vec3b>(y, x) = sum / kernelSize;
        }
    }
}

int main()
{
    // �������� �����������
    cv::Mat image = cv::imread("C:/Users/������/Downloads/code.png");

    if (image.empty()) {
        std::cerr << "������ ��� �������� �����������!" << std::endl;
        return -1;
    }

    // ���������� ������� ��� �������� ����������
    cv::Mat blurredImage;
    cv::Mat blurredImagev2; // ��� ������

    // ������ ���� ������������ ������� (��������, 5x5)
    cv::Size ksize(5, 5); //����� �������

    // ����� ������� ������������ �����������
    applyBlur(image, blurredImage, ksize);
    customBlur(image, blurredImagev2, ksize);

    // ����� ������������� � ����������� �����������
    cv::imshow("Original Image", image);
    cv::imshow("Blurred Image", blurredImage);
    cv::imshow("Custom Blurred Image v2", blurredImagev2);


    // �������� ������� �������
    cv::waitKey(0);

    return 0;
}
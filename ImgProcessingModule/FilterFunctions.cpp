#include "pch.h"
#include "FilterFunctions.h"

/// <summary>
///  Реализации дискретных частотных фильтров сглаживания изображений
/// </summary>

cv::Mat GetSimmetricFilterImage(const int P, const int Q, int (*PerfectLowPassFilter)(const int, const int, const int, const int, const int), const int Factor) {
    cv::Mat filter(P, Q, CV_64FC2);

    for (int u = 0; u < P; ++u) {
        for (int v = 0; v < Q; ++v) {
            filter.at<cv::Vec2d>(u, v) = PerfectLowPassFilter(u, v, P, Q, Factor);
        }
    }
    return filter;
}

cv::Mat GetSimmetricFilterImage(const int P, const int Q, double (*ButterworthLowPassFilter)(const int, const int, const int, const int, const int, const int), const int Factor, const int order) {
    cv::Mat filter(P, Q, CV_64FC2);

    for (int u = 0; u < P; ++u) {
        for (int v = 0; v < Q; ++v) {
            filter.at<cv::Vec2d>(u, v) = ButterworthLowPassFilter(u, v, P, Q, Factor, order);
        }
    }
    return filter;
}

cv::Mat GetSimmetricFilterImage(const int P, const int Q, double (*GaussianLowPassFilter)(const int, const int, const int, const int, const int), const int Factor) {
    cv::Mat filter(P, Q, CV_64FC2);

    for (int u = 0; u < P; ++u) {
        for (int v = 0; v < Q; ++v) {
            filter.at<cv::Vec2d>(u, v) = GaussianLowPassFilter(u, v, P, Q, Factor);
        }
    }
    return filter;
}

/// <summary>
/// Идеальный фильтр низких частот. Очень резкий. Двумерный. Обрезает все частотные состовляющие за пределами радиуса (Factor). Передаточная функция представляет разрыв
/// </summary>
int PerfectLowPassFilter(const int U, const int V, const int P, const int Q, const int Factor){
    double Radius;
    Radius = sqrt(pow(U - P / 2, 2) + pow(V - Q / 2, 2));
    if (Radius <= Factor) {
        return 1.0;
    }
    return 0.0;
}

/// <summary>
/// Фильтр низких частот Баттерворда. Двумерный. По резкости между идеальным и Гауссовым. При увеличении порядка фильтра (order) приближается к Идеальному фильтру низких частот. Передаточная функция не имеет разрыва, она плавная
/// </summary>
double ButterworthLowPassFilter(const int U, const int V, const int P, const int Q, const int Factor, const int order) {
    double dist = sqrt(pow(U - P/2, 2) + pow(V - Q/2, 2));
    double val = 1.0 / (1.0 + pow(dist / Factor, 2 * order));
    return val;
}

double GaussianLowPassFilter(const int U, const int V, const int P, const int Q, const int Factor) {
    double dist = sqrt(pow(U - P/2, 2) + pow(V - Q/2, 2));
    double val = exp(-(dist * dist) / (2 * Factor * Factor));
    return val;
}

void shiftDFT(cv::Mat & mat) {
    int cx = mat.cols / 2;
    int cy = mat.rows / 2;

    cv::Mat q1(mat, cv::Rect(0, 0, cx, cy));
    cv::Mat q2(mat, cv::Rect(cx, 0, cx, cy));
    cv::Mat q3(mat, cv::Rect(0, cy, cx, cy));
    cv::Mat q4(mat, cv::Rect(cx, cy, cx, cy));

    cv::Mat tmp;
    q1.copyTo(tmp);
    q4.copyTo(q1);
    tmp.copyTo(q4);

    q2.copyTo(tmp);
    q3.copyTo(q2);
    tmp.copyTo(q3);
}

void PrepareExtendedImage(cv::Mat& mat) {
    for (int Y = 0; Y < mat.rows; Y++) {
        for (int X = 0; X < mat.cols; X++) {
            mat.at<uchar>(X, Y) = mat.at<uchar>(X, Y) * pow(-1, X + Y);
        }
    }
}

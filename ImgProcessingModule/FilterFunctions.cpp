#include "pch.h"
#include "FilterFunctions.h"

cv::Mat GetSimmetricFilterImage(const int P, const int Q, int (*PerfectLowPassFilter)(const int, const int, const int, const int, const int), const int Factor) {
    cv::Mat filter(P, Q, CV_8UC3);

    for (int u = 0; u < P; ++u) {
        for (int v = 0; v < Q; ++v) {
            filter.at<cv::Vec3b>(u, v) = PerfectLowPassFilter(u, v, P, Q, Factor);
        }
    }
    return filter;
}

/// <summary>
/// Идеальный фильтр низких частот.
/// </summary>
int PerfectLowPassFilter(const int U, const int V, const int P, const int Q, const int Factor){
    double Radius;
    Radius = sqrt(pow(U - P / 2, 2) + pow(V - Q / 2, 2));
    if (Radius <= Factor) {
        return 1;
    }
    return 0;
}
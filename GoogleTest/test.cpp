#include "pch.h"
#include "../ImgProcessingModule/SpatialMathFunc.h"
#include "../ImgProcessingModule/LinealMathFunc.h"
#include "../ImgProcessingModule/pch.h"

double CalculateMeanError(const cv::Mat& mat1, const cv::Mat& mat2);
cv::Mat CropMatrix(const cv::Mat& src);

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(GetLocalityDTEST, Handles8Matrix) {
	cv::Point _CPoint(3, 2);
	std::pair<uint, uint> Core(3, 3);
	std::vector<cv::Point> Expect = { {2,1}, {3,1}, {4,1}, {2,2}, {3,2}, {4,2}, {2,3}, {3,3}, {4,3} };
	EXPECT_EQ(GetLocalityD(_CPoint, Core), Expect);
}

TEST(BlurTEST, HandlesNeigbourhood3Test) {
	cv::Mat src = cv::imread("D:/opencv/repos/GoogleTest/Test9x9pi.jpg", cv::IMREAD_COLOR);
	cv::Point _CPoint(3, 2);
	std::pair<uint, uint> Core(3, 3);
	cv::Vec3b pixel = src.at<cv::Vec3b>(_CPoint);
	double abs_error = (static_cast<double>((uchar)pixel[0]) + static_cast<double>((uchar)pixel[1]) + static_cast<double>((uchar)pixel[2])) * (double)1 / 3;
	EXPECT_NE(src.data, nullptr);
	EXPECT_NE(Blur(src, GetLocalityD(_CPoint, Core), Core), (cv::Vec3d)src.at<cv::Vec3b>(_CPoint));
}

//TEST(BlurTEST, HandlesFullBlurTest) {
//	cv::Mat src = cv::imread("D:/opencv/repos/GoogleTest/Test1920x1920pi.jpg", cv::IMREAD_COLOR);
//	std::pair<uint, uint> Core(27, 27);
//	cv::Mat test_blur;
//	test_blur = ThrowNeighborhood(src, Blur, Core);
//	cv::Mat real_blur;
//	cv::blur(src, real_blur, cv::Point(27, 27));
//	double abs_error = CalculateMeanError(test_blur, real_blur);
//	//MAE PER PIXEL среднее абсолютное отклонение на пиксель
//	double MAEPPPI = (double)abs_error / ((src.cols - 2) * (src.rows - 2));
//
//	GTEST_LOG_(INFO) << "The mean absolute error (MAE) / pixel: " << MAEPPPI;
//	EXPECT_NEAR(MAEPPPI, 0.0, 0.00003);
//
//	cv::imwrite("D:/opencv/repos/.outputImage/test_blur.jpg", test_blur);
//	cv::imwrite("D:/opencv/repos/.outputImage/real_blur.jpg", real_blur);
//}

TEST(BlurTEST, HandlesGaussian2DTest) {
	cv::Mat src = cv::imread("D:/opencv/repos/GoogleTest/Test1024x1024pi.jpg", cv::IMREAD_COLOR);
	std::pair<uint, uint> Core(9, 9);
	cv::Mat test_blur;
	test_blur = ApplyCorrelation(src, GaussianBlur, Core, 20.0);
	cv::Mat real_blur;
	cv::GaussianBlur(src, real_blur, cv::Point(9, 9), 20.0, 20.0);
	double abs_error = CalculateMeanError(test_blur, real_blur);
	//MAE PER PIXEL среднее абсолютное отклонение на пиксель
	double MAEPPPI = (double)abs_error / ((src.cols - 2) * (src.rows - 2));

	GTEST_LOG_(INFO) << "The mean absolute error (MAE) / pixel: " << MAEPPPI;
	EXPECT_NEAR(MAEPPPI, 0.0, 0.00003);

	cv::imwrite("D:/opencv/repos/.outputImage/test_blur.jpg", test_blur);
	cv::imwrite("D:/opencv/repos/.outputImage/real_blur.jpg", real_blur);
}

double CalculateMeanError(const cv::Mat& _mat1, const cv::Mat& _mat2) {
	assert(_mat1.size() == _mat2.size() && _mat1.type() == _mat2.type());

	cv::Mat mat1 = CropMatrix(_mat1);
	cv::Mat mat2 = CropMatrix(_mat2);

	double total_error = 0.0;
	int num_pixels = mat1.rows * mat1.cols;

	// Проходим по всем пикселям и вычисляем абсолютное отклонение для каждого канала
	for (int y = 0; y < mat1.rows; ++y) {
		for (int x = 0; x < mat1.cols; ++x) {
			cv::Vec3b pixel1 = mat1.at<cv::Vec3b>(y, x); 
			cv::Vec3b pixel2 = mat2.at<cv::Vec3b>(y, x);

			// Считаем абсолютную разницу для каждого цветового канала
			for (int channel = 0; channel < 3; ++channel) {
				total_error += std::abs(static_cast<double>(pixel1[channel]) - static_cast<double>(pixel2[channel]));
			}
		}
	}

	// Вычисляем среднее абсолютное отклонение
	return total_error / (num_pixels * 3);  // 3 канала
}

cv::Mat CropMatrix(const cv::Mat& src) {
	// Обрезаем по одному пикселю с каждой стороны
	return src(cv::Range(1, src.rows - 1), cv::Range(1, src.cols - 1));
}
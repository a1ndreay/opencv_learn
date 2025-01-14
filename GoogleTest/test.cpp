#include "pch.h"
#include "../ImgProcessingModule/SpatialMathFunc.h"
#include "../ImgProcessingModule/LinealMathFunc.h"
#include "../ImgProcessingModule/pch.h"

double CalculateMeanError(const cv::Mat& mat1, const cv::Mat& mat2);
cv::Mat CropMatrix(const cv::Mat& src);
bool AreMatricesEqual(const cv::Mat& mat1, const cv::Mat& mat2);

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

//TEST(BlurTEST, HandlesBlurTest) {
//	cv::Mat src = cv::imread("D:/opencv/repos/GoogleTest/Test1920x1920pi.jpg", cv::IMREAD_COLOR);
//	std::pair<uint, uint> Core(27, 27);
//	cv::Mat test_blur;
//	test_blur = ThrowNeighborhood(src, Blur, Core);
//	cv::Mat real_blur;
//	cv::blur(src, real_blur, cv::Point(27, 27));
//	double abs_error = CalculateMeanError(test_blur, real_blur);
//	//MAE PER PIXEL ������� ���������� ���������� �� �������
//	double MAEPPPI = (double)abs_error / ((src.cols - 2) * (src.rows - 2));
//
//	GTEST_LOG_(INFO) << "The mean absolute error (MAE) / pixel: " << MAEPPPI;
//	EXPECT_NEAR(MAEPPPI, 0.0, 0.00003);
//
//	cv::imwrite("D:/opencv/repos/.outputImage/test_blur.jpg", test_blur);
//	cv::imwrite("D:/opencv/repos/.outputImage/real_blur.jpg", real_blur);
//}

//TEST(BlurTEST, HandlesGaussian2DTest) {
//	cv::Mat src = cv::imread("D:/opencv/repos/GoogleTest/Test1024x1024pi.jpg", cv::IMREAD_COLOR);
//	std::pair<uint, uint> Core(9, 9);
//	cv::Mat test_blur;
//	test_blur = ApplyCorrelation(src, GaussianBlur, Core, 20.0);
//	cv::Mat real_blur;
//	cv::GaussianBlur(src, real_blur, cv::Point(9, 9), 20.0, 20.0);
//	double abs_error = CalculateMeanError(test_blur, real_blur);
//	//MAE PER PIXEL ������� ���������� ���������� �� �������
//	double MAEPPPI = (double)abs_error / ((src.cols - 2) * (src.rows - 2));
//
//	GTEST_LOG_(INFO) << "The mean absolute error (MAE) / pixel: " << MAEPPPI;
//	EXPECT_NEAR(MAEPPPI, 0.0, 0.00003);
//
//	cv::imwrite("D:/opencv/repos/.outputImage/test_blur.jpg", test_blur);
//	cv::imwrite("D:/opencv/repos/.outputImage/real_blur.jpg", real_blur);
//}

//TEST(BlurTEST, HandlesMedianBlurTest) {
//	cv::Mat src = cv::imread("D:/opencv/repos/GoogleTest/Test1024x1024pi.jpg", cv::IMREAD_COLOR);
//	std::pair<uint, uint> Core(9, 9);
//	cv::Mat test_blur;
//	test_blur = ThrowNeighborhood(src, medianBlur, Core);
//	cv::Mat real_blur;
//	cv::medianBlur(src, real_blur, 9);
//	double abs_error = CalculateMeanError(test_blur, real_blur);
//	MAE PER PIXEL ������� ���������� ���������� �� �������
//	double MAEPPPI = (double)abs_error / ((src.cols - 2) * (src.rows - 2));
//
//	GTEST_LOG_(INFO) << "The mean absolute error (MAE) / pixel: " << MAEPPPI;
//	EXPECT_NEAR(MAEPPPI, 0.0, 0.00003);
//
//	cv::imwrite("D:/opencv/repos/.outputImage/test_blur.jpg", test_blur);
//	cv::imwrite("D:/opencv/repos/.outputImage/real_blur.jpg", real_blur);
//}

//TEST(BlurTEST, HandlesLaplacianTest) {
//	cv::Mat src = cv::imread("D:/opencv/repos/GoogleTest/Test1024x1024pi.jpg", cv::IMREAD_COLOR);
//	cv::Mat test_blur;
//	
//	EXPECT_NO_THROW(test_blur = ApplyCorrelation(src, Derivative, ProximityMask::getLaplacianMask(LaplacianMasks::NegMulx90)));
//	cv::Mat real_blur;
//	cv::Laplacian(src, real_blur, CV_8U);
//	//double abs_error = CalculateMeanError(test_blur, real_blur);
//	//MAE PER PIXEL ������� ���������� ���������� �� �������
//	//double MAEPPPI = (double)abs_error / ((src.cols - 2) * (src.rows - 2));
//
//	//GTEST_LOG_(INFO) << "The mean absolute error (MAE) / pixel: " << MAEPPPI;
//	//EXPECT_NEAR(MAEPPPI, 0.0, 0.00003);
//
//	cv::imwrite("D:/opencv/repos/.outputImage/test_blur.jpg", test_blur);
//	cv::imwrite("D:/opencv/repos/.outputImage/real_blur.jpg", real_blur);
//}

//TEST(BlurTEST, HandlesSobolTest) {
//	cv::Mat src = cv::imread("D:/opencv/repos/GoogleTest/Test1024x1024pi.jpg", cv::IMREAD_COLOR);
//	cv::Mat test_blur;
//
//	EXPECT_NO_THROW(test_blur = ApplyCorrelation(src, Derivative, ProximityMask::getSobelMask(SobelMasks::Left)));
//	cv::Mat real_blur;
//	cv::Sobel(src, real_blur, CV_32FC1, 0, 1);
//	//double abs_error = CalculateMeanError(test_blur, real_blur);
//	//MAE PER PIXEL ������� ���������� ���������� �� �������
//	//double MAEPPPI = (double)abs_error / ((src.cols - 2) * (src.rows - 2));
//
//	//GTEST_LOG_(INFO) << "The mean absolute error (MAE) / pixel: " << MAEPPPI;
//	//EXPECT_NEAR(MAEPPPI, 0.0, 0.00003);
//
//	cv::imwrite("D:/opencv/repos/.outputImage/test_blur.jpg", test_blur);
//	cv::imwrite("D:/opencv/repos/.outputImage/real_blur.jpg", real_blur);
//}

//TEST(BlurTEST, HandlesManualTest) {
//	cv::Mat src = cv::imread("D:/opencv/repos/GoogleTest/Test1024x1024pi.jpg", cv::IMREAD_COLOR);
//	cv::Mat test_blur;
//	ProximityMask maskObject;
//	maskObject.MaskAdapter({ {1,  0, -1},
//						     {0,  0,  0},
//						     {-1, 0,  1} });
//
//	maskObject.MaskAdapterCV({ {1,  0, -1},
//							   {0,  0,  0},
//							   {-1, 0,  1} });
//	EXPECT_NO_THROW(test_blur = ApplyCorrelation(src, Derivative, maskObject.ReservedMask));
//	cv::Mat real_blur;
//	cv::filter2D(src, real_blur, CV_64F, maskObject.ReservedMask3x3);
//	//double abs_error = CalculateMeanError(test_blur, real_blur);
//	//MAE PER PIXEL ������� ���������� ���������� �� �������
//	//double MAEPPPI = (double)abs_error / ((src.cols - 2) * (src.rows - 2));
//
//	//GTEST_LOG_(INFO) << "The mean absolute error (MAE) / pixel: " << MAEPPPI;
//	//EXPECT_NEAR(MAEPPPI, 0.0, 0.00003);
//
//	cv::imwrite("D:/opencv/repos/.outputImage/test_blur.jpg", test_blur);
//	cv::imwrite("D:/opencv/repos/.outputImage/real_blur.jpg", real_blur);
//}

TEST(PCHTEST, HandlesExtendMatrixZeros) {
	cv::Mat src = cv::imread("D:/opencv/repos/GoogleTest/SourceExtendMatrixZeros.jpg", cv::IMREAD_GRAYSCALE);
	cv::Mat prepared;
	try {
		prepared = ExtendMatrixZeros(src, 300, 300);
		cv::imwrite("D:/opencv/repos/.outputImage/Test_HandlesExtendMatrixZeros.jpg", prepared);
	}
	catch (const std::exception& e) {
		FAIL() << "std::exception thrown: " << e.what();
	}

	cv::Mat expect = cv::imread("D:/opencv/repos/GoogleTest/ExpectExtendMatrixZeros.jpg", cv::IMREAD_GRAYSCALE);
	EXPECT_TRUE(AreMatricesEqual(prepared, expect));
}

//TEST(FilterFunctionsTEST, HandlesGetSimmetricFilterImage) {
//	cv::Mat SimmetricFilterImage;
//	cv::Mat result;
//	EXPECT_NO_THROW(SimmetricFilterImage = GetSimmetricFilterImage(150, 150, PerfectLowPassFilter, 50));
//	// ������������ � ���������� � ���� CV_8U ��� �����������
//	normalize(SimmetricFilterImage, result, 0, 255, cv::NORM_MINMAX);
//	result.convertTo(result, CV_8U);
//	cv::extractChannel(result, result, 0);
//	cv::normalize(result, result, 0, 255, cv::NORM_MINMAX);
//	std::cout << "result: Type = " << result.type() << ", Channels = " << result.channels() << std::endl;
//	cv::imwrite("D:/opencv/repos/.outputImage/Test_HandlesGetSimmetricFilterImage.jpg", result);
//}

TEST(ImgProcessingModule_FunctionTest_SpatialMathFunc, HandlesFrequencyFiltering_LowPassFiltersScope_PerfectLowPassFilter) {
	cv::Mat src = cv::imread("D:/opencv/repos/GoogleTest/Test150x150pi.jpg", cv::IMREAD_GRAYSCALE);
	std::cout << "Expected type: " << src.type() << " Expected channels: " << src.channels() << " Expected dims: " << src.dims << " Expected depth: " << src.depth() << std::endl;
	cv::Mat src2 = cv::imread("D:/opencv/repos/GoogleTest/Test150x150pi.jpg", cv::IMREAD_COLOR);
	std::cout << "Colors type: " << src2.type() << " Colors channels: " << src2.channels() << " Colors dims: " << src2.dims << " Colors depth: " << src2.depth() << std::endl;
	std::vector<cv::Mat> channels;
	cv::split(src2, channels);
	std::cout << "channels1 type: " << channels[0].type() << " channels1 channels: " << channels[0].channels() << " channels1 dims: " << channels[0].dims << " channels1 depth: " << channels[0].depth() << std::endl;

	cv::Mat res = FrequencyFiltering(src2, FrequencyFilters::LowPass, PerfectLowPassFilter, 5);
	cv::imwrite("D:/opencv/repos/.outputImage/Test_HandlesFrequencyFiltering_PerfectLowPassFilter.jpg", res);
	cv::Mat tst;
	cv::GaussianBlur(src2, tst, cv::Point(7, 7), 10.0, 0.0);

	cv::Mat resFloat, tstFloat;
	res.convertTo(resFloat, CV_32F);
	tst.convertTo(tstFloat, CV_32F);
	std::cout << "resFloat: Type = " << resFloat.type() << ", Channels = " << resFloat.channels() << std::endl;
	std::cout << "tstFloat: Type = " << tstFloat.type() << ", Channels = " << tstFloat.channels() << std::endl;
	cv::Mat subFloat = resFloat - tstFloat;
	double minVal, maxVal;
	// ���������� ������������ � ������������� ��������
	cv::minMaxLoc(subFloat, &minVal, &maxVal);
	GTEST_LOG_(INFO) << "Maximum int / pixel: " << maxVal;
	EXPECT_NEAR(maxVal, 0.0, 100); 
}

TEST(ImgProcessingModule_FunctionTest_SpatialMathFunc, HandlesFrequencyFiltering_LowPassFiltersScope_ButterworthLowPassFilter) {
	cv::Mat src = cv::imread("D:/opencv/repos/GoogleTest/Test150x150pi.jpg", cv::IMREAD_GRAYSCALE);
	std::cout << "Expected type: " << src.type() << " Expected channels: " << src.channels() << " Expected dims: " << src.dims << " Expected depth: " << src.depth() << std::endl;
	cv::Mat src2 = cv::imread("D:/opencv/repos/GoogleTest/Test150x150pi.jpg", cv::IMREAD_COLOR);
	std::cout << "Colors type: " << src2.type() << " Colors channels: " << src2.channels() << " Colors dims: " << src2.dims << " Colors depth: " << src2.depth() << std::endl;
	std::vector<cv::Mat> channels;
	cv::split(src2, channels);
	std::cout << "channels1 type: " << channels[0].type() << " channels1 channels: " << channels[0].channels() << " channels1 dims: " << channels[0].dims << " channels1 depth: " << channels[0].depth() << std::endl;

	cv::Mat res = FrequencyFiltering(src2, FrequencyFilters::LowPass, ButterworthLowPassFilter, 5, 5);
	cv::imwrite("D:/opencv/repos/.outputImage/Test_HandlesFrequencyFiltering_ButterworthLowPassFilte.jpg", res);
	cv::Mat tst;
	cv::GaussianBlur(src2, tst, cv::Point(7, 7), 10.0, 0.0);

	cv::Mat resFloat, tstFloat;
	res.convertTo(resFloat, CV_32F);
	tst.convertTo(tstFloat, CV_32F);
	std::cout << "resFloat: Type = " << resFloat.type() << ", Channels = " << resFloat.channels() << std::endl;
	std::cout << "tstFloat: Type = " << tstFloat.type() << ", Channels = " << tstFloat.channels() << std::endl;
	cv::Mat subFloat = resFloat - tstFloat;
	double minVal, maxVal;
	// ���������� ������������ � ������������� ��������
	cv::minMaxLoc(subFloat, &minVal, &maxVal);
	GTEST_LOG_(INFO) << "Maximum int / pixel: " << maxVal;
	EXPECT_NEAR(maxVal, 0.0, 100);
}

TEST(ImgProcessingModule_FunctionTest_SpatialMathFunc, HandlesFrequencyFiltering_LowPassFiltersScope_GaussianLowPassFilter) {
	cv::Mat src = cv::imread("D:/opencv/repos/GoogleTest/Test150x150pi.jpg", cv::IMREAD_GRAYSCALE);
	std::cout << "Expected type: " << src.type() << " Expected channels: " << src.channels() << " Expected dims: " << src.dims << " Expected depth: " << src.depth() << std::endl;
	cv::Mat src2 = cv::imread("D:/opencv/repos/GoogleTest/Test150x150pi.jpg", cv::IMREAD_COLOR);
	std::cout << "Colors type: " << src2.type() << " Colors channels: " << src2.channels() << " Colors dims: " << src2.dims << " Colors depth: " << src2.depth() << std::endl;
	std::vector<cv::Mat> channels;
	cv::split(src2, channels);
	std::cout << "channels1 type: " << channels[0].type() << " channels1 channels: " << channels[0].channels() << " channels1 dims: " << channels[0].dims << " channels1 depth: " << channels[0].depth() << std::endl;

	cv::Mat res = FrequencyFiltering(src2, FrequencyFilters::LowPass, GaussianLowPassFilter, 5);
	cv::imwrite("D:/opencv/repos/.outputImage/Test_HandlesFrequencyFiltering_GaussianLowPassFilter.jpg", res);
	cv::Mat tst;
	cv::GaussianBlur(src2, tst, cv::Point(7, 7), 10.0, 0.0);

	cv::Mat resFloat, tstFloat;
	res.convertTo(resFloat, CV_32F);
	tst.convertTo(tstFloat, CV_32F);
	std::cout << "resFloat: Type = " << resFloat.type() << ", Channels = " << resFloat.channels() << std::endl;
	std::cout << "tstFloat: Type = " << tstFloat.type() << ", Channels = " << tstFloat.channels() << std::endl;
	cv::Mat subFloat = resFloat - tstFloat;
	double minVal, maxVal;
	// ���������� ������������ � ������������� ��������
	cv::minMaxLoc(subFloat, &minVal, &maxVal);
	GTEST_LOG_(INFO) << "Maximum int / pixel: " << maxVal;
	EXPECT_NEAR(maxVal, 0.0, 100);
}

TEST(ImgProcessingModule_FunctionTest_SpatialMathFunc, HandlesFrequencyFiltering_HightPassFiltersScope_PerfectHightPassFilter) {
	cv::Mat src = cv::imread("D:/opencv/repos/GoogleTest/Test150x150pi.jpg", cv::IMREAD_GRAYSCALE);
	std::cout << "Expected type: " << src.type() << " Expected channels: " << src.channels() << " Expected dims: " << src.dims << " Expected depth: " << src.depth() << std::endl;
	cv::Mat src2 = cv::imread("D:/opencv/repos/GoogleTest/Test150x150pi.jpg", cv::IMREAD_COLOR);
	std::cout << "Colors type: " << src2.type() << " Colors channels: " << src2.channels() << " Colors dims: " << src2.dims << " Colors depth: " << src2.depth() << std::endl;
	std::vector<cv::Mat> channels;
	cv::split(src2, channels);
	std::cout << "channels1 type: " << channels[0].type() << " channels1 channels: " << channels[0].channels() << " channels1 dims: " << channels[0].dims << " channels1 depth: " << channels[0].depth() << std::endl;

	cv::Mat res = FrequencyFiltering(src2, FrequencyFilters::HightPass, PerfectLowPassFilter, 5);
	cv::imwrite("D:/opencv/repos/.outputImage/Test_HandlesFrequencyFiltering_PerfectHightPassFilter.jpg", res);
	cv::Mat tst;
	cv::GaussianBlur(src2, tst, cv::Point(0, 0), 3.0);

	cv::Mat resFloat, tstFloat;
	res.convertTo(resFloat, CV_32F);
	tst.convertTo(tstFloat, CV_32F);
	std::cout << "resFloat: Type = " << resFloat.type() << ", Channels = " << resFloat.channels() << std::endl;
	std::cout << "tstFloat: Type = " << tstFloat.type() << ", Channels = " << tstFloat.channels() << std::endl;
	cv::Mat subFloat = resFloat - tstFloat;
	double minVal, maxVal;
	// ���������� ������������ � ������������� ��������
	cv::minMaxLoc(subFloat, &minVal, &maxVal);
	GTEST_LOG_(INFO) << "Maximum int / pixel: " << maxVal;
	EXPECT_NEAR(maxVal, 0.0, 100);
}

TEST(ImgProcessingModule_FunctionTest_SpatialMathFunc, HandlesFrequencyFiltering_HightPassFiltersScope_ButterworthLowPassFilter) {
	cv::Mat src = cv::imread("D:/opencv/repos/GoogleTest/Test150x150pi.jpg", cv::IMREAD_GRAYSCALE);
	std::cout << "Expected type: " << src.type() << " Expected channels: " << src.channels() << " Expected dims: " << src.dims << " Expected depth: " << src.depth() << std::endl;
	cv::Mat src2 = cv::imread("D:/opencv/repos/GoogleTest/Test150x150pi.jpg", cv::IMREAD_COLOR);
	std::cout << "Colors type: " << src2.type() << " Colors channels: " << src2.channels() << " Colors dims: " << src2.dims << " Colors depth: " << src2.depth() << std::endl;
	std::vector<cv::Mat> channels;
	cv::split(src2, channels);
	std::cout << "channels1 type: " << channels[0].type() << " channels1 channels: " << channels[0].channels() << " channels1 dims: " << channels[0].dims << " channels1 depth: " << channels[0].depth() << std::endl;

	cv::Mat res = FrequencyFiltering(src2, FrequencyFilters::HightPass, ButterworthLowPassFilter, 5, 5);
	cv::imwrite("D:/opencv/repos/.outputImage/Test_HandlesFrequencyFiltering_ButterworthHightPassFilte.jpg", res);
	cv::Mat tst;
	cv::GaussianBlur(src2, tst, cv::Point(7, 7), 10.0, 0.0);

	cv::Mat resFloat, tstFloat;
	res.convertTo(resFloat, CV_32F);
	tst.convertTo(tstFloat, CV_32F);
	std::cout << "resFloat: Type = " << resFloat.type() << ", Channels = " << resFloat.channels() << std::endl;
	std::cout << "tstFloat: Type = " << tstFloat.type() << ", Channels = " << tstFloat.channels() << std::endl;
	cv::Mat subFloat = resFloat - tstFloat;
	double minVal, maxVal;
	// ���������� ������������ � ������������� ��������
	cv::minMaxLoc(subFloat, &minVal, &maxVal);
	GTEST_LOG_(INFO) << "Maximum int / pixel: " << maxVal;
	EXPECT_NEAR(maxVal, 0.0, 100);
}

TEST(ImgProcessingModule_FunctionTest_SpatialMathFunc, HandlesFrequencyFiltering_HightPassFiltersScope_GaussianLowPassFilter) {
	cv::Mat src = cv::imread("D:/opencv/repos/GoogleTest/Test150x150pi.jpg", cv::IMREAD_GRAYSCALE);
	std::cout << "Expected type: " << src.type() << " Expected channels: " << src.channels() << " Expected dims: " << src.dims << " Expected depth: " << src.depth() << std::endl;
	cv::Mat src2 = cv::imread("D:/opencv/repos/GoogleTest/Test150x150pi.jpg", cv::IMREAD_COLOR);
	std::cout << "Colors type: " << src2.type() << " Colors channels: " << src2.channels() << " Colors dims: " << src2.dims << " Colors depth: " << src2.depth() << std::endl;
	std::vector<cv::Mat> channels;
	cv::split(src2, channels);
	std::cout << "channels1 type: " << channels[0].type() << " channels1 channels: " << channels[0].channels() << " channels1 dims: " << channels[0].dims << " channels1 depth: " << channels[0].depth() << std::endl;

	cv::Mat res = FrequencyFiltering(src2, FrequencyFilters::HightPass, GaussianLowPassFilter, 5);
	cv::imwrite("D:/opencv/repos/.outputImage/Test_HandlesFrequencyFiltering_GaussianHightPassFilter.jpg", res);
	cv::Mat tst;
	cv::GaussianBlur(src2, tst, cv::Point(7, 7), 10.0, 0.0);

	cv::Mat resFloat, tstFloat;
	res.convertTo(resFloat, CV_32F);
	tst.convertTo(tstFloat, CV_32F);
	std::cout << "resFloat: Type = " << resFloat.type() << ", Channels = " << resFloat.channels() << std::endl;
	std::cout << "tstFloat: Type = " << tstFloat.type() << ", Channels = " << tstFloat.channels() << std::endl;
	cv::Mat subFloat = resFloat - tstFloat;
	double minVal, maxVal;
	// ���������� ������������ � ������������� ��������
	cv::minMaxLoc(subFloat, &minVal, &maxVal);
	GTEST_LOG_(INFO) << "Maximum int / pixel: " << maxVal;
	EXPECT_NEAR(maxVal, 0.0, 100);
}

TEST(ImgProcessingModule_FunctionTest_SpatialMathFunc, HandlesFrequencyFiltering_BandPassFiltersScope_PerfectBandPassFilter) {
	cv::Mat src = cv::imread("D:/opencv/repos/GoogleTest/Test150x150pi.jpg", cv::IMREAD_GRAYSCALE);
	std::cout << "Expected type: " << src.type() << " Expected channels: " << src.channels() << " Expected dims: " << src.dims << " Expected depth: " << src.depth() << std::endl;
	cv::Mat src2 = cv::imread("D:/opencv/repos/GoogleTest/Test150x150pi.jpg", cv::IMREAD_COLOR);
	std::cout << "Colors type: " << src2.type() << " Colors channels: " << src2.channels() << " Colors dims: " << src2.dims << " Colors depth: " << src2.depth() << std::endl;
	std::vector<cv::Mat> channels;
	cv::split(src2, channels);
	std::cout << "channels1 type: " << channels[0].type() << " channels1 channels: " << channels[0].channels() << " channels1 dims: " << channels[0].dims << " channels1 depth: " << channels[0].depth() << std::endl;

	cv::Mat res = FrequencyFiltering(src2, PerfectBandPassFilter, 5, 10);
	cv::imwrite("D:/opencv/repos/.outputImage/Test_HandlesFrequencyFiltering_PerfectBandPassFilter.jpg", res);
	cv::Mat tst;
	cv::GaussianBlur(src2, tst, cv::Point(7, 7), 10.0, 0.0);

	cv::Mat resFloat, tstFloat;
	res.convertTo(resFloat, CV_32F);
	tst.convertTo(tstFloat, CV_32F);
	std::cout << "resFloat: Type = " << resFloat.type() << ", Channels = " << resFloat.channels() << std::endl;
	std::cout << "tstFloat: Type = " << tstFloat.type() << ", Channels = " << tstFloat.channels() << std::endl;
	cv::Mat subFloat = resFloat - tstFloat;
	double minVal, maxVal;
	// ���������� ������������ � ������������� ��������
	cv::minMaxLoc(subFloat, &minVal, &maxVal);
	GTEST_LOG_(INFO) << "Maximum int / pixel: " << maxVal;
	EXPECT_NEAR(maxVal, 0.0, 100);
}

TEST(ImgProcessingModule_FunctionTest_SpatialMathFunc, HandlesFrequencyFiltering_BandPassFiltersScope_ButterworthBandPassFilter) {
	cv::Mat src = cv::imread("D:/opencv/repos/GoogleTest/Test150x150pi.jpg", cv::IMREAD_GRAYSCALE);
	std::cout << "Expected type: " << src.type() << " Expected channels: " << src.channels() << " Expected dims: " << src.dims << " Expected depth: " << src.depth() << std::endl;
	cv::Mat src2 = cv::imread("D:/opencv/repos/GoogleTest/Test150x150pi.jpg", cv::IMREAD_COLOR);
	std::cout << "Colors type: " << src2.type() << " Colors channels: " << src2.channels() << " Colors dims: " << src2.dims << " Colors depth: " << src2.depth() << std::endl;
	std::vector<cv::Mat> channels;
	cv::split(src2, channels);
	std::cout << "channels1 type: " << channels[0].type() << " channels1 channels: " << channels[0].channels() << " channels1 dims: " << channels[0].dims << " channels1 depth: " << channels[0].depth() << std::endl;

	cv::Mat res = FrequencyFiltering(src2, ButterworthBandPassFilter, 5, 10, 100);
	cv::imwrite("D:/opencv/repos/.outputImage/Test_HandlesFrequencyFiltering_ButterworthBandPassFilter.jpg", res);
	cv::Mat tst;
	cv::GaussianBlur(src2, tst, cv::Point(7, 7), 10.0, 0.0);

	cv::Mat resFloat, tstFloat;
	res.convertTo(resFloat, CV_32F);
	tst.convertTo(tstFloat, CV_32F);
	std::cout << "resFloat: Type = " << resFloat.type() << ", Channels = " << resFloat.channels() << std::endl;
	std::cout << "tstFloat: Type = " << tstFloat.type() << ", Channels = " << tstFloat.channels() << std::endl;
	cv::Mat subFloat = resFloat - tstFloat;
	double minVal, maxVal;
	// ���������� ������������ � ������������� ��������
	cv::minMaxLoc(subFloat, &minVal, &maxVal);
	GTEST_LOG_(INFO) << "Maximum int / pixel: " << maxVal;
	EXPECT_NEAR(maxVal, 0.0, 100);
}

TEST(ImgProcessingModule_FunctionTest_SpatialMathFunc, HandlesFrequencyFiltering_BandPassFiltersScope_GaussianBandPassFilter) {
	cv::Mat src = cv::imread("D:/opencv/repos/GoogleTest/Test150x150pi.jpg", cv::IMREAD_GRAYSCALE);
	std::cout << "Expected type: " << src.type() << " Expected channels: " << src.channels() << " Expected dims: " << src.dims << " Expected depth: " << src.depth() << std::endl;
	cv::Mat src2 = cv::imread("D:/opencv/repos/GoogleTest/Test150x150pi.jpg", cv::IMREAD_COLOR);
	std::cout << "Colors type: " << src2.type() << " Colors channels: " << src2.channels() << " Colors dims: " << src2.dims << " Colors depth: " << src2.depth() << std::endl;
	std::vector<cv::Mat> channels;
	cv::split(src2, channels);
	std::cout << "channels1 type: " << channels[0].type() << " channels1 channels: " << channels[0].channels() << " channels1 dims: " << channels[0].dims << " channels1 depth: " << channels[0].depth() << std::endl;

	cv::Mat res = FrequencyFiltering(src2, GaussianBandPassFilter, 5, 10);
	cv::imwrite("D:/opencv/repos/.outputImage/Test_HandlesFrequencyFiltering_GaussianBandPassFilter.jpg", res);
	cv::Mat tst;
	cv::GaussianBlur(src2, tst, cv::Point(7, 7), 10.0, 0.0);

	cv::Mat resFloat, tstFloat;
	res.convertTo(resFloat, CV_32F);
	tst.convertTo(tstFloat, CV_32F);
	std::cout << "resFloat: Type = " << resFloat.type() << ", Channels = " << resFloat.channels() << std::endl;
	std::cout << "tstFloat: Type = " << tstFloat.type() << ", Channels = " << tstFloat.channels() << std::endl;
	cv::Mat subFloat = resFloat - tstFloat;
	double minVal, maxVal;
	// ���������� ������������ � ������������� ��������
	cv::minMaxLoc(subFloat, &minVal, &maxVal);
	GTEST_LOG_(INFO) << "Maximum int / pixel: " << maxVal;
	EXPECT_NEAR(maxVal, 0.0, 100);
}

double CalculateMeanError(const cv::Mat& _mat1, const cv::Mat& _mat2) {
	assert(_mat1.size() == _mat2.size() && _mat1.type() == _mat2.type());

	cv::Mat mat1 = CropMatrix(_mat1);
	cv::Mat mat2 = CropMatrix(_mat2);

	double total_error = 0.0;
	int num_pixels = mat1.rows * mat1.cols;

	// �������� �� ���� �������� � ��������� ���������� ���������� ��� ������� ������
	for (int y = 0; y < mat1.rows; ++y) {
		for (int x = 0; x < mat1.cols; ++x) {
			cv::Vec3b pixel1 = mat1.at<cv::Vec3b>(y, x); 
			cv::Vec3b pixel2 = mat2.at<cv::Vec3b>(y, x);

			// ������� ���������� ������� ��� ������� ��������� ������
			for (int channel = 0; channel < 3; ++channel) {
				total_error += std::abs(static_cast<double>(pixel1[channel]) - static_cast<double>(pixel2[channel]));
			}
		}
	}

	// ��������� ������� ���������� ����������
	return total_error / (num_pixels * 3);  // 3 ������
}

cv::Mat CropMatrix(const cv::Mat& src) {
	// �������� �� ������ ������� � ������ �������
	return src(cv::Range(1, src.rows - 1), cv::Range(1, src.cols - 1));
}

bool AreMatricesEqual(const cv::Mat& mat1, const cv::Mat& mat2) {
	if (mat1.size() != mat2.size() || mat1.type() != mat2.type()) {
		return false; // ������� ��� ���� �� ���������
	}
	for (int Y = 0; Y < mat1.rows; Y++) {
		for (int X = 0; X < mat1.cols; X++) {
			uchar pixel1 = mat1.at<uchar>(X, Y);
			uchar pixel2 = mat2.at<uchar>(X, Y);
			if (pixel1 != pixel2) {
				for (int i = 0; i < 3; i++) {
					double dev1 = (double)pixel1 - pixel2;
					if (abs(dev1) > 25) {
						return false;
					}
				}
			}
		}
	}
	return true; // �������� �� ������������ ���� ���������
}
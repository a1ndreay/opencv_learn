#include "pch.h"
#include "LinealMathFunc.h"


/// <summary>
/// Усредняющий фильтр.
/// </summary>
/// <param name="src">исходная матрица</param>
/// <param name="Locality">ядро</param>
/// <param name="Core">параметры маски</param>
/// <returns>усреднённое значение пикселей окрестности</returns>
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
/// Медианный фильтр.
/// </summary>
/// <param name="src">исходная матрица</param>
/// <param name="Locality">ядро</param>
/// <param name="Core">параметры маски</param>
/// <returns>медиана окрестности</returns>
cv::Vec3d medianBlur(const cv::Mat& src, const std::vector<cv::Point>& Locality, std::pair<uint, uint> Core) {
    cv::Vec3d Val;
    uint Sum = 0;
    std::vector<double> c[3]; std::sort(c[0].begin(), c[0].end());
    for (cv::Point Point : Locality)
    {
        cv::Vec3d _MappedPoint = src.at<cv::Vec3b>(Point);
        c[0].push_back(_MappedPoint[0]);
        c[1].push_back(_MappedPoint[1]);
        c[2].push_back(_MappedPoint[2]);
    }
    std::sort(c[0].begin(), c[0].end());
    std::sort(c[1].begin(), c[1].end());
    std::sort(c[2].begin(), c[2].end());
    Val = cv::Vec3d((double)c[0].at(c[0].size() / 2), (double)c[1].at(c[1].size() / 2), (double)c[2].at(c[2].size() / 2));
    return Val;
}
/// <summary>
/// Функция гауссовой фильтрации изображения.
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
/// Делает единичный шаг кореляции, используя заданную маску коэффициентов. В отличии от обычной корреляции дополнительно ограничивает диапазон в 8-битное изображение (0; 255.0) 
/// </summary>
/// <param name="src"></param>
/// <param name="Locality"></param>
/// <param name="Core"></param>
/// <param name="coefficients">Маска коэффициентов</param>
/// <returns></returns>
cv::Vec3d Derivative(const cv::Mat& src, const std::vector<cv::Point>& Locality, std::pair<uint, uint> Core, std::vector<std::vector<double>> coefficients)
{
    cv::Vec3d Val = Correlation(src, Locality, Core, coefficients);
    // Ограничение значений в допустимый диапазон (clamping)
    for (int i = 0; i < 3; i++) {
        Val[i] = std::max(0.0, std::min(255.0, Val[i]));
    }
    return Val;
}

/// <summary>
/// Создание маски коээфициентов с нормальным распределением
/// </summary>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="sigma">Стандартное отклонение</param>
/// <returns>Возвращает маску коэффициентов</returns>
std::vector<std::vector<double>> createGaussianKernel(int width, int height, double sigma) {
    std::vector<std::vector<double>> coefficients(width, std::vector<double>(height));

    // Центр ядра
    int centerX = width / 2;
    int centerY = height / 2;

    double sum = 0.0;  // Для нормализации

    // Заполнение матрицы коэффициентов
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            int x = i - centerX;
            int y = j - centerY;
            coefficients[i][j] = gaussian2D(x, y, sigma);
            sum += coefficients[i][j];
        }
    }

    // Нормализация ядра (чтобы сумма всех элементов была равна 1)
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            coefficients[i][j] /= sum;
        }
    }

    return coefficients;
}

/// <summary>
/// Гауссова функция для двух переменных
/// «Гауссова функция двух переменных» (Гонсалес, Р. Цифровая обработка изображений  / Р. Гонсалес, Р. Вудс. — 3-е изд., испр. и доп. — Москва : Техносфера, 2012. — ISBN 978-5-94836-331-8.
///  — Текст : электронный // Лань : электронно-библиотечная система. — URL: https://e.lanbook.com/book/73514  — С. 194.).
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="sigma">Стандартное отклонение</param>
/// <returns></returns>
double gaussian2D(int x, int y, double sigma) {
    double exponent = -(x * x + y * y) / (2 * sigma * sigma);
    return std::exp(exponent);
}

/// <summary>
/// Функция корелляции фильтра
/// </summary>
/// <param name="src">Исходная матрицы</param>
/// <param name="Locality">Ядро</param>
/// <param name="Core">Параметры ядра</param>
/// <param name="coefficients">Маска коэффициентов</param>
/// <returns>Смещение корреляции</returns>
cv::Vec3d Correlation(const cv::Mat& src, const std::vector<cv::Point>& Locality, std::pair<uint, uint> Core, std::vector<std::vector<double>> coefficients) {
    std::stack<cv::Point> SLocality = ConvertVectorToStack(Locality);
    cv::Vec3d Val(0, 0, 0);
    int a = (Core.first - 1) / 2;
    int b = (Core.second - 1) / 2;

    for (int s = -a; s <= a; s++) {  
        for (int t = -b; t <= b; t++) {
            cv::Point Point = SLocality.top();
            SLocality.pop();
            cv::Point SPoint = shiftCoordinates(s, t, a, b); 
            cv::Vec3d _MappedPoint = src.at<cv::Vec3b>(Point.x, Point.y);
            Val += coefficients[SPoint.x][SPoint.y] * _MappedPoint;
        }
    }
    return Val;
}


/// <summary>
/// Функция свёртки фильтра
/// </summary>
/// <param name="src">Исходная матрицы</param>
/// <param name="Locality">Ядро</param>
/// <param name="Core">Параметры ядра</param>
/// <param name="coefficients">Маска коэффициентов</param>
/// <returns>Смещение свёртки</returns>
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

// Функция для преобразования координат (смещаем систему координат из центра в левый верхний угол) параллельный перенос координат
cv::Point shiftCoordinates(int s, int t, int a, int b) {
    // Сдвиг координат на a и b для правильного доступа к вектору
    return cv::Point(s + a, t + b);
}

//прямое дискретное преобразование фурье
cv::Mat DPF(const cv::Mat& src, int flag) {
    cv::Mat img_src;
    cv::Mat img_complex;
    cv::Mat img_dft;
    cv::Mat img_idft;
    cv::Mat img_dst;
    int rows;
    int cols;
    int row;
    int col;
    double val_real;
    cv::Vec2d val_complex;
    img_src = src;
    rows = cv::getOptimalDFTSize(img_src.rows);
    cols = cv::getOptimalDFTSize(img_src.cols);
    img_complex.create(cv::Size(cols, rows), CV_64FC2);
    for (row = 0; row < rows; row++)
        for (col = 0; col < cols; col++)
        {
            if (row < img_src.rows)
            {
                if (col < img_src.cols)
                    val_real =
                    (double)img_src.at<uchar>(row, col);
                else
                    val_real = 0.0;
            }
            else
                val_real = 0.0;
            img_complex.at<cv::Vec2d>(row, col)[0] =
                val_real;
            img_complex.at<cv::Vec2d>(row, col)[1] = 0.0;
        }
    img_dft.create(cv::Size(cols, rows), CV_64FC2);
    img_idft.create(cv::Size(cols, rows), CV_64FC2);
    img_dst.create(cv::Size(img_src.cols, img_src.rows),
        CV_8UC1);
        cv::dft(img_complex, img_dft, flag, img_src.rows);
    dft(img_dft, img_idft, cv::DFT_INVERSE | cv::DFT_SCALE,
        img_src.rows);
    for (row = 0; row < img_dst.rows; row++)
        for (col = 0; col < img_dst.cols; col++)
        {
            val_complex = img_idft.at<cv::Vec2d>(row, col);
            img_dst.at<uchar>(row, col) =
                (uchar)val_complex[0];
        }
    return img_dst;
}

cv::Mat NormalizeColorRange_CV_8UC3(const cv::Mat& src) {
                                                       // Создаем матрицу для работы с double
    cv::Mat srcDouble = src;
    src.convertTo(srcDouble, CV_64F);                // Конвертируем исходное изображение в тип double

    cv::Mat channels[3];
    cv::split(srcDouble, channels);                    // Разделяем на 3 канала (B, G, R)

    cv::Mat Minimazed[3];
    for (int c = 0; c < 3; c++) {
        double minVal, maxVal;                         // Локальные минимумы и максимумы каналов исходной матрицы
        cv::minMaxLoc(channels[c], &minVal, &maxVal);  // Находим минимум и максимум для канала исходной матрицы

                                                       // Минимизируем каждый канал
        Minimazed[c] = (channels[c] - minVal);         // Минимизируем каналы матрицы для локального минимума
    }

    cv::Mat Normalized[3];                              //Нормализованная матрица
    for (int c = 0; c < 3; c++) {
        double minVal, maxVal;                          // Локальные минимумы и максимумы каналов минимизированной матрицы
        cv::minMaxLoc(Minimazed[c], &minVal, &maxVal);  // Находим минимум и максимум для канала минимизированной матрицы

                                                        // Минимизируем каждый канал
        Normalized[c] = (Minimazed[c] / maxVal) * 255.0;
    }
                                                        // Объединяем обратно каналы
    cv::Mat result;
    cv::merge(Normalized, 3, result);
                                                        // Преобразуем матрицу обратно в 8-битное изображение
    result.convertTo(result, CV_8UC3);                  // Конвертируем в 8-битное изображение с 3 каналами

    return result;
}
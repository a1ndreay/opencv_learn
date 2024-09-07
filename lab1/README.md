### Цифровая обработка изображений
### Отчет по лабораторной работе **1** 

<div style="display: flex; flex-direction: column; gap: 5px; font-size: 14pt; border-top: 1px solid #fff; border-bottom: 1px solid #fff; padding: 10px">
<div><b>Выполнил</b>: Зорькин Андрей гр. 4308.</div>
<div><b>Цель</b>: Целью данной работы является освоить базовые функции и структуры данных, предоставляемые библиотекой <a href="https://docs.opencv.org/4.x/index.html">[opencv]. </a></div>
<div><b>Задача</b>: Разработать программу рисования треугольников с сохранением результата в файле. </div>
</div>

<h3>Ниже изображён результат работы программы: </h3>
![saved_image](https://github.com/user-attachments/assets/080ae3ae-1f3c-4a3d-8dfe-35bc36f675eb)

<h3>Ниже представлен листинг программы: </h3>
```cpp

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

const char* winname = "Template window";
std::string save_path = "C:/Users/Андрей/Downloads/saved_image.png";
Rect trinangle;
Rect tmp;
bool lockEvent = false;

void my_mouse_callback(int event, int x, int y, int flags, void* param);
void draw_triangle(Mat* pimg, Rect rect);
void log_rect(const Rect& rect);

void log_rect(const Rect& rect) {
    if (tmp != rect) {
        tmp = rect;
        std::cout << "[INFO:        ] [x, y] = ["
            << rect.x << ", " << rect.y <<
            "] [width, height] = ["
            << rect.width << ", " << rect.height << "]" << std::endl;
    }
    if (rect.empty()) {
        return;
    }
}

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
        draw_triangle(pimg, trinangle);
        break;
    }
}

std::vector<Point> ConvertRectToTrianglePoints(const Rect& rect) {
    // Левая нижняя точка
    Point2f leftBottom(rect.x, rect.y + rect.height);

    // Правая нижняя точка
    Point2f rightBottom(rect.x + rect.width, (rect.y + rect.height));

    // Верхняя точка
    Point2f top(rect.x + rect.width / 2, rect.y );

    // Вектор с тремя точками
    std::vector<Point> trianglePoints = { leftBottom, rightBottom, top };

    // Возвращаем InputArrayOfArrays
    return trianglePoints;
};

void draw_triangle(Mat* pimg, Rect rect) {
    
    log_rect(rect);

    // Массив точек для рисования
    std::vector<Point> points = ConvertRectToTrianglePoints(rect);

    // Массив, необходимый для функции fillPoly
    const Point* pts = points.data();
    int npts = static_cast<int>(points.size());

    // Заполняем треугольник на изображении красным цветом
    fillPoly(*pimg, &pts, &npts, 1, Scalar(0, 0, 255)); // Используем красный цвет
}
int main()
{
    
    std::string image_path = "C:/Users/Андрей/Downloads/code.png";
    Mat image = Mat(Size(400, 400), CV_8UC3,
        Scalar(0xff, 0xff, 0xff));
    Mat temp = image.clone();

    MouseCallback onMouse = my_mouse_callback;
    trinangle = Rect(-1, -1, 0, 0);
    namedWindow(winname);

    setMouseCallback(winname, onMouse, (void*)&image);
    while (1)
    {
        image.copyTo(temp);
        if (lockEvent) draw_triangle(&temp, trinangle);
        imshow(winname, temp);
        if (waitKey(15) == 27) break; //escape
    }
    // Сохранение изображения в файл
	if (!imwrite(save_path, temp)) {
	    std::cerr << "Ошибка при сохранении изображения!" << std::endl;
	}
	else {
	    std::cout << "Изображение успешно сохранено в " << save_path << std::endl;
	}
	destroyWindow(winname);
    destroyWindow(winname);
    return 0;
}
```


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
 * Сохранение выделенной области изображения
 */

 // Code starts here

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

std::string save_path = "C:/Users/Андрей/Downloads/cropped_image.png";
std::string image_path = "C:/Users/Андрей/Downloads/code.png";
const char* winname = "Template window";
Rect box;
Rect tmp;
Mat image;
bool lockEvent = false;

void my_mouse_callback(int event, int x, int y, int flags, void* param);
void draw_box(Mat* pimg, Rect rect);
void log_rect(const Rect& rect);
void trim_img(Mat& pimg, Rect rect);

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


void draw_box(Mat* pimg, Rect rect)
{
    log_rect(rect);
    rectangle(
        *pimg,
        Point(box.x, box.y),
        Point(box.x + box.width, box.y + box.height),
        Scalar(0x00, 0x00, 0x00));
}

void trim_img(Mat& pimg, Rect rect) {
    if (rect.x < 0) rect.x = 0;
    if (rect.y < 0) rect.y = 0;
    if (rect.width > pimg.cols - rect.x) rect.width = pimg.cols - rect.x;
    if (rect.height > pimg.rows - rect.y) rect.height = pimg.rows - rect.y;

    // Обрезка изображения по указанной области
    Mat cropped = pimg(rect);

    // Копирование обрезанного изображения обратно в pimg
    cropped.copyTo(pimg);
}

void my_mouse_callback(int event, int x, int y, int flags, void* param)
{
    Mat* pimg = (Mat*)param;
    switch (event)
    {
    case EVENT_MOUSEMOVE:
        if (lockEvent)
        {
            box.width = x - box.x;
            box.height = y - box.y;
        }
        break;
    case EVENT_LBUTTONDOWN:
        lockEvent = true;
        box = Rect(x, y, 0, 0);
        break;
    case EVENT_LBUTTONUP:
        lockEvent = false;
        if (box.width < 0)
        {
            box.x += box.width;
            box.width *= -1;
        }
        if (box.height < 0)
        {
            box.y += box.height;
            box.height *= -1;
        }
        draw_box(pimg, box);
        trim_img(*pimg, box);
        break;
    }
}

int main()
{
    image = imread(image_path, IMREAD_COLOR);
    Mat temp = image.clone();

    MouseCallback onMouse = my_mouse_callback;
    box = Rect(-1, -1, 0, 0);
    namedWindow(winname);

    setMouseCallback(winname, onMouse, (void*)&image);
    while (1)
    {
        image.copyTo(temp);
        if (lockEvent) draw_box(&temp, box);
        imshow(winname, temp);
        if (waitKey(15) == 27) break; //escape
    }
    if (!imwrite(save_path, temp)) {
        std::cerr << "Ошибка при сохранении изображения!" << std::endl;
    }
    else {
        std::cout << "Изображение успешно сохранено в " << save_path << std::endl;
    }
    destroyWindow(winname);
    return 0;
}
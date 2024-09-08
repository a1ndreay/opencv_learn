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
 * Склеивание двух изображений и сохранение результата
 */

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

std::string save_path = "C:/Users/Андрей/Downloads/cropped_image.png";
std::string first_image_path = "D:/opencv/repos/lab1_3/lab1_3/2024-09-08-205001.png";
std::string second_image_path = "D:/opencv/repos/lab1_3/lab1_3/2024-09-08-204553.png";
const char* winname = "Template window";
Rect tmp;

void concat(Mat& pimg, Mat* fimg, Mat* simg);


void concat(Mat& pimg, Mat* fimg, Mat* simg, Point pos){
    int newWidth = std::max(fimg->cols, pos.x + simg->cols);
    int newHeight = std::max(fimg->rows, pos.y + simg->rows);

    // Создаем изображение с белым фоном
    pimg.create(newHeight, newWidth, fimg->type());
    pimg.setTo(Scalar(255, 255, 255)); // Белый фон

    // Копируем первое изображение в новое изображение
    Mat roi = pimg(Rect(0, 0, fimg->cols, fimg->rows));
    fimg->copyTo(roi);

    // Копируем второе изображение в новое изображение по указанной позиции
    roi = pimg(Rect(pos.x, pos.y, simg->cols, simg->rows));
    simg->copyTo(roi);
}

int main()
{
    Mat img1 = imread(first_image_path, IMREAD_COLOR);
    Mat img2 = imread(second_image_path, IMREAD_COLOR);
    Mat res;
    Point position(img1.cols, img1.rows); //позиция вставки по правый нижний угол первого изображения
    concat(res, &img1, &img2, position);
    Mat temp = res.clone();

    namedWindow(winname);
    imshow(winname, temp);

    while (1)
    {
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
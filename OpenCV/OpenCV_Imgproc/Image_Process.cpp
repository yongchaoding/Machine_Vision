//
//  Image_Process.cpp
//  OpenCV_Xcode_Project
//
//  Created by 丁永超 on 17/05/2017.
//  Copyright © 2017 Chad_Ding. All rights reserved.
//

//第六章 图像处理
//线性滤波：方框滤波，均值滤波，高斯滤波
//非线性滤波：中值滤波，双边滤波
//图像处理形态学：腐蚀，膨胀，开运算，闭运算，形态学梯度，顶帽，黑帽
//漫水填充
//图像缩放
//图像金字塔
//阈值化
#include <stdio.h>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

Mat srcImage;
int g_BoxFilterValue;
int g_BlurValue;
int g_GaussianBlurValue;
int g_medianBlurValue;
int g_BilateralFilterValue;

void on_BoxFilter(int, void*);
void on_Blur(int, void*);
void on_GaussianBlur(int, void*);
void on_medianBlur(int, void*);
void on_BilateralFilter(int, void*);

int main(int argc, char** argv)
{
    srcImage = imread(argv[1]);
    //显示原始图像
    imshow("original image", srcImage);
    //线性滤波方式
    namedWindow("BoxFilter Image");
    g_BoxFilterValue = 5;
    createTrackbar("Kernel Value", "BoxFilter Image", &g_BoxFilterValue, 10, on_BoxFilter);
    on_BoxFilter(g_BoxFilterValue, 0);
    
    namedWindow("Blur Image");
    g_BlurValue = 5;
    createTrackbar("Kernel Value", "Blur Image", &g_BlurValue, 10, on_Blur);
    on_Blur(g_BlurValue, 0);
    
    namedWindow("GaussianBlur Image");
    g_GaussianBlurValue = 4;
    createTrackbar("Kernel Value", "GaussianBlur Image", &g_GaussianBlurValue, 10, on_GaussianBlur);
    on_GaussianBlur(g_GaussianBlurValue, 0);
    
    //非线性滤波方式
    namedWindow("medianBlur Image");
    g_medianBlurValue = 5;
    createTrackbar("Kernel Value", "medianBlur Image", &g_medianBlurValue, 10, on_medianBlur);
    on_medianBlur(g_medianBlurValue, 0);
    
    namedWindow("BilateralFilter Image");
    g_BilateralFilterValue = 5;
    createTrackbar("Kernel Value", "BilateralFilter Image", &g_BilateralFilterValue, 50, on_BilateralFilter);
    on_BilateralFilter(g_BilateralFilterValue, 0);
    waitKey(0);
    return 0;
}

void on_BoxFilter(int, void*)
{
    Mat destImage = srcImage.clone();
    boxFilter(destImage, destImage, -1, Size(g_BoxFilterValue+1,g_BoxFilterValue+1));
//    //! smooths the image using the box filter. Each pixel is processed in O(1) time
//    CV_EXPORTS_W void boxFilter( InputArray src, OutputArray dst, int ddepth,
//                                Size ksize, Point anchor=Point(-1,-1),    ksize 核大小
//                                bool normalize=true,  默认为均值滤波（区域归一化）
//                                int borderType=BORDER_DEFAULT );
    imshow("BoxFilter Image", destImage);
}

// 当方框滤波的 normalize = true 的时候，即为均值滤波
void on_Blur(int, void*)
{
    Mat destImage = srcImage.clone();
    blur(destImage, destImage, Size(g_BlurValue+1,g_BlurValue+1));
//    //! a synonym for normalized box filter
//    CV_EXPORTS_W void blur( InputArray src, OutputArray dst,
//                           Size ksize, Point anchor=Point(-1,-1),
//                           int borderType=BORDER_DEFAULT );
    imshow("Blur Image", destImage);
}

void on_GaussianBlur(int, void*)
{
    Mat destImage = srcImage.clone();
    if (g_GaussianBlurValue % 2 != 0)
    {
        g_GaussianBlurValue++;
    }
    GaussianBlur(srcImage, destImage, Size(g_GaussianBlurValue+1,g_GaussianBlurValue+1), 0);
//    //! smooths the image using Gaussian filter.
//    CV_EXPORTS_W void GaussianBlur( InputArray src,
//                                   OutputArray dst, Size ksize,   需要确保核的大小都为奇数
//                                   double sigmaX, double sigmaY=0,    sigma一般0即可
//                                   int borderType=BORDER_DEFAULT );
    imshow("GaussianBlur Image", destImage);
}

//中值滤波
void on_medianBlur(int, void*)
{
    Mat destImage = srcImage.clone();
    if(g_medianBlurValue % 2 != 0)
    {
        g_medianBlurValue++;
    }
    medianBlur(destImage, destImage, g_medianBlurValue+1);
//    //! smooths the image using median filter.
//    CV_EXPORTS_W void medianBlur( InputArray src, OutputArray dst, int ksize ); size为整形
    imshow("medianBlur Image", destImage);
}

//双线性滤波
void on_BilateralFilter(int, void*)
{
    Mat destImage;
    destImage.create(srcImage.rows, srcImage.cols, srcImage.type());
    bilateralFilter(srcImage, destImage, g_BilateralFilterValue, g_BilateralFilterValue*2, g_BilateralFilterValue/2);
    imshow("BilateralFilter Image", destImage);
}

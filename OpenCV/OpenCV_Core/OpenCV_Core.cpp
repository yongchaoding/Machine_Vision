//
//  OpenCV_Core.cpp
//  OpenCV_Xcode_Project
//
//  Created by 丁永超 on 15/05/2017.
//  Copyright © 2017 Chad_Ding. All rights reserved.
//

#include <stdio.h>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void DrwaEllipse(Mat img, double angle);
void DrawFilledCircle(Mat img, Point center);
void DrawLine(Mat img, Point start, Point end);
void DrawPolygon(Mat img);

#define ACCESS_WAY 1
//访问图像中的像素
void colorReduce_pointer(Mat InputImage, Mat OutputImage, int div);
void colorReduce_STL(Mat InputImage, Mat OutputImage, int div);
void colorReduce_DynamicAddress(Mat InputImage, Mat OutputImage, int div);

#define WINDOW_WIDTH 600

int main(int argc, char** argv)
{
    Mat srcImage = imread(argv[1]);
    Mat destImage;
    destImage.create(srcImage.rows, srcImage.cols, srcImage.type());
    //基本图形的绘制
//    DrwaEllipse(srcImage, 0);
//    DrawFilledCircle(srcImage, Point(srcImage.cols/2, srcImage.rows/2));
//    DrawLine(srcImage, Point(0,0), Point(srcImage.cols/2, srcImage.rows/2));
//    DrawPolygon(srcImage);
    
    //core advance
    
    //利用计时函数比较不同像素操作的效率问题（似乎结果有些问题）
    double time0 = static_cast<double>(getTickCount());
    colorReduce_pointer(srcImage, destImage, 100);
    double time = ((double)getTickCount() - time0)/getTickFrequency();
    cout << "The time used in pointer is " << time << "Second" <<endl;
    
    time0 = static_cast<double>(getTickCount());
    colorReduce_STL(srcImage, destImage, 100);
    time = ((double)getTickCount() - time0)/getTickFrequency();
    cout << "The time used in STL is " << time << "Second" <<endl;
    
    time0 = static_cast<double>(getTickCount());
    colorReduce_DynamicAddress(srcImage, destImage, 100);
    time = ((double)getTickCount() - time0)/getTickFrequency();
    cout << "The time used in DynamicAddress is " << time << "Second" <<endl;
    
    waitKey(0);
    return 0;
}

//绘制椭圆
void DrwaEllipse(Mat img, double angle)
{
    int thickness = 2;
    int lineType = 8;
    
    ellipse(img, Point(img.cols/2, img.rows/2), Size(WINDOW_WIDTH/4, WINDOW_WIDTH/16), angle, 0, 360, Scalar(255,0,0), thickness, lineType);
    ellipse(img, Point(img.cols/2, img.rows/2), Size(WINDOW_WIDTH/4, WINDOW_WIDTH/4), angle, 0, 360, Scalar(255,0,0), thickness, lineType);
//    void ellipse(CV_IN_OUT Mat& img, Point center, Size axes,         将椭圆画到img上，中心点为point，并且大小为Size
//                 double angle, double startAngle, double endAngle,    椭圆旋转角度为angle，弧度从0到360
//                 const Scalar& color, int thickness=1,                色系由Scalar决定， 线宽默认为1
//                 int lineType=8, int shift=0);                        线形默认为8
    imshow("Ellipse", img);
}

//绘制实心圆
void DrawFilledCircle(Mat img, Point center)
{
    int thickness = -1;
    int lineType = 8;
    
    circle(img, center, WINDOW_WIDTH/16, Scalar(0,0,255), thickness, lineType);
//    void circle(CV_IN_OUT Mat& img, Point center, int radius,         将填充圆画到Img上，中心为center，半径为radius
//                const Scalar& color, int thickness=1,
//                int lineType=8, int shift=0);
    imshow("Filled Circle", img);
}

//绘制直线
void DrawLine(Mat img, Point start, Point end)
{
    int thickness = 2;
    int lineType = 8;
    
    line(img, start, end, Scalar(0,255,0), thickness, lineType);
//    void line(CV_IN_OUT Mat& img, Point pt1, Point pt2, const Scalar& color,
//              int thickness=1, int lineType=8, int shift=0);
    imshow("Line", img);
}

//绘制多边形
void DrawPolygon(Mat img)
{
    Point rookpoint[1][3];
    rookpoint[0][0] = Point(img.cols/2, img.rows/2);
    rookpoint[0][1] = Point(img.cols, img.rows/2);
    rookpoint[0][2] = Point(img.cols/2, img.rows);
    
    const Point* ppt[1] = {rookpoint[0]};
    int npt[] = {3};
    
    fillPoly(img, ppt, npt, 1, Scalar(255,255,255));
//    void fillPoly(Mat& img, const Point** pts,                        在img上画多边形， 参考点（顶点集合）为pts
//                  const int* npts, int ncontours,                     参考点数（多边形定点数）为npts，绘制多边形数量为1
//                  const Scalar& color, int lineType=8, int shift=0,
//                  Point offset=Point() );
    
    imshow("Polygon", img);
}

//利用指针访问像素
void colorReduce_pointer(Mat InputImage, Mat OutputImage, int div)
{
    OutputImage = InputImage.clone();
    int rowNumber = OutputImage.rows;
    int colNumber = OutputImage.cols * OutputImage.channels();  //兼容三通道图片
    
    for(int i = 0; i < rowNumber; i++)
    {
        uchar* data = OutputImage.ptr<uchar>(i);        //通过ptr得到图像任意行的首地址
        for (int j = 0; j < colNumber; j++)
        {
            data[j] = data[j]/div*div + div/2;          //对像素点进行处理
        }
    }
    imshow("Reduce Image Using pointer", OutputImage);
}

//利用迭代器操作像素
void colorReduce_STL(Mat InputImage, Mat OutputImage, int div)
{
    OutputImage = InputImage.clone();
    Mat_<Vec3b>::iterator it = OutputImage.begin<Vec3b>();  //初始位置的迭代器
    Mat_<Vec3b>::iterator itend = OutputImage.end<Vec3b>(); //终止位置的迭代器
    
    for(; it != itend; it++)
    {
        (*it)[0] = (*it)[0]/div*div + div/2;        //针对三通道图像
        (*it)[1] = (*it)[1]/div*div + div/2;
        (*it)[2] = (*it)[2]/div*div + div/2;
    }
    imshow("Reduce Image using STL", OutputImage);
}

//利用动态地址操作像素
void colorReduce_DynamicAddress(Mat InputImage, Mat OutputImage, int div)
{
    OutputImage = InputImage.clone();
    int rowNumber = OutputImage.rows;
    int colNumber = OutputImage.cols;
    
    for (int i = 0; i < rowNumber; i++)
    {
        for(int j = 0; j < colNumber; j++)
        {
            OutputImage.at<Vec3b>(i,j)[0] = OutputImage.at<Vec3b>(i,j)[0]/div*div + div/2;  //此处使用vet3b因为三通道图像
            OutputImage.at<Vec3b>(i,j)[1] = OutputImage.at<Vec3b>(i,j)[1]/div*div + div/2;
            OutputImage.at<Vec3b>(i,j)[2] = OutputImage.at<Vec3b>(i,j)[2]/div*div + div/2;
        }
    }
    imshow("Reduce Image using dynamic address", OutputImage);
}

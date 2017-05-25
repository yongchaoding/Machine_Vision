//
//  Image_Convert.cpp
//  OpenCV_Xcode_Project
//
//  Created by 丁永超 on 25/05/2017.
//  Copyright © 2017 Chad_Ding. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void Canny_EdgeDetection(Mat src);
void Sobel_EdgeDetection(Mat src);
void Laplacian_EdgeDetection(Mat src);
void Scharr_EdgeDetection(Mat src);

void Hough_Lines(Mat src);

int main(int argc, char ** argv)
{
    Mat srcImage;
    srcImage = imread(argv[1]);
    imshow("Origin Image", srcImage);
    
    //边缘提取
    //Canny_EdgeDetection(srcImage);
    //Sobel_EdgeDetection(srcImage);
    //Laplacian_EdgeDetection(srcImage);
    //Scharr_EdgeDetection(srcImage);
    
    //霍夫变换
    Hough_Lines(srcImage);
    waitKey(0);
    return 0;
}

void Canny_EdgeDetection(Mat src)
{
    Mat dstImage;
    
    Canny(src, dstImage, 200, 100);
//    //! applies Canny edge detector and produces the edge map.
//    CV_EXPORTS_W void Canny( InputArray image, OutputArray edges,
//                            double threshold1, double threshold2,
//                            int apertureSize=3, bool L2gradient=false );  Sobel算子孔径大小
    //使用滞后阈值，滞后阈值需要两个阈值（高阈值和低阈值）（2：1或在3：1）
    //1. 若某像素位置的幅值超过高阈值，则该像素被保留为边缘像素
    //2. 若某像素位置的幅值小于低阈值，则像素被排除
    //3. 若某像素位置的幅值在两个阈值之间，则仅仅在连接到一个边缘像素时被保留
    imshow("Canny Edge", dstImage);
    
    Mat destImage;
    Mat GrayImage;
    destImage.create(src.rows, src.cols, src.type());
    //彩色图转化为灰度图像
    cvtColor(src, GrayImage, CV_RGB2GRAY);
    //图像滤波
    blur(GrayImage, GrayImage, Size(3,3));
    //边缘提取
    Canny(GrayImage, destImage, 200, 100);
    
    imshow("Canny Edge2", destImage);
}

void Sobel_EdgeDetection(Mat src)
{
    Mat dstImage;
    Mat Grad_x,Grad_y;
    Mat Grad;
    //X方向上的梯度
    Sobel(src, Grad_x, CV_16S, 1, 0);
    convertScaleAbs(Grad_x, Grad_x);
    imshow("Grad_x", Grad_x);
    //Y方向上的梯度
    Sobel(src, Grad_y, CV_16S, 0, 1);
    convertScaleAbs(Grad_y, Grad_y);
    imshow("Grad_y", Grad_y);
    //合并梯度
    addWeighted(Grad_x, 0.5, Grad_y, 0.5, 0, Grad);
    imshow("Grad_X And Grad_y", Grad);
    //X与Y方向上的梯度
    Sobel(src, dstImage, CV_16S, 1, 1);
    convertScaleAbs(dstImage, dstImage);
    imshow("Grad", dstImage);
//    //! applies generalized Sobel operator to the image
//    CV_EXPORTS_W void Sobel( InputArray src, OutputArray dst, int ddepth,     图像深度
//                            int dx, int dy, int ksize=3,      x，y方向上的差分阶数，Sobel核大小1，3，5，7
//                            double scale=1, double delta=0,
//                            int borderType=BORDER_DEFAULT );
    
}


void Laplacian_EdgeDetection(Mat src)
{
    Mat destImage;
    Mat Gray;
    
    cvtColor(src, Gray, CV_RGB2GRAY);
    
    GaussianBlur(Gray, Gray, Size(3,3), 0);
    
    Laplacian(Gray, destImage, Gray.depth(), 3, 1);
//    //! applies Laplacian operator to the image
//    CV_EXPORTS_W void Laplacian( InputArray src, OutputArray dst, int ddepth,     目标图像的深度
//                                int ksize=1, double scale=1, double delta=0,      滤波器孔径大小，正奇数；比例因子；
//                                int borderType=BORDER_DEFAULT );
    convertScaleAbs(destImage, destImage);
    imshow("Laplacian Edge", destImage);
}


void Scharr_EdgeDetection(Mat src)
{
    Mat destImage;
    Mat Grad_x,Grad_y;
    Scharr(src, Grad_x, src.depth(), 1, 0);
    Scharr(src, Grad_y, src.depth(), 0, 1);
//    //! applies the vertical or horizontal Scharr operator to the image
//    CV_EXPORTS_W void Scharr( InputArray src, OutputArray dst, int ddepth,
//                             int dx, int dy, double scale=1, double delta=0,
//                             int borderType=BORDER_DEFAULT );
    convertScaleAbs(Grad_x, Grad_x);
    convertScaleAbs(Grad_y, Grad_y);
//    //! scales array elements, computes absolute values and converts the results to 8-bit unsigned integers: dst(i)=saturate_cast<uchar>abs(src(i)*alpha+beta)
//    CV_EXPORTS_W void convertScaleAbs(InputArray src, OutputArray dst,
//                                      double alpha=1, double beta=0);
    addWeighted(Grad_x, 0.5, Grad_y, 0.5, 0, destImage);
    
    imshow("Scharr Edge Gard_x", Grad_x);
    imshow("Scharr Edge Gard_y", Grad_y);
    imshow("Scharr Edge ", destImage);
}

void Hough_Lines(Mat src)
{
    Mat GaryImg;
    Mat GaussianImg;
    Mat EdgeImg;
    cvtColor(src, GaryImg, CV_RGB2GRAY);
    GaussianBlur(GaryImg, GaussianImg, Size(3,3), 0,0);
    Canny(GaussianImg, EdgeImg, 200, 100);
    //霍夫变换寻找直线
    //存放直线的二维数组
    vector<Vec2f> lines;
    HoughLines(EdgeImg, lines, 1, CV_PI/180, 60);
//    //! finds lines in the black-n-white image using the standard or pyramid Hough transform
//    CV_EXPORTS_W void HoughLines( InputArray image, OutputArray lines,
//                                 double rho, double theta, int threshold,     以像素为单位的距离精度；以弧度为单位的角度精度；累加平面的阈值参数
//                                 double srn=0, double stn=0 );
    //在图上绘制直线
    for(size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0];
        float theta = lines[i][1];
        
        Point pt1,pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        //暂时还未看懂这部分在干什么，应该在找到两个点
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*a);
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*a);
        //在图像上画出直线段
        //line(EdgeImg, pt1, pt2, Scalar(255,255,255));
    }
    
    imshow("Lines Image", EdgeImg);
    
    vector<Vec4i> lines_p;
    HoughLinesP(EdgeImg, lines_p, 1, CV_PI/180, 20, 10, 10);
//    //! finds line segments in the black-n-white image using probabilistic Hough transform
//    CV_EXPORTS_W void HoughLinesP( InputArray image, OutputArray lines,
//                                  double rho, double theta, int threshold,
//                                  double minLineLength=0, double maxLineGap=0 );  最低线段的长度；允许同一行点与点连起来的最大距离
    for(size_t i = 0; i < lines_p.size(); i++)
    {
        Vec4i l = lines_p[i];
        line(src, Point(l[0],l[1]), Point(l[2],l[3]), Scalar(255,255,255));
    }
    imshow("Lines_p Image", src);
}

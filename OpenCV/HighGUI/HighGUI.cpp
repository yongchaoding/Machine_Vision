//
//  HighGUI.cpp
//  OpenCV_Xcode_Project
//
//  Created by 丁永超 on 14/05/2017.
//  Copyright © 2017 Chad_Ding. All rights reserved.
//

#include <stdio.h>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

void on_Trackbar(int, void *);

Mat srcImage;
Mat SMULogo;
int ValueSlider;
const int MaxAlphaValue = 100;
double AlphaValue;
double BetaValue;

int main(int argc, char** argv)
{
//    //初始化Mat数据结构（error）
//    //Mat pic(320,640,Scalar(100));
//    
//    /****************************
//     读取Image图像到Mat类型的srcImage内
//     ****************************/
    srcImage = imread(argv[1]);
//    //Mat imread( const string& filename, int flags=1 );
//    //flags > 0 返回一个3通道的彩色图
//    //flags = 0 返回灰色图像
//    //flags < 0 返回包含Alpha通道的加载图像（不常用）
//    //Example
//    //Mat SrcImageColor = imread(argv[1], 1);
//    Mat SrcImageGray = imread(argv[1], 0);
    SMULogo = imread("/Users/chad_ding/Desktop/Machine_Vision/OpenCV/SMU_logo.jpg");
//    
//    /****************************
//     显示 Mat 图像到窗口
//     ****************************/
//    imshow("origin Image", srcImage);
//    imshow("SMU Logo", SMULogo);
//    //void imshow(const string& winname, InputArray mat);
//    // winname 为窗口识别名称
//    // mat 为需要显示的图像
//    //Example
//    //imshow("Gray Image", SrcImageGray);
//    //imshow("Color Image", SrcImageColor);
//    
//    /****************************
//     提前创建窗口，供滑动条使用
//     ****************************/
//    //如果只是普通的图片显示，可以直接省略
//    namedWindow("Gray Image", CV_WINDOW_NORMAL);
//    //waitKey(0);
//    imshow("Gray Image", SrcImageGray);
//    //namedWindow(const string& winname, int flags = WINDOW_AUTOSIZE);
//    //CV_WINDOW_NORMAL 可改变窗口大小
//    //CV_WINDOW_AUTOSIZE 自动调整窗口，不能手动改变窗口大小
//    //CV_WINDOW_OPENGL 支持OpenGL
//    // 关闭窗口，取消之前分配的与窗口相关的所有内存（对代码不大的程序，不需要调用）
//    //destroyWindow("Gray Image");
//    //destroyAllWindows();
//    
//    /****************************
//     输出图像到文件
//     ****************************/
//    imwrite(argv[2], SrcImageGray);
//    //imwrite( const string& filename, InputArray img, const vector<int>& params=vector<int>());
//    //params 特定格式的参数编码（一般采用默认值）
//    
//    /****************************
//     简单的图像混合
//     ****************************/
//    //定义一个混合区域
//    Mat ImageROI;
//    //采用赋值的方式，若改变ROI，则改变原图（这与copy不同）
//    ImageROI = srcImage(Rect(srcImage.cols - SMULogo.cols, srcImage.rows - SMULogo.rows, SMULogo.cols, SMULogo.rows));
//    //Rect_(_Tp _x, _Tp _y, _Tp _width, _Tp _height);
//    // x, y分别代表矩形在图中的位置， width与height表示矩形的大小
//    //imshow("ImageROI", ImageROI);
//    addWeighted(ImageROI, 0.5, SMULogo, 0.3, 0., ImageROI);
//    //void addWeighted(InputArray src1, double alpha, InputArray src2, double beta, double gamma, OutputArray dst, int dtype=-1);
//    // src1 比重为 alpha， src2 比重为beta, gamma 为像素偏移
//    // dst = alpha*src1 + beta*src2 + gamma
//    imshow("Image_Merge", srcImage);
    
    /****************************
    滑动条的创建与使用
    ****************************/
    
    namedWindow("Image");
    //初始值
    ValueSlider = 70;
    createTrackbar("Merge_factor", "Image", &ValueSlider, MaxAlphaValue, on_Trackbar);
//    int createTrackbar(const string& trackbarname, const string& winname,  //滑动条名称及其窗口名称
//                       int* value, int count,       //指向指针的变量表示滑动条位置及其最大值
//                       TrackbarCallback onChange = 0, //指向回调函数的指针void XXX(int, void*)
//                       void* userdata = 0);       //用户传给回调函数的参数，如value为全局变量，则不需要这个参数
    //初始启动加载照片，否则要等到改变trackbar的时候才会第一次加载照片
    on_Trackbar(ValueSlider, 0);
    //int getTrackbarPos(const string& trackbarname, const string& winname);
    // 返回当前轨迹条的位置
    waitKey(0);
    return 0;
}


void on_Trackbar(int, void *)
{
    //计算 alpha， beta 的值
    AlphaValue = (double) ValueSlider/MaxAlphaValue;
    BetaValue = 1.0 - AlphaValue;
    //简单的图像混合
    Mat ImageROI;
    //利用clone进行copy，确保不对原图像产生影响
    Mat ImageClone = srcImage.clone();
    ImageROI = ImageClone(Rect(srcImage.cols - SMULogo.cols, srcImage.rows - SMULogo.rows, SMULogo.cols, SMULogo.rows));
    addWeighted(ImageROI, AlphaValue, SMULogo, BetaValue, 0., ImageROI);
    //显示混合后的图像
    imshow("Image", ImageClone);
}

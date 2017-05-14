//
//  Calibration.cpp
//  OpenCV_Xcode_Project
//
//  Created by 丁永超 on 14/05/2017.
//  Copyright © 2017 Chad_Ding. All rights reserved.
//

#include <stdio.h>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    Mat ImageInput = imread(argv[1]);
    Mat ImageGray;
    cvtColor(ImageInput, ImageGray, CV_RGB2GRAY);
    
    imshow("Gray_Image", ImageGray);
    
    Mat ImageCorners;
    goodFeaturesToTrack(ImageGray, ImageCorners, 100, 0.01, 10);
    
    waitKey(0);
    return 0;
}

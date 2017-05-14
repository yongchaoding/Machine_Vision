//
//  BasicImage.cpp
//  OpenCV
//
//  Created by 丁永超 on 13/05/2017.
//  Copyright © 2017 Chad_Ding. All rights reserved.
//

#include <stdio.h>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    Mat src = imread(argv[1]);
    imshow("Example1", src);
    waitKey(0);
    return 0;
}

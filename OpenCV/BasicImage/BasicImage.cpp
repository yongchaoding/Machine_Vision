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
    
    IplImage* img = cvLoadImage(argv[1]);
    cout << argv[1] << endl;
    cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE);
    cvShowImage("Example1", img);
    cvWaitKey(0);
    cvReleaseImage(&img);
    cvDestroyWindow("Example1");
    return 0;
}

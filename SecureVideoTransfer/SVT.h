//
//  SVT.h
//  SecureVideoTransfer
//
//  Created by Arjit Sharma on 19/09/2019.
//  Copyright © 2019 Arjit Sharma. All rights reserved.
//

#ifndef SVT_h
#define SVT_h

#include <iostream>
#include <opencv2/opencv.hpp>
#include "FaceBlur.hpp"

using namespace std;
using namespace cv;

static Rect roi[2]; // Only two ROI considered for this project
static int drag = 0;
static Point point1, point2;
static Mat frame, greyframe;
static bool bLastUpdateSecond = false;

class SVT {
    private:
    int frameWidth, frameHeight, fps;
    long lTotalFramesRead, lTotalFramesWrite;
    string strInFilePath, strOutFilePath;
    VideoCapture cap;
    VideoWriter video;
    
    public:
    int getInFile(string strInFilePath);
    string getOutFile(string strOutFilePath);
    void showMeTheVideo();
    void writeTheVideo(Mat frame);
    int startCapture(string strInFilePath);
    int endCapture(string strInFilePath);
    void finalize();
    int BlurROI(Mat frame, int iCall);
    
    FaceBlur fb;
};


#endif /* SVT_h */

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
static Mat frame;
static bool bLastUpdateSecond = false;

class SVT {
    private:
    bool bPauseVideo = 1; // Start with no pause
    int frameWidth, frameHeight, fps;
    long lTotalFramesRead, lTotalFramesWrite;
    string strInFilePath, strOutFilePath, strOutImagePath, bWithHaarFaceBlur;
    VideoCapture cap;
    VideoWriter video;
    
    public:
    int getInFile(string strInFilePath);
    string getOutFile(string strOutFilePath);
    void FaceBlurRequired(string bWithHaarFaceBlur);
    void showMeTheVideo(string bWithHaarFaceBlur);
    void writeTheVideo(Mat frame);
    int BlurROI(Mat frame, int iCall, string bWithHaarFaceBlur);
    void finalize();
    
    FaceBlur fb;
};


#endif /* SVT_h */

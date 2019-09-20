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

using namespace std;
using namespace cv;

class SVT {
    private:
    int frameWidth, frameHeight;
    long lTotalFramesRead, lTotalFramesWrite;
    string strInFilePath, strOutFilePath;
    Mat frame, greyframe;
    VideoCapture cap;
    VideoWriter video;
    
    public:
    int getInFile(string strInFilePath);
    string getOutFile();
    void showMeTheVideo();
    void writeTheVideo();
    int startCapture(string strInFilePath);
    int endCapture(string strInFilePath);
    void finalize();
};

#endif /* SVT_h */

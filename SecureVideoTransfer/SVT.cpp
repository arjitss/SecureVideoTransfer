//
//  SVT.cpp
//  SecureVideoTransfer
//
//  Created by Arjit Sharma on 19/09/2019.
//  Copyright © 2019 Arjit Sharma. All rights reserved.
//

#include "SVT.h"

int SVT::getInFile(string strInFilePath){
   // For Test Purpose
    if(strInFilePath.length() == 0)
        strInFilePath = "/Users/arjits/cosmos/VideoAnalytics/OpenCvShamb2/RightScenario.mp4";
    this->strInFilePath = strInFilePath;
    cap.open(strInFilePath);
    if(!cap.isOpened()){
      cout << "Error opening video stream or file" << endl;
      return -1;
    }
    // Default resolution of the frame is obtained.The default resolution is system dependent.
    frameWidth = cap.get(CAP_PROP_FRAME_WIDTH);
    frameHeight = cap.get(CAP_PROP_FRAME_HEIGHT);
    fps = cap.get(CAP_PROP_FPS);
    return 0;
};
string SVT::getOutFile(string strOutFilePath){
    
    time_t curtime;
    time(&curtime);
    
    if(strOutFilePath == "")
        strOutFilePath.assign(strInFilePath.begin(), strInFilePath.end()-4);
    
    strOutFilePath.append("TCS_Updated.avi");
    cout << "File will be written at following location: \n" << strOutFilePath << endl;

    // Define the codec and create VideoWriter object.
    video.open(strOutFilePath,cv::VideoWriter::fourcc('M','J','P','G'),fps, Size(frameWidth,frameHeight));
    return strOutFilePath;
};

 void mouseClick(int event, int x, int y, int flags, void* param){
     
     Mat img1 = ::frame.clone();
     
    if (event == EVENT_LBUTTONDOWN && !drag){
        point1 = Point(x, y);
        drag = 1;

    }
    if (event == EVENT_MOUSEMOVE && drag){
        point2 = Point(x, y);
        rectangle(img1, point1, point2, Scalar(0, 0, 255), 1, 8, 0);
        imshow("Frame", img1);
        }
    
    if (event == EVENT_LBUTTONUP && drag){
        point2 = Point(x, y);
        drag = 0;
        if(::roi[0].empty() || bLastUpdateSecond){
            ::roi[0] = Rect(point1.x, point1.y, x - point1.x, y - point1.y);
            bLastUpdateSecond = false;
        }
        else{
            ::roi[1] = Rect(point1.x, point1.y, x - point1.x, y - point1.y);
            bLastUpdateSecond = true;
        }
        
    }
    if (event == EVENT_LBUTTONUP){
        drag = 0;
    }
};

void SVT::showMeTheVideo(){
    cap >> ::frame;
    // If the frame is empty, break immediately
    if (frame.empty())
        exit(-1);
    
    lTotalFramesRead ++ ; // Get the count of the frames
    cout << lTotalFramesRead << endl;
    BlurROI(::frame, 0);
    waitKey(0);
    
    while(1){
        if( BlurROI(::frame, 1) == -1)
            break;
    }
};

 int SVT::BlurROI(Mat frame, int iCall){
    Mat grey;
    if(lTotalFramesRead == 1 && iCall == 0){
        imshow( "Frame", frame );
        setMouseCallback("Frame", mouseClick, NULL);
        return 0;
    }
     // If the frame is empty, break immediately
    if (frame.empty())
        return -1;
    
    for (int i = 0; i < (sizeof(roi) / sizeof(roi[0])) ; i++){
        cvtColor(frame, grey, COLOR_BGR2GRAY);
        cvtColor(grey, grey, COLOR_GRAY2BGR);
        if(!::roi[i].empty()){
            grey(::roi[i]).copyTo(frame(::roi[i]));
            grey = frame;
            GaussianBlur(grey(::roi[i]), grey(::roi[i]), Size(0, 0), 4);
        }
    }
    imshow( "Frame", frame );
    writeTheVideo(frame);
    cap >> ::frame; //next frame
    lTotalFramesRead++;

    // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
        return -1;
    return 0;
 };

void SVT::writeTheVideo(Mat frame){
       // Get the count of the frames
    lTotalFramesWrite ++ ;
    video.write(frame);
};

void SVT::finalize(){
    cout << "Cleaning the data \n";
    cout << "Total Frames Read: " << lTotalFramesRead << endl;
    cap.release();
    destroyAllWindows();
};

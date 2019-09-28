//
//  SVT.cpp
//  SecureVideoTransfer
//
//  Created by Arjit Sharma on 19/09/2019.
//  Copyright © 2019 Arjit Sharma. All rights reserved.
//

#include "SVT.h"

//----------------------------------------------------------------------
/* This function is for opening the input Video file that we wish to  */
/* secure & blur                                                      */
//----------------------------------------------------------------------

int SVT::getInFile(string strInFilePath){
   // For Test Purpose
    if(strInFilePath.length() == 0){
        //strInFilePath = "https://www.w3schools.com/html/mov_bbb.mp4";
        strInFilePath = "/Users/arjits/cosmos/VideoAnalytics/OpenCvShamb2/RightScenario.mp4";
    }
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

//----------------------------------------------------------------------
/* This function is for opening the output Video file based on the    */
/* input                                                              */
//----------------------------------------------------------------------
string SVT::getOutFile(string strOutFilePath){
    
    time_t curtime;
    time(&curtime);
    
    if(strOutFilePath == "")
        strOutFilePath.assign(strInFilePath.begin(), strInFilePath.end()-4);
    
    strOutFilePath.append("Secure_Updated.avi");
    cout << "File will be written at following location: \n" << strOutFilePath << endl;

    // Define the codec and create VideoWriter object.
    video.open(strOutFilePath,cv::VideoWriter::fourcc('M','J','P','G'),fps, Size(frameWidth,frameHeight));
    return strOutFilePath;
};

//----------------------------------------------------------------------
/* Identify the 2 ROIs based on the mouse click                        */
//----------------------------------------------------------------------

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

//----------------------------------------------------------------------
/* This is the Key function that is called to view the video
   This function also in turn calls:
   1. BlurROI - for selecting two ROIs and Blur it                   */
//----------------------------------------------------------------------

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

//----------------------------------------------------------------------
/* Heart of the program
  1. Identify ROI based on mouse click and blur it
  2. Calls extern function detectAndDraw - That use Haar to indetify the
     face and blur it
  3. It also pause or start play based on space bar or letter 'p' press */
//----------------------------------------------------------------------

 int SVT::BlurROI(Mat frame, int iCall){
    Mat grey, imgFace;
    if(lTotalFramesRead == 1 && iCall == 0){
        imshow( "Frame", frame );
        setMouseCallback("Frame", mouseClick, NULL);
        return 0;
    }
     // If the frame is empty, break immediately
    if (frame.empty())
        return -1;
    
     if(bPauseVideo){
        for (int i = 0; i < (sizeof(roi) / sizeof(roi[0])) ; i++){
            cvtColor(frame, grey, COLOR_BGR2GRAY);
            cvtColor(grey, grey, COLOR_GRAY2BGR);
            if(!::roi[i].empty()){
                grey(::roi[i]).copyTo(frame(::roi[i]));
                grey = frame;
                GaussianBlur(grey(::roi[i]), grey(::roi[i]), Size(0, 0), 4);
            }
        }
        // imgFace = frame.clone();
         fb.detectAndDraw(frame);
        imshow( "Frame", frame );
     
        writeTheVideo(frame);
        cap >> ::frame; //next frame
        lTotalFramesRead++;
     }

    // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
        return -1;
     else if (c == 32 || c == 'p') //pause in and out on space press or 'p' key press
         bPauseVideo = !bPauseVideo;
     else if (c == 'c') { // capture screenshot
         strOutImagePath.assign(strInFilePath.begin(), strInFilePath.end()-4);
         strOutImagePath = strOutImagePath + to_string(lTotalFramesRead) + ".jpg";
         imwrite(strOutImagePath, frame);
     }
    return 0;
 };

//----------------------------------------------------------------------
/* Writing the Video File                        */
//----------------------------------------------------------------------

void SVT::writeTheVideo(Mat frame){
       // Get the count of the frames
    lTotalFramesWrite ++ ;
    video.write(frame);
};

//----------------------------------------------------------------------
/* Clean Up                        */
//----------------------------------------------------------------------
void SVT::finalize(){
    cout << "Cleaning the data \n";
    cout << "Total Frames Read: " << lTotalFramesRead << endl;
    cap.release();
    destroyAllWindows();
};

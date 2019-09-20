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
    strInFilePath = "/Users/arjits/cosmos/VideoAnalytics/OpenCvShamb2/RightScenario.mp4";
    cap.open(strInFilePath);
    if(!cap.isOpened()){
      cout << "Error opening video stream or file" << endl;
      return -1;
    }
    // Default resolution of the frame is obtained.The default resolution is system dependent.
    frameWidth = cap.get(CAP_PROP_FRAME_WIDTH);
    frameHeight = cap.get(CAP_PROP_FRAME_HEIGHT);
    
    return 0;
};
string SVT::getOutFile(){
    
    getline(cin, strOutFilePath);
    if(strOutFilePath == "")
        strOutFilePath = strInFilePath;
    // For Test Purpose
    // strOutFilePath = "/Users/arjits/cosmos/VideoAnalytics/OpenCvShamb2/RightScenario3.mp4";
    cout << "File will be written at following location: \n" << strOutFilePath << endl;
    
    // Define the codec and create VideoWriter object.
    video.open(strOutFilePath,cv::VideoWriter::fourcc('M','J','P','G'),70, Size(frameWidth,frameHeight));
    return strOutFilePath;
};

void SVT::showMeTheVideo(){
    while(1){
        cap >> frame;
     
       // If the frame is empty, break immediately
       if (frame.empty())
         break;
       // Get the count of the frames
       lTotalFramesRead ++ ;
       // cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
       // Display the resulting frame
       imshow( "Frame", frame );
    
       // Press  ESC on keyboard to exit
       char c=(char)waitKey(25);
       if(c==27)
         break;
    }
};
void SVT::writeTheVideo(){
    while(1){
        cap >> frame;
     
       // If the frame is empty, break immediately
       if (frame.empty())
         break;
       // Get the count of the frames
        lTotalFramesWrite ++ ;
        video.write(frame);
       // Display the resulting frame
       imshow( "Frame", frame );
    
       // Press  ESC on keyboard to exit
       char c=(char)waitKey(25);
       if(c==27)
         break;
    }
};

void SVT::finalize(){
    cout << "Cleaning the data \n";
    cout << "Total Frames Read: " << lTotalFramesRead << endl;
    cap.release();
    destroyAllWindows();
}

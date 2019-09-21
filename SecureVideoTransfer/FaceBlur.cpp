//
//  FaceBlur.cpp
//  SecureVideoTransfer
//
//  Created by Arjit Sharma on 21/09/2019.
//  Copyright © 2019 Arjit Sharma. All rights reserved.
//

#include "FaceBlur.hpp"

//----------------------------------------------------------------------
/* To load the Haar Cascade XML                       */
//----------------------------------------------------------------------

int FaceBlur::LoadCascade(string xmlFile){
    if( xmlFile == ""){
        xmlFile = "/Users/arjits/cosmos/VideoAnalytics/opencv-4.1.1/data/haarcascades/haarcascade_frontalface_alt.xml";
    }
    
    cascade.load( xmlFile ) ;

    return 0;
};


//----------------------------------------------------------------------
/* Call the Haar Algo to Blur the face in Video                       */
//----------------------------------------------------------------------
void FaceBlur::detectAndDraw(Mat& img){
    Mat frame_gray, img1;
    
    cvtColor( img, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
      std::vector<Rect> faces;
    // Detect faces of different sizes using cascade classifier
       cascade.detectMultiScale( frame_gray,faces );
    for ( size_t i = 0; i < faces.size(); i++ ){
        Rect faceROI2 =  faces[i];
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        //ellipse( img, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 255, 255 ), 4 );
        
        GaussianBlur(img(faceROI2), img(faceROI2), Size(0, 0), 4);
    }
}



//
//  FaceBlur.hpp
//  SecureVideoTransfer
//
//  Created by Arjit Sharma on 21/09/2019.
//  Copyright © 2019 Arjit Sharma. All rights reserved.
//

#ifndef FaceBlur_hpp
#define FaceBlur_hpp

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class FaceBlur{
private:
  CascadeClassifier cascade, nestedCascade;
public:
    int LoadCascade(string xmlFile);
    void detectAndDraw( Mat& img);

};


#endif /* FaceBlur_hpp */

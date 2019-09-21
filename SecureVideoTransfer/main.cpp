//
//  main.cpp
//  SecureVideoTransfer
//
//  Created by Arjit Sharma on 19/09/2019.
//  Copyright © 2019 Arjit Sharma. All rights reserved.
//

// This programe does 3 things
// 1. Read a vide input and save it to new location.
// 2. Blur out the max 3 ROI selected by user
// 3. Detect the face using HAR algo and blur it
//
#include <iostream>
#include "SVT.h"

int main(int argc, const char * argv[]) {
    string strInFilePath, strOutFilePath;
    // insert code here...
    std::cout << "Hello, World!\n";
    SVT svt;
    std::cout << "Enter the Path and File Name to be converted:\n";
    getline(cin, strInFilePath);

    if( svt.getInFile(strInFilePath) == -1){
        exit(-1);
    }
    
    std::cout << "Enter the Path and File Name of output file (Default : Enter)\n";
    
    getline(cin, strOutFilePath);
    cout << strOutFilePath <<endl;
    
    svt.getOutFile(strOutFilePath); // Use the same path as input file
    
    svt.fb.LoadCascade("");
    
    svt.showMeTheVideo();
    svt.finalize();
    return 0;
}
